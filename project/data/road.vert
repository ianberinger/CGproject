uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mediump vec4 EyePos;

attribute vec4 Position;
attribute vec4 Normal;
attribute vec4 TexCoord;

varying mediump vec4 posVarying;
varying lowp vec4 texCoordVarying;
varying mediump float detailLevel;

void main() {
  vec4 pos = ModelViewMatrix * Position;
  
  mediump float minZ = pos.z / 3.0;
  mediump float maxZ = pos.z * 4.2;
  
  posVarying=pos;
  texCoordVarying = TexCoord;
  
  detailLevel = 1.0 - log(pos.z / minZ)/log(maxZ / minZ);
  
  gl_Position = ProjectionMatrix * pos;
}
