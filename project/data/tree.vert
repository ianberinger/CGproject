
uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

attribute vec4 Position;
attribute vec4 Normal;
attribute vec4 TexCoord;

// TODO: create varying variable to hand over color values to the fragment shader

varying vec4 colorVarying;

void main()
{
    vec4 pos = ModelViewMatrix * Position;  // vertex position in eye coordinates

    // TODO: uncomment to assign normal value to color varying variable
    colorVarying = vec4(vec3(0.5) + Normal.xyz * 0.5, 1.0);
    
    gl_Position = ProjectionMatrix * pos;
}
