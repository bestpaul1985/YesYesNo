

void main(void)
{
    
	gl_TexCoord[0] = gl_MultiTexCoord0;
    
   
	gl_Position = modelViewProjectionMatrix * gl_Position;
    //gl_Position.z = 0.0;
    //gl_Position.wxyz = vec4(0.0, gl_Position.xyz);
    //gl_Position.z *= 1.2;
}