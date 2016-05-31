uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mediump vec4 EyePos;

attribute vec4 Position;
attribute vec4 Normal;
attribute vec4 TexCoord;

varying mediump vec4 posVarying;
varying lowp vec4 texCoordVarying;

void main() {
  vec4 pos = ModelViewMatrix * Position;
  
  posVarying=pos;
  texCoordVarying = TexCoord;
  
  gl_Position = ProjectionMatrix * pos;
}
