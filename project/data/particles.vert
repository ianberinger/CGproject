 // Attributes
 attribute float a_pID;
 attribute float a_pRadiusOffset;
 attribute float a_pVelocityOffset;
 attribute float a_pDecayOffset;
 attribute float a_pSizeOffset;
 attribute vec3 a_pColorOffset;
 attribute vec4 a_position;

 
 // Uniforms
 uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ModelViewMatrix;
 uniform vec3 u_Gravity;
 uniform float u_Time;
 uniform float u_eRadius;
 uniform float u_eVelocity;
 uniform float u_eDecay;
 uniform float u_eSize;
 
 // Varying
 varying vec3        v_pColorOffset;
 
 void main(void)
{
    
    float x = cos(a_pID);
    float y = sin(a_pID);
    float r = u_eRadius * a_pRadiusOffset;
    
    
    
    // 2
    // Lifetime
    float growth = r / (u_eVelocity + a_pVelocityOffset);
    float decay = u_eDecay + a_pDecayOffset;
    
    // 3
    // If blast is growing
    if(u_Time < growth)
    {
        float time = u_Time / growth;
        x = x * r * time;
        y = y * r * time;
    }
    
    // 4
    // Else if blast is decaying
    else
    {
        float time = (u_Time - growth) / decay;
        x = (x * r) + (u_Gravity.x * time);
        y = (y * r) + (u_Gravity.y * time);
    }
    
    vec4 pos=u_ModelViewMatrix*vec4(164.0,1.0,16.0,1.0);

    // 5
    // Required OpenGLES 2.0 outputs
    gl_Position = u_ProjectionMatrix *pos;
    gl_PointSize = float(10);
    
    // Fragment Shader outputs
    v_pColorOffset = a_pColorOffset;
    
    
}