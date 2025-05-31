#version 410 core

in vec2 texCoords;
layout (location = 0) out vec2 fragColor;

const float PI = 3.14159265359;

float radicalInverseVdc(uint bits);
vec2 hammersley(uint i, uint N);
vec3 importanceSampleGGX(vec2 xi, vec3 n, float roughness);
float geometrySchlickGGX(float nDotV, float roughness);
float geometrySmith(vec3 n, vec3 v, vec3 l, float roughness);

vec2 integrateBRDF(float nDotV, float roughness)
{
    vec3 v;
    v.x = sqrt(1.0 - nDotV*nDotV);
    v.y = 0.0;
    v.z = nDotV;

    float a = 0.0;
    float b = 0.0;

    vec3 n = vec3(0.0, 0.0, 1.0);

    const uint SAMPLE_COUNT = 1024;
    for(uint i = 0u; i < SAMPLE_COUNT; ++i)
    {
        vec2 xi = hammersley(i, SAMPLE_COUNT);
        vec3 h  = importanceSampleGGX(xi, n, roughness);
        vec3 L  = normalize(2.0 * dot(v, h) * h - v);

        float nDotL = max(L.z, 0.0);
        float nDotH = max(h.z, 0.0);
        float vDotH = max(dot(v, h), 0.0);

        if(nDotL > 0.0)
        {
            float g = geometrySmith(n, v, L, roughness);
            float gVis = (g * vDotH) / (nDotH * nDotV);
            float fc = pow(1.0 - vDotH, 5.0);

            a += (1.0 - fc) * gVis;
            b += fc * gVis;
        }
    }
    a /= float(SAMPLE_COUNT);
    b /= float(SAMPLE_COUNT);
    return vec2(a, b);
}

void main()
{
    fragColor = integrateBRDF(texCoords.x, texCoords.y);
}

float radicalInverseVdc(uint bits)
{
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

vec2 hammersley(uint i, uint N)
{
    return vec2(float(i)/float(N), radicalInverseVdc(i));
}

vec3 importanceSampleGGX(vec2 xi, vec3 n, float roughness)
{
    float a = roughness*roughness;

    float phi = 2.0 * PI * xi.x;
    float cosTheta = sqrt((1.0 - xi.y) / (1.0 + (a*a - 1.0) * xi.y));
    float sinTheta = sqrt(1.0 - cosTheta*cosTheta);

    // spherical to cartesian
    vec3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;

    // tangent-space to world-space
    vec3 up        = abs(n.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
    vec3 tangent   = normalize(cross(up, n));
    vec3 bitangent = cross(n, tangent);

    vec3 sampleVec = tangent * H.x + bitangent * H.y + n * H.z;
    return normalize(sampleVec);
}

float geometrySchlickGGX(float nDotV, float roughness) {
    float a = roughness;
    float k = (a * a) / 2.0;

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