uniform mediump vec4 EyePos;
uniform mediump vec4 fogColor;
uniform bool ghost;

uniform lowp float ShadowStrength;

varying mediump vec4 posVarying;
varying lowp vec4 texCoordVarying;


void main()
{
  // TODO: change output color
  mediump float dist= length((EyePos-posVarying).xyz);
  mediump float fogCo=1.0/(pow(2.71828,(dist*0.05)));
  
  lowp vec4 color = vec4(0.2, 0.2, 0.2, ShadowStrength);
  
  gl_FragColor = color;
}
