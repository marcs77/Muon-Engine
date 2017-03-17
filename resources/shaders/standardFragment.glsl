#version 330 core

in vec2 _uv;
in vec3 _normal;

out vec4 out_color;

uniform sampler2D diff0;
uniform sampler2D diff1;
uniform sampler2D diff2;
uniform sampler2D specular0;
uniform sampler2D specular1;
uniform sampler2D specular2;

void main() {
    out_color = texture(diff0, _uv);
}