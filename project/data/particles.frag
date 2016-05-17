 // Varying
 varying highp vec3      v_pColorOffset;
 
 // Uniforms
 uniform highp float     u_Time;
 uniform highp vec3      u_eColor;
 
 void main(void)
{
    // Color
    highp vec4 color = vec4(1.0);
    color.rgb = u_eColor + v_pColorOffset;
    color.rgb = clamp(color.rgb, vec3(0.0), vec3(1.0));
    
    // Required OpenGL ES 2.0 outputs
    gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}