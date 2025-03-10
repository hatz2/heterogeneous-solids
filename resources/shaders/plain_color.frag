#version 410

layout (location = 0) out vec4 fragColor;

uniform vec3 solidColor;

void main() {
    fragColor = vec4(solidColor, 1);
}