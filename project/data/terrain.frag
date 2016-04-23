
// TODO: create varying variable to receive color values from the vertex shader, don't forget to specify precision
uniform mediump vec4 EyePos;


varying lowp vec4 colorVarying;
varying mediump vec4 posVarying; 

void main()
{
    // TODO: change output color
    mediump float dist= length((EyePos-posVarying).xyz);
    
    mediump float fogCo=1.0/(pow(2.71828,(dist*0.05)));
    mediump vec4 fogC= vec4(0.5, 0.5, 0.5, 1);
    
    gl_FragColor = mix(fogC,colorVarying,fogCo);
}
