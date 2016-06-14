uniform highp vec4 EyePos;
uniform highp vec4 fogColor;
uniform highp vec4 LightPos;
uniform highp vec3 ScaleFactor;

uniform lowp vec3 Ka;   // ambient material coefficient
uniform lowp vec3 Kd;   // diffuse material coefficient
uniform lowp vec3 Ks;   // specular material coefficient

uniform mediump float Ns;   // specular material exponent (shininess)

uniform highp vec3 Ia;   // ambient light intensity
uniform highp vec3 Id;   // diffuse light intensity


varying highp float detailLevel;

uniform sampler2D DiffuseMap;
uniform sampler2D NormalMap;

varying highp vec4 texCoordVarying;
varying lowp vec4 ambientVarying;
varying lowp vec4 diffuseVarying;
varying lowp vec4 specularVarying;
varying highp vec4 posVarying;


varying mediump vec3 normalVarying;     // normal in world space
varying mediump vec3 tangentVarying;    // tangent in world space











void main() {
    
    
    
  highp float dist= length((EyePos-posVarying).xyz);
  highp float fogCo=1.0/(pow(2.71828,(dist*0.04)));
  
  highp vec4 color = texture2D(DiffuseMap, vec2(texCoordVarying.s * ScaleFactor.x, texCoordVarying.t*ScaleFactor.z));
  
    
    lowp vec4 ambientResult = vec4(Ka * Ia, 1.0);
    
    mediump vec4 pos = posVarying;
    mediump vec3 n = normalize(normalVarying);
    
    mediump vec3 t = normalize(tangentVarying);
    mediump vec3 b = normalize(cross(t,n));
    mediump mat3 tbn = mat3(t,b,n);
    
    mediump vec3 rgb = texture2D(NormalMap,vec2(texCoordVarying.s * ScaleFactor.x, texCoordVarying.t*ScaleFactor.z)).xyz;
    rgb = normalize(rgb * 2.0 - 1.0);
    
    n= normalize(tbn*rgb);
    
    
    mediump vec3 l = normalize(pos - pos).xyz;
    
    lowp float intensity = dot(n, l);
    lowp vec3 diffuse = Kd * clamp(intensity, 0.0, 1.0) * Id;
    lowp vec4 diffuseResult = vec4(clamp(diffuse, 0.0, 1.0), 1.0);
    
    lowp vec4 color2 =  (ambientResult + diffuseResult) * color;

    gl_FragColor = mix(fogColor,color2,fogCo);

}
