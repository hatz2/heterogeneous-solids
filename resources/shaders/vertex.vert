#version 410

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

uniform float vertexRadius;

uniform vec3 cameraPosition;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

void main() {
    vec4 modelPosition = modelMatrix * vec4(vPosition, 1.0);
    vec3 cameraDistance = cameraPosition - vec3(modelPosition);

    vec3 offset = normalize(cameraDistance) * (smoothstep(0.01f, 5.f, length(cameraDistance)) * 0.2);
    gl_Position = projectionMatrix * viewMatrix * (modelPosition + vec4(offset, 0));

    float size = 1 - smoothstep(0.01f, 8.f * vertexRadius, length(cameraDistance));
    gl_PointSize = vertexRadius * 35 * smoothstep(0.5f, 1, size) * step(0.4f, pow(size, 2));
}