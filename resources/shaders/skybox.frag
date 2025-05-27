#version 410

in vec3 texCoords;

uniform samplerCube environmentMap;

layout (location = 0) out vec4 fragColor;

void main() {
    vec3 color = texture(environmentMap, texCoords).rgb;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));
    fragColor = vec4(color, 1.0);
}