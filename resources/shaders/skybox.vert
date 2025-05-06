#version 410

layout (location = 0) in vec3 vPosition;

out vec3 texCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main() {
    texCoords = vPosition;
    gl_Position = projectionMatrix * viewMatrix * vec4(vPosition, 1.0);
}