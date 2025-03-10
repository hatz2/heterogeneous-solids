#version 400

layout (location = 0) out vec4 fragColor;

uniform vec4 solidColor;

void main() {
    fragColor = solidColor;
}