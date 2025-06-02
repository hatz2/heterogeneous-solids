vec3 fresnelSchlick(float cosTheta, vec3 f0) {
    return f0 + (1.0 - f0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 f0, float roughness) {
    return f0 + (max(vec3(1.0 - roughness), f0) - f0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
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
    float k = (r * r) / 8.0; // PBR term

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