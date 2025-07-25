#version 410

#define M_PI 3.1415926535897932384626433832795

const int max_lights = 8;

in vec4 lightSpacePositions[max_lights];
in vec3 position;
in vec3 normal;
in vec3 uvw;

uniform struct Material {
    vec3 kA;
    vec3 kD;
    vec3 kS;

    float shininess;
    float roughness;
    float metallic;
} materials[2];

layout (location = 0) out vec4 fragColor;

//subroutine vec3 LightMethod(Material material);
//subroutine uniform LightMethod lightMethod;
subroutine Material SelectMaterial();
subroutine uniform SelectMaterial selectMaterial;

vec3 lightMethod(Material material);

void main() {
    Material material = selectMaterial();
    fragColor = vec4(lightMethod(material), 1);
}