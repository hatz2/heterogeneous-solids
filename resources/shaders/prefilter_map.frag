#version 410 core

in vec3 localPos;
layout (location = 0) out vec4 fragColor;

uniform samplerCube environmentMap;
uniform float roughness;
uniform float environmentMapResolution;

const float PI = 3.14159265359;

vec3 importanceSampleGGX(vec2 xi, vec3 n, float roughness);
float iblDistributionGGX(vec3 n, vec3 h, float roughness);
vec2 hammersley(uint i, uint N);

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
            float d = iblDistributionGGX(n, h, roughness);
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