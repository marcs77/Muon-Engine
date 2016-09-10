#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in int tid;
layout (location = 3) in vec4 color;

out DATA 
{
	vec3 pos;
	vec2 uv;
	vec4 col;
	vec4 wpos;
	float tid;
} v_out;


uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

void main() 
{
	v_out.wpos = ml_matrix * position;

	gl_Position =  pr_matrix * vw_matrix * v_out.wpos;
	v_out.pos = position.xyz;
	v_out.col = color;
	v_out.uv = uv;
	v_out.tid = tid;
}