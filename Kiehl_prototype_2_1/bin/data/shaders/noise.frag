#version 120

uniform sampler2DRect tex0;
uniform vec2 mouse;
uniform float radius;
varying vec2 texCoordVarying;

void main()
{
    vec4 texel0 = texture2DRect(tex0, texCoordVarying);
    
    vec4 color = texel0;
    vec2 d = texCoordVarying - mouse;
	float len =  sqrt(d.x*d.x + d.y*d.y);
    
    // radius of brightness
    float innerRadius = 300.0;
    float outerRadius = 1000.0;
    float pct = 1.0;
    if (len < innerRadius){
        pct = 1.0;
    } else if (len < outerRadius){
        pct = 1.0 - (len-innerRadius) / (outerRadius - innerRadius);
    } else {
        pct = 0.0;
    }
    
    float scale = pct * 1.2;
    
    color.rgb *=  (scale);
    
    gl_FragColor = vec4(color.rgb, 1.0);

    
}