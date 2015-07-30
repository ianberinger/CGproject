// Some operations of vmmlib will cause a warning in Visual C++ (specifically culling)
#define _SCL_SECURE_NO_WARNINGS

#include "../headers/Renderer.h"
#include "../headers/IRenderProject.h"
#include "../headers/ShaderDataFile.h"
#include "../headers/ShaderData.h"
#include "../headers/Configuration.h"

#include <boost/lexical_cast.hpp>
using boost::lexical_cast;

/* Public functions */

Renderer::Renderer()
{
	reset();
}

ViewPtr Renderer::getView()
{
	return _view;
}

InputPtr Renderer::getInput()
{
	return _input;
}

AssetManagementPtr Renderer::getAssets()
{
	return _assetManagement;
}

RenderQueuePtr Renderer::getRenderQueue()
{
	return _renderQueue;
}

bool Renderer::isInitialized()
{
	return _initialized;
}

bool Renderer::isRunning()
{
    return _running;
}

void Renderer::setRenderProject(IRenderProject *p)
{
	_renderProject = p;
}

void Renderer::setInitFunction(void(*f)())
{
	_initFunction = f;
}

void Renderer::setLoopFunction(void(*f)(const double deltaTime, const double elapsedTime))
{
	_loopFunction = f;
}

void Renderer::setTerminateFunction(void(*f)())
{
	_terminateFunction = f;
}

bool Renderer::initRenderer(std::string windowTitle)
{
    if (_initialized)
        return true;
    
    // initialize view
    if(!_view)  _view = ViewPtr(new View);
	if (!_view->initView(windowTitle))
        return false;
    
	// OpenGL
	// clear
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// for Alpha
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Input
    if(!_input)  			_input = InputPtr(new Input);
    _input->setView(_view);

	// Asset management
	if (!_assetManagement)  _assetManagement = AssetManagementPtr(new AssetManagement);

	// Render queue
	if (!_renderQueue)  _renderQueue = RenderQueuePtr(new RenderQueue);

    // call static function if set
    if (_initFunction)
        _initFunction();
    
    // call member function if set
    if (_renderProject)
        _renderProject->initFunction();

	_initialized = true;
    
    return true;
}

bool Renderer::initRenderer(bool fullscreen, std::string windowTitle)
{
    if (_initialized)
        return true;
    
    // initialize view
    if(!_view)  _view = ViewPtr(new View);
	if (!_view->initView(fullscreen, windowTitle))
        return false;
    
	return initRenderer(windowTitle);
}

bool Renderer::initRenderer(GLint width, GLint height, bool fullscreen, std::string windowTitle)
{
    if (_initialized)
        return true;
    
    // initialize view
    if(!_view) 		_view = ViewPtr(new View);
	if (!_view->initView(width, height, fullscreen, windowTitle))
        return false;
    
	return initRenderer(windowTitle);
}

void Renderer::drawModel(const std::string &modelName, const std::string &cameraName, const vmml::Matrix4f & modelMatrix, const std::vector<std::string> &lightNames, bool doFrustumCulling, bool cullIndividualGeometry)
{
	drawModel(modelName, modelMatrix, _assetManagement->getCamera(cameraName)->getViewMatrix(), _assetManagement->getCamera(cameraName)->getProjectionMatrix(), lightNames, doFrustumCulling, cullIndividualGeometry);
}

