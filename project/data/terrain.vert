uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform highp vec4 EyePos;

attribute vec4 Position;
attribute vec4 Normal;
attribute vec4 TexCoord;

varying highp vec4 posVarying;
varying highp vec4 texCoordVarying;
varying highp float detailLevel;

void main() {
  vec4 pos = ModelViewMatrix * Position;
  
  highp float minZ = pos.z / 3.0;
  highp float maxZ = pos.z * 5.0;
  
  posVarying=pos;
  texCoordVarying = TexCoord;
  
  detailLevel = 1.0 - log(pos.z / minZ)/log(maxZ / minZ);
  
  gl_Position = ProjectionMatrix * pos;
}
