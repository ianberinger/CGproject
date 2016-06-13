uniform highp vec4 EyePos;
uniform highp vec4 fogColor;
uniform highp vec4 LightPos;
uniform highp vec3 ScaleFactor;

varying highp float detailLevel;

uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;

varying highp vec4 posVarying;
varying highp vec4 texCoordVarying;

void main() {
  highp float dist= length((EyePos-posVarying).xyz);
  highp float fogCo=1.0/(pow(2.71828,(dist*0.05)));
  
  highp vec4 color = texture2D(DiffuseMap, vec2(texCoordVarying.s * ScaleFactor.x, texCoordVarying.t*ScaleFactor.z));
  
  gl_FragColor = mix(fogColor,color,fogCo);
}
