#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 pr_matrix = mat4(1.0);
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

uniform vec3 camPos;

out vec3 worldPos;
out vec3 cmPos;

void main() {
    cmPos = camPos;
    worldPos = (ml_matrix * vec4(position, 1.0)).xyz;
    gl_Position = pr_matrix * vw_matrix * vec4(worldPos,1.0);
}
