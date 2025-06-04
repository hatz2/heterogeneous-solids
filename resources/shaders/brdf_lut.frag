#version 410 core

in vec2 texCoords;
layout (location = 0) out vec2 fragColor;

vec2 hammersley(uint i, uint N);
float iblGeometrySmith(vec3 n, vec3 v, vec3 l, float roughness);
float iblGeometrySchlickGGX(vec3 n, vec3 v, vec3 l, float roughness);
vec3 importanceSampleGGX(vec2 xi, vec3 n, float roughness);

const float PI = 3.14159265359;

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
            float g = iblGeometrySmith(n, v, L, roughness);
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