
// TODO: create varying variable to receive color values from the vertex shader, don't forget to specify precision
uniform mediump vec4 EyePos;
uniform mediump vec4 fogColor;

varying lowp vec4 colorVarying;
varying mediump vec4 posVarying; 

void main()
{
    // TODO: change output color
    mediump float dist= length((EyePos-posVarying).xyz);    
    mediump float fogCo=1.0/(pow(2.71828,(dist*0.05)));
    
    gl_FragColor = mix(fogColor,colorVarying,fogCo);
}
