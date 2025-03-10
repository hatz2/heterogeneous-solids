#version 410

layout (location = 0) in vec3 vPosition;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main() {
    mat4 mvMatrix = viewMatrix * modelMatrix;

    gl_Position = projectionMatrix * mvMatrix * vec4(vPosition, 1.0);
}