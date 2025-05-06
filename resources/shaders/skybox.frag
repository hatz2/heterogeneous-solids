#version 410

in vec3 texCoords;

uniform samplerCube cubemap;

layout (location = 0) out vec4 fragColor;

void main() {
    fragColor = texture(cubemap, texCoords);
}