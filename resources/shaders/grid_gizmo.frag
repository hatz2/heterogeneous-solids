#version 410

in vec3 position;
uniform vec3 cameraPosition;

out vec4 fragColor;

void main() {
    bool isX = abs(position.x) < 0.01;
    bool isZ = abs(position.z) < 0.01;
    vec3 refCamera = vec3(cameraPosition.x, 0, cameraPosition.z);
    float visibility = 1 - smoothstep(16, 80, distance(position, refCamera));
    fragColor = vec4(0.2 + (0.8 * float(isX)), 0.2, 0.2 + (0.8 * float(isZ)), visibility);
}