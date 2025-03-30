
vec3 pbrPointLight(Material material);
vec3 pbrDirectionalLight(Material material);
vec3 pbrSpotLight(Material material);

vec3 pbrPointLight(Material material) {
    return vec3(1, 0, 0);
}
vec3 pbrDirectionalLight(Material material) {
    return vec3(0, 1, 0);
}
vec3 pbrSpotLight(Material material) {
    return vec3(0, 0, 1);
}