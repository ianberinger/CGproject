uniform mediump vec4 EyePos;
uniform mediump vec4 fogColor;
uniform mediump vec4 LightPos;
uniform mediump mat4 LightSpaceMatrix;

uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;
uniform sampler2D DepthMap;

uniform lowp float RenderMode;

varying mediump float detailLevel;
varying mediump vec4 posVarying;
varying lowp vec4 texCoordVarying;
varying mediump vec4 fragPosLightSpace;

void main()
{
  if (RenderMode < 1.0) {
    mediump float dist= length((EyePos-posVarying).xyz);
    mediump float fogCo=1.0/(pow(2.71828,(dist*0.05)));
    
    mediump vec3 normal = texture2D(NormalMap, texCoordVarying.st).xyz;
    mediump vec3 n = normalize(normal * 2.0 - 1.0);
    
    mediump vec3 l = normalize(LightPos - posVarying).xyz;
    
    lowp vec4 color = texture2D(DiffuseMap, vec2(detailLevel, dot(n,l)));
    
    //shadow
    lowp vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    lowp float closestDepth = texture2D(DepthMap, projCoords.xy).r;
    lowp float currentDepth = projCoords.z;
    lowp float shadow = currentDepth > closestDepth ? 1.0 : 0.0;
    
    gl_FragColor = texture2D(DepthMap, texCoordVarying.st);
  } else {
    gl_FragDepthEXT = 0.9;
  }
}