void Renderer::drawModel(const std::string &modelName, const vmml::Matrix4f &modelMatrix, const vmml::Matrix4f &viewMatrix, const vmml::Matrix4f &projectionMatrix, const std::vector<std::string> &lightNames, bool doFrustumCulling, bool cullIndividualGeometry)
{
	vmml::Matrix4f modelViewMatrix = viewMatrix*modelMatrix;
	vmml::Matrix4f modelViewProjectionMatrix;
	vmml::Visibility visibility = vmml::VISIBILITY_FULL;

	GLint compareShader = -1;

	// Frsutum culling
	if (doFrustumCulling){
		modelViewProjectionMatrix = projectionMatrix*modelViewMatrix;
		visibility = viewFrustumCulling(_assetManagement->getModel(modelName)->getBoundingBoxObjectSpace(), modelViewProjectionMatrix);
		//if (visibility == vmml::VISIBILITY_NONE) 	bRenderer::log(modelName + " was culled");
	}

	// Draw geometry
	if (visibility != vmml::VISIBILITY_NONE){
		Model::GroupMap &groupsModel = _assetManagement->getModel(modelName)->getGroups();
		for (auto i = groupsModel.begin(); i != groupsModel.end(); ++i)
		{
			GeometryPtr geometry = i->second;

			// Only do frsutum culling for the geometry if the model has more than one geometry object, 
			// otherwise the culling restult of the whole model is the same as for the geometry
			if (doFrustumCulling && cullIndividualGeometry && groupsModel.size() > 1){
				visibility = viewFrustumCulling(geometry->getBoundingBoxObjectSpace(), modelViewProjectionMatrix);
				//if (visibility == vmml::VISIBILITY_NONE) 	bRenderer::log(modelName + " was culled");
			}

			if (visibility != vmml::VISIBILITY_NONE){
				ShaderPtr shader = geometry->getMaterial()->getShader();

				// Only pass Uniforms if the shader of the current geometry differs from the one of the last
				if (shader && compareShader != shader->getProgramID())
				{
					compareShader = shader->getProgramID();

					shader->setUniform(bRenderer::DEFAULT_SHADER_UNIFORM_PROJECTION_MATRIX(), projectionMatrix);
					shader->setUniform(bRenderer::DEFAULT_SHADER_UNIFORM_MODEL_VIEW_MATRIX(), modelViewMatrix);

					// Lighting
					if (shader->supportsDiffuseLighting() || shader->supportsSpecularLighting()){
						GLfloat numLights = lightNames.size();
						bool variableNumberOfLights = shader->supportsVariableNumberOfLights();
						GLuint maxLights = shader->getMaxLights();
						if (numLights > maxLights)
							numLights = maxLights;

						if (variableNumberOfLights)
							shader->setUniform(bRenderer::DEFAULT_SHADER_UNIFORM_NUMBER_OF_LIGHTS(), numLights);
						for (int i = 0; i < numLights; i++){
							std::string pos = lexical_cast<std::string>(i);
							LightPtr l = _assetManagement->getLight(lightNames[i]);
							shader->setUniform(bRenderer::DEFAULT_SHADER_UNIFORM_LIGHT_POSITION_VIEW_SPACE() + pos, (viewMatrix*l->getPosition()));
							if (shader->supportsDiffuseLighting())
								shader->setUniform(bRenderer::DEFAULT_SHADER_UNIFORM_DIFFUSE_LIGHT_COLOR() + pos, l->getDiffuseColor());
							if (shader->supportsSpecularLighting())
								shader->setUniform(bRenderer::DEFAULT_SHADER_UNIFORM_SPECULAR_LIGHT_COLOR() + pos, l->getSpecularColor());
							shader->setUniform(bRenderer::DEFAULT_SHADER_UNIFORM_LIGHT_INTENSITY() + pos, l->getIntensity());
							shader->setUniform(bRenderer::DEFAULT_SHADER_UNIFORM_LIGHT_ATTENUATION() + pos, l->getAttenuation());
						}
					}
					// Ambient
					if (shader->supportsAmbientLighting())
						shader->setUniform(bRenderer::DEFAULT_SHADER_UNIFORM_AMBIENT_COLOR(), _assetManagement->getAmbientColor());
				}

				geometry->draw();
			}
		}
	}
}


void Renderer::queueModel(const std::string &modelName, const std::string &cameraName, const vmml::Matrix4f & modelMatrix, const std::vector<std::string> &lightNames, bool doFrustumCulling, bool cullIndividualGeometry, bool isTransparent, GLenum blendSfactor, GLenum blendDfactor, GLfloat customDistance)
{
	queueModel(modelName, modelMatrix, _assetManagement->getCamera(cameraName)->getViewMatrix(), _assetManagement->getCamera(cameraName)->getProjectionMatrix(), lightNames, doFrustumCulling, cullIndividualGeometry, isTransparent, blendSfactor, blendDfactor, customDistance);
}

