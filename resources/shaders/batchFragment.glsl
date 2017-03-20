#version 330 core

in DATA
{
	//vec3 pos;
	vec2 uv;
	vec4 col;
	flat int tid;
}f_in;

uniform sampler2D tex[32];

out vec4 color;

void main()
{

	if(f_in.tid >= 0)
	{
		color = f_in.col * texture(tex[f_in.tid], f_in.uv);
	} else 
	{
		color = f_in.col;
	}

	//color = texture(tex[0], f_in.uv);
	//color = f_in.col;
}