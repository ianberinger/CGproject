
uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mediump vec4 EyePos;
uniform mediump vec4 LightPos;

attribute vec4 Position;
attribute vec4 Normal;
attribute vec4 TexCoord;

// TODO: create varying variable to hand over color values to the fragment shader

varying vec4 colorVarying;
varying mediump vec4 posVarying;
varying lowp vec4 texCoordVarying;


void main()
{
    vec4 pos = ModelViewMatrix * Position;  // vertex position in eye coordinates

    // TODO: uncomment to assign normal value to color varying variable
    colorVarying = vec4(vec3(0.5) + Normal.xyz * 0.5, 1.0);
    posVarying=pos;
  lowp float x = mod(TexCoord.x, 10.0);
  lowp float y = mod(TexCoord.y, 10.0);
    texCoordVarying = vec4(vec3(x,y,TexCoord.z),1.0);

    gl_Position = ProjectionMatrix * pos;
}
