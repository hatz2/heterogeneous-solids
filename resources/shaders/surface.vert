#version 410

const int max_lights = 8;

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vUVW;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;

uniform uint numLights;
uniform mat4 lightSpaceMatrices[max_lights];

out vec4 lightSpacePositions[max_lights];
out vec3 position;
out vec3 normal;
out vec3 uvw;

void main() {
    mat4 mvMatrix = viewMatrix * modelMatrix;

    position = vec3(mvMatrix * vec4(vPosition, 1.0));
    normal = vec3(mvMatrix * vec4(vNormal, 0.0));
    uvw = vUVW;

    for (int i = 0; i < numLights; ++i) {
        vec3 worldPos = vec3(modelMatrix * vec4(vPosition, 1.0));
        lightSpacePositions[i] = lightSpaceMatrices[i] * vec4(worldPos, 1.0);
    }

    gl_Position = projectionMatrix * vec4(position, 1.0);
}