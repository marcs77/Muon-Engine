#version 330 core

in vec2 _uv;
in vec3 _normal;

out vec4 out_color;

uniform sampler2D tex;

void main() {
    out_color = texture(tex, _uv);
}
