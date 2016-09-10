#version 330 core

in DATA 
{
	vec3 pos;
	vec2 uv;
	vec4 col;
	vec4 wpos;
	float tid;
} f_in;

uniform vec2 lightpos;
uniform sampler2D tex[32];

out vec4 color;

void main() {
	//vec3 p = f_in.pos+vec3(0.5, 0.5, 0.5);
	vec4 basecolor = f_in.col;
	float intensity = 1.0 / length(f_in.wpos.xy - lightpos.xy);
	
	intensity = 1.0;

	if(f_in.tid >= 0.0) {
		color = basecolor * texture(tex[int(f_in.tid)], f_in.uv) * intensity;
	}else {
		color = basecolor * intensity;
	}

	//color = vec4(f_in.tid,f_in.tid,f_in.tid,1);
}