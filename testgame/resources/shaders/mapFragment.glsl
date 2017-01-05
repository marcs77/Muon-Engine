#version 330 core
in vec3 worldPos;
in vec3 cmPos;
out vec4 color;

uniform vec4 base_color = vec4(1.0, 1.0, 1.0, 1.0);
uniform float colorDivisions = 30.0;
uniform float mapScroll = 0.0;

const float maxDistance = 520.0;
const vec4 fogColor = vec4(0.0, 0.0, 0.0, 1.0);

void main() {
    float dist = worldPos.z - mapScroll;
    color = mix(base_color, fogColor, (ceil(dist) - ceil(cmPos.z - mapScroll))/colorDivisions);
}
