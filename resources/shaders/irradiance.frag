#version 410 core

in vec3 localPos;
uniform samplerCube cubeMap;
layout (location = 0) out vec4 fragColor;

const float PI = 3.14159265359;
const float SAMPLE_DELTA = 0.025;

vec3 convolution(vec3 normal)
{
    vec3 irradiance = vec3(0.0);

    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 right = normalize(cross(up, normal));
    up = normalize(cross(normal, right));

    float numSamples = 0.0;

    for (float phi = 0.0; phi < 2.0 * PI; phi += SAMPLE_DELTA)
    {
        for (float theta = 0.0; theta < 0.5 * PI; theta += SAMPLE_DELTA)
        {
            // Spherical coord to cartesian (in tangent space)
            vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
            // Tangent coord to world coord
            vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * normal;

            vec3 texColor = texture(cubeMap, sampleVec).rgb;

            irradiance +=  texColor * cos(theta) * sin(theta);
            ++numSamples;
        }
    }

    irradiance = PI * irradiance * (1 / numSamples);

    return irradiance;
}

void main()
{
    vec3 normal = normalize(localPos);
    vec3 irradiance = convolution(normal);
    fragColor = vec4(irradiance, 1.0);
}