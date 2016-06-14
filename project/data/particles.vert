 // Attributes
 attribute float a_pID;
 attribute float a_pRadiusOffset;
 attribute float a_pVelocityOffset;
 attribute float a_pDecayOffset;
 attribute float a_pSizeOffset;
 attribute vec3 a_pColorOffset;

 
 // Uniforms
 uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ModelViewMatrix;
 uniform vec3 u_Gravity;
 uniform float u_Time;
uniform float u_Life;
 uniform float u_eRadius;
 uniform float u_eVelocity;
 uniform float u_eDecay;
 uniform float u_eSize;
 uniform vec4 u_position;

 
 // Varying
 varying vec3        v_pColorOffset;
 
 void main(void)
{
    
    float x = cos(a_pID);
    float y = sin(a_pID);
    float z = a_pID/1800.0;
    float r = u_eRadius;
    
    
    
    // 2
    // Lifetime
    float growth = r / (u_eVelocity + a_pVelocityOffset);
    float decay = u_eDecay + a_pDecayOffset;
    r=0.075;
    
    
    // 3
    // If blast is growing
   
        float time = u_Time / growth;
        x = x * r * time;
        y = y * r * time;
        z = z + time *0.05;


//    vec4 pos=u_ModelViewMatrix*vec4(164.0+x,1.0+y,16.0,1.0);
    vec4 pos=u_ModelViewMatrix*vec4(x,1.5+y,5.5+z,1.0);

    // 5
    // Required OpenGLES 2.0 outputs
    gl_Position = u_ProjectionMatrix *pos;
    gl_PointSize = 0.75;
    
    // Fragment Shader outputs
    v_pColorOffset = a_pColorOffset;
    
    
}