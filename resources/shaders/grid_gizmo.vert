#version 410

layout (location = 0) in vec2 point;

uniform vec3 cameraPosition;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 position;

void main() {
    position = vec3(
        cameraPosition.x - mod(cameraPosition.x, 4) + point.x,
        0,
        cameraPosition.z - mod(cameraPosition.z, 4) + point.y
    );

    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1);
}