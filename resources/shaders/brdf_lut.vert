#version 410 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vUVW;

out vec2 texCoords;

void main() {
    texCoords = vec2(vUVW);
    gl_Position = vec4(vPosition, 1.0);
}