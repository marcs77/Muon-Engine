#version 330 core
in vec3 pos;
in vec3 _col;
out vec4 color;

void main() {
    color = vec4(_col, 1.0);
}
