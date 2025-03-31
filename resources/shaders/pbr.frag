
vec3 fresnelSchlick(float cosTheta, vec3 f0) {
    return f0 + (1.0 - f0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}


float distributionGGX(vec3 n, vec3 h, float roughness) {
    float a = roughness * roughness; // a = alpha so roughness is elevated by 2 here
    float a2 = a * a;
    float nDotH = max(dot(n, h), 0.0);
    float nDotH2 = nDotH * nDotH;

    float numerator = a2;
    float denominator = (nDotH2 * (a2 - 1.0) + 1.0);
    denominator = M_PI * denominator * denominator;

    return numerator / denominator;
}



float geometrySchlickGGX(float nDotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0; // TODO: Remapping for IBL

    float numerator = nDotV;
    float denominator = nDotV * (1.0 - k ) + k;

    return numerator / denominator;
}


float geometrySmith(vec3 n, vec3 v, vec3 l, float roughness) {
    float nDotV = max(dot(n, v), 0.0);
    float nDotL = max(dot(n, l), 0.0);
    float ggx1 = geometrySchlickGGX(nDotV, roughness);
    float ggx2 = geometrySchlickGGX(nDotL, roughness);

    return ggx1 * ggx2;
}


vec3 pbrPointLight(Material material) {
    return vec3(1, 0, 0);
}


vec3 pbrDirectionalLight(Material material) {
    vec3 n = normalize(normal);
    vec3 v = normalize(-position);
    vec3 l = normalize(-light.direction);
    vec3 h = normalize(v + l);

    float metallic = material.metallic;
    float roughness = material.roughness;

    vec3 f0 = vec3(0.04);
    f0 = mix(f0, material.kD, metallic);

    vec3 Lo = vec3(0.0);

    vec3 radiance = light.iD;

    // cook-torrance
    float d = distributionGGX(n, h, roughness);
    float g = geometrySmith(n, v, l, roughness);
    vec3 f = fresnelSchlick(max(dot(h, v), 0.0), f0);

    vec3 ks = f;
    vec3 kd = vec3(1.0) - ks;
    kd *= 1.0 - metallic;

    float nDotL = max(dot(n, l), 0.0);
    float nDotV = max(dot(n, v), 0.0);

    vec3 numerator = d * g * f;
    float denominator = 4.0 * max(nDotV * nDotL, 0.0) + 0.0001;
    vec3 specular = numerator / denominator;

    Lo += (kd * material.kD / M_PI + specular) * radiance * nDotL;

    vec3 color = Lo;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0 / 2.2));
    return color;
}


vec3 pbrSpotLight(Material material) {
    return vec3(0, 0, 1);
}