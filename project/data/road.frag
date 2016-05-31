uniform mediump vec4 EyePos;
uniform mediump vec4 fogColor;
uniform mediump vec4 LightPos;
uniform mediump vec3 ScaleFactor;

uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;

varying mediump vec4 posVarying;
varying lowp vec4 texCoordVarying;

void main() {
  mediump float dist= length((EyePos-posVarying).xyz);
  mediump float fogCo=1.0/(pow(2.71828,(dist*0.05)));
  
  mediump vec3 normal = texture2D(NormalMap, vec2(texCoordVarying.s, texCoordVarying.t*ScaleFactor.z)).xyz;
  mediump vec3 n = normalize(normal * 2.0 - 1.0);
  
  mediump vec3 l = normalize(LightPos - posVarying).xyz;
  mediump vec3 eyeVec = normalize(EyePos.xyz - posVarying.xyz);
  
  mediump vec3 r = l - 2.0 * dot(l,n) * n;
  
  lowp float detailLevel = length(dot(eyeVec, r));
  
  lowp vec4 color = texture2D(DiffuseMap, detailLevel * texCoordVarying.st);
  
  gl_FragColor = mix(fogColor,color,fogCo);
}
