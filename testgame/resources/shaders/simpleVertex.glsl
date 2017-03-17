#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out vec2 _uv;
out vec3 _normal;

void main() {
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(position, 1);
	_uv = uv;
	_normal = normal;
}
