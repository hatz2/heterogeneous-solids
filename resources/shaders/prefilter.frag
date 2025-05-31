#version 410 core

in vec3 localPos;
layout (location = 0) out vec4 fragColor;

uniform samplerCube environmentMap;
uniform float roughness;
uniform float environmentMapResolution;

const float PI = 3.14159265359;

float radicalInverseVdc(uint bits);
vec2 hammersley(uint i, uint N);
vec3 importanceSampleGGX(vec2 xi, vec3 n, float roughness);
float distributionGGX(vec3 n, vec3 h, float roughness);

void main()
{
    vec3 n = normalize(localPos);
    vec3 r = n;
    vec3 v = r;

    const uint SAMPLE_COUNT = 1024;
    float totalWeight = 0.0;
    vec3 prefilteredColor = vec3(0.0);
    for(uint i = 0; i < SAMPLE_COUNT; ++i)
    {
        vec2 xi = hammersley(i, SAMPLE_COUNT);
        vec3 h  = importanceSampleGGX(xi, n, roughness);
        vec3 L  = normalize(2.0 * dot(v, h) * h - v);

        float nDotL = max(dot(n, L), 0.0);
        if(nDotL > 0.0)
        {
            float d = distributionGGX(n, h, roughness);
            float nDotH = max(dot(n, h), 0.0);
            float hDotV = max(dot(h, v), 0.0);
            float pdf = d * nDotH / (4.0 * hDotV) + 0.0001;

            float resolution = environmentMapResolution;
            float saTexel  = 4.0 * PI / (6.0 * resolution * resolution);
            float saSample = 1.0 / (float(SAMPLE_COUNT) * pdf + 0.0001);
            float mipLevel = roughness == 0.0 ? 0.0 : 0.5 * log2(saSample / saTexel);

            prefilteredColor += textureLod(environmentMap, L, mipLevel).rgb * nDotL;
            totalWeight      += nDotL;
        }
    }
    prefilteredColor = prefilteredColor / totalWeight;

    fragColor = vec4(prefilteredColor, 1.0);
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
// ----------------------------------------------------------------------------
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

    // from spherical coordinates to cartesian coordinates
    vec3 H;
    H.x = cos(phi) * sinTheta;
    H.y = sin(phi) * sinTheta;
    H.z = cosTheta;

    // from tangent-space vector to world-space sample vector
    vec3 up        = abs(n.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
    vec3 tangent   = normalize(cross(up, n));
    vec3 bitangent = cross(n, tangent);

    vec3 sampleVec = tangent * H.x + bitangent * H.y + n * H.z;
    return normalize(sampleVec);
}

float distributionGGX(vec3 n, vec3 h, float roughness) {
    float a = roughness * roughness; // a = alpha so roughness is elevated by 2 here
    float a2 = a * a;
    float nDotH = max(dot(n, h), 0.0);
    float nDotH2 = nDotH * nDotH;

    float numerator = a2;
    float denominator = (nDotH2 * (a2 - 1.0) + 1.0);
    denominator = PI * denominator * denominator;

    return numerator / denominator;
}