#version 330 core

in vec3 _col;

out vec4 out_color;

uniform vec4 baseColor = vec4(1,0,0,1);

void main() {
	out_color = vec4(_col, 1);
}