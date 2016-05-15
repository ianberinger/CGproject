
// TODO: create varying variable to receive color values from the vertex shader, don't forget to specify precision
uniform mediump vec4 EyePos;
uniform mediump vec4 fogColor;

varying mediump vec4 posVarying;

void main()
{
    // other color variation
    //mediump vec4 bottom = vec4(0.607, 0.892, 0.949, 1.0);
    //mediump vec4 top = vec4(0.121, 0.572, 0.794, 1.0);
    mediump vec4 bottom = vec4(0.99, 0.95, 0.69, 0.5);
    mediump vec4 top = vec4(0.18, 0.59, 0.72, 1.0);
    
    mediump float co = abs(posVarying.y+0.01)*10.0;
    
    gl_FragColor = mix(bottom, top, co);
}
