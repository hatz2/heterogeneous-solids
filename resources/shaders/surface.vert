#version 410

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vUVW;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

out vec3 position;
out vec3 normal;
out vec3 uvw;

void main() {
    mat4 mvMatrix = viewMatrix * modelMatrix;

    position = vec3(mvMatrix * vec4(vPosition, 1.0));
    normal = vec3(mvMatrix * vec4(vNormal, 0.0));
    uvw = vUVW;

    gl_Position = projectionMatrix * mvMatrix * vec4(vPosition, 1.0);
}