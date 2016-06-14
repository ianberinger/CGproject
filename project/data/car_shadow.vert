uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mediump vec4 EyePos;

attribute vec4 Position;
attribute vec4 Normal;
attribute vec4 TexCoord;

// TODO: create varying variable to hand over color values to the fragment shader

varying mediump vec4 posVarying;
varying lowp vec4 texCoordVarying;

void main()
{
  vec4 pos = ModelViewMatrix * Position;  // vertex position in eye coordinates
  
  // TODO: uncomment to assign normal value to color varying variable
  posVarying=pos;
  texCoordVarying = TexCoord;
  
  gl_Position = ProjectionMatrix * pos;
}
