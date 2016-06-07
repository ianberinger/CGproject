uniform mediump vec4 EyePos;
uniform mediump vec4 fogColor;
uniform mediump vec4 LightPos;

uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;

varying mediump float detailLevel;
varying mediump vec4 posVarying;
varying lowp vec4 texCoordVarying;

void main()
{
  mediump float dist= length((EyePos-posVarying).xyz);
  mediump float fogCo=1.0/(pow(2.71828,(dist*0.05)));
  
  mediump vec3 normal = texture2D(NormalMap, texCoordVarying.st).xyz;
  mediump vec3 n = normalize(normal * 2.0 - 1.0);
  
  mediump vec3 l = normalize(LightPos - posVarying).xyz;
  
  lowp vec4 color = texture2D(DiffuseMap, vec2(detailLevel, dot(n,l)));

  gl_FragColor = mix(fogColor,color,fogCo);
}
