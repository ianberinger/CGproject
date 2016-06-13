uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform highp vec4 EyePos;
uniform mediump mat3 NormalMatrix;

uniform mediump vec4 LightPos;

uniform lowp vec3 Ka;   // ambient material coefficient
uniform lowp vec3 Kd;   // diffuse material coefficient
uniform lowp vec3 Ks;   // specular material coefficient

uniform mediump float Ns;   // specular material exponent (shininess)

uniform highp vec3 Ia;   // ambient light intensity
uniform highp vec3 Id;   // diffuse light intensity

attribute vec4 Position;
attribute vec3 Normal;
attribute vec3 Tangent;
attribute vec4 TexCoord;

varying highp vec4 posVarying;
varying highp float detailLevel;

varying lowp vec4 ambientVarying;
varying lowp vec4 diffuseVarying;
varying lowp vec4 specularVarying;
varying lowp vec4 texCoordVarying;

varying mediump vec3 normalVarying;     // normal in world space
varying mediump vec3 tangentVarying;    // tangent in world space


void main() {
  vec4 pos = ModelViewMatrix * Position;
  
  highp float minZ = pos.z / 3.0;
  highp float maxZ = pos.z * 5.0;
  
  posVarying=pos;
  normalVarying = normalize(NormalMatrix * Normal);
  tangentVarying = normalize(NormalMatrix * Tangent);
  texCoordVarying = TexCoord;

  
  detailLevel = 1.0 - log(pos.z / minZ)/log(maxZ / minZ);
  
  gl_Position = ProjectionMatrix * pos;
}