void Renderer::queueModel(const std::string &modelName, const vmml::Matrix4f &modelMatrix, const vmml::Matrix4f &viewMatrix, const vmml::Matrix4f &projectionMatrix, const std::vector<std::string> &lightNames, bool doFrustumCulling, bool cullIndividualGeometry, bool isTransparent, GLenum blendSfactor, GLenum blendDfactor, GLfloat customDistance)
{
	vmml::Matrix4f modelViewMatrix = viewMatrix*modelMatrix;
	vmml::Matrix4f modelViewProjectionMatrix;
	vmml::Visibility visibility = vmml::VISIBILITY_FULL;

	// Frsutum culling
	if (doFrustumCulling){
		modelViewProjectionMatrix = projectionMatrix*modelViewMatrix;
		visibility = viewFrustumCulling(_assetManagement->getModel(modelName)->getBoundingBoxObjectSpace(), modelViewProjectionMatrix);
		//if (visibility == vmml::VISIBILITY_NONE) 	bRenderer::log(modelName + " was culled");
	}

	// Draw geometry
	if (visibility != vmml::VISIBILITY_NONE){
		Model::GroupMap &groupsModel = _assetManagement->getModel(modelName)->getGroups();
		ShaderPtr shaderLastGeometry;
		PropertiesPtr propertiesLastGeometry;
		for (auto i = groupsModel.begin(); i != groupsModel.end(); ++i)
		{
			std::string groupName = i->first;
			GeometryPtr geometry = i->second;

			// Only do frsutum culling for the geometry if the model has more than one geometry object, 
			// otherwise the culling restult of the whole model is the same as for the geometry
			if (doFrustumCulling && cullIndividualGeometry && groupsModel.size() > 1){
				visibility = viewFrustumCulling(geometry->getBoundingBoxObjectSpace(), modelViewProjectionMatrix);
				//if (visibility == vmml::VISIBILITY_NONE) 	bRenderer::log(modelName + " was culled");
			}

			if (visibility != vmml::VISIBILITY_NONE){
				ShaderPtr shader = geometry->getMaterial()->getShader();
				if (shader)
				{
					// Get existing properties of the geometry
					PropertiesPtr propertiesGeometry = geometry->getProperties();

					// Only create new properties if current geometry has different properties or a different shader than the last
					if (shader != shaderLastGeometry || propertiesGeometry != propertiesLastGeometry){
						propertiesLastGeometry = propertiesGeometry;
						shaderLastGeometry = shader;

						if (propertiesGeometry){
							propertiesRenderQueue = *propertiesGeometry;
						}
						else
							propertiesRenderQueue.clear();

						propertiesRenderQueue.setMatrix(bRenderer::DEFAULT_SHADER_UNIFORM_PROJECTION_MATRIX(), projectionMatrix);
						propertiesRenderQueue.setMatrix(bRenderer::DEFAULT_SHADER_UNIFORM_MODEL_VIEW_MATRIX(), modelViewMatrix);

						// Lighting
						if (shader->supportsDiffuseLighting() || shader->supportsSpecularLighting()){
							GLfloat numLights = lightNames.size();
							bool variableNumberOfLights = shader->supportsVariableNumberOfLights();
							GLuint maxLights = shader->getMaxLights();
							if (numLights > maxLights)
								numLights = maxLights;

							if (variableNumberOfLights)
								propertiesRenderQueue.setScalar(bRenderer::DEFAULT_SHADER_UNIFORM_NUMBER_OF_LIGHTS(), numLights);
							for (int i = 0; i < numLights; i++){
								std::string pos = lexical_cast<std::string>(i);
								LightPtr l = _assetManagement->getLight(lightNames[i]);
								propertiesRenderQueue.setVector(bRenderer::DEFAULT_SHADER_UNIFORM_LIGHT_POSITION_VIEW_SPACE() + pos, (viewMatrix*l->getPosition()));
								if (shader->supportsDiffuseLighting())
									propertiesRenderQueue.setVector(bRenderer::DEFAULT_SHADER_UNIFORM_DIFFUSE_LIGHT_COLOR() + pos, l->getDiffuseColor());
								if (shader->supportsSpecularLighting())
									propertiesRenderQueue.setVector(bRenderer::DEFAULT_SHADER_UNIFORM_SPECULAR_LIGHT_COLOR() + pos, l->getSpecularColor());
								propertiesRenderQueue.setScalar(bRenderer::DEFAULT_SHADER_UNIFORM_LIGHT_INTENSITY() + pos, l->getIntensity());
								propertiesRenderQueue.setScalar(bRenderer::DEFAULT_SHADER_UNIFORM_LIGHT_ATTENUATION() + pos, l->getAttenuation());
							}
						}
						// Ambient
						if (shader->supportsAmbientLighting())
							propertiesRenderQueue.setVector(bRenderer::DEFAULT_SHADER_UNIFORM_AMBIENT_COLOR(), _assetManagement->getAmbientColor());
					}

					if (isTransparent){
						// Find out distance
						GLfloat distance = customDistance;
						if (distance > 9999.0f){
							vmml::Vector3f centerViewSpace = (modelViewProjectionMatrix * geometry->getBoundingBoxObjectSpace().getCenter());
							distance = centerViewSpace.z();
						}
						_renderQueue->submitToRenderQueue(shader->getProgramID(), groupName, geometry->getMaterial()->getName(), geometry, propertiesRenderQueue, distance, isTransparent, blendSfactor, blendDfactor);
					}
					else
						_renderQueue->submitToRenderQueue(shader->getProgramID(), groupName, geometry->getMaterial()->getName(), geometry, propertiesRenderQueue);
				}

			}
		}
	}
}

vmml::Visibility Renderer::viewFrustumCulling(const vmml::AABBf &aabbObjectSpace, const vmml::Matrix4f &modelViewProjectionMatrix)
{
	vmml::FrustumCullerf culler;
	culler.setup(modelViewProjectionMatrix);
	return culler.test_aabb(vmml::Vector2f(aabbObjectSpace.getMin().x(), aabbObjectSpace.getMax().x()), vmml::Vector2f(aabbObjectSpace.getMin().y(), aabbObjectSpace.getMax().y()), vmml::Vector2f(aabbObjectSpace.getMin().z(), aabbObjectSpace.getMax().z()));
}

vmml::Visibility Renderer::viewFrustumCulling(const vmml::AABBf &aabbObjectSpace, const vmml::Matrix4f &modelViewProjectionMatrix, vmml::FrustumCullerf &culler)
{
	culler.setup(modelViewProjectionMatrix);
	return culler.test_aabb(vmml::Vector2f(aabbObjectSpace.getMin().x(), aabbObjectSpace.getMax().x()), vmml::Vector2f(aabbObjectSpace.getMin().y(), aabbObjectSpace.getMax().y()), vmml::Vector2f(aabbObjectSpace.getMin().z(), aabbObjectSpace.getMax().z()));
}

/* Private functions */

void Renderer::reset()
{
	_stopTime = 0;
	_initialTime = 0;
	_elapsedTime = 0;

	if (_assetManagement)
		_assetManagement->clear();
}
