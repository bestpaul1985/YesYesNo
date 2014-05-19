


void main(void)
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
    //gl_Position.wxyz = vec4(0.0, gl_Position.xyz);
    //gl_Position.z *= 1.2;
}