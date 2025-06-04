#version 410

layout (location = 0) in vec3 vPosition;

out vec3 texCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main() {
    texCoords = vPosition;
    mat4 viewMat = mat4(mat3(viewMatrix)); // remove translation
    vec4 pos = projectionMatrix * viewMat * vec4(vPosition, 1.0);
    gl_Position = pos.xyww;
}