uniform samplerCube irradianceMap;
uniform samplerCube prefilteredMap;
uniform sampler2D brdfLUT;
uniform mat4 viewMatrix;

vec3 pbrAmbientLight(Material material, Light light);
vec3 pbrPointLight(Material material, Light light);
vec3 pbrDirectionalLight(Material material, Light light);
vec3 pbrSpotLight(Material material, Light light);


vec3 pbrLighting(Material material) {
    vec3 result = vec3(0, 0, 0);

    for (uint i = 0; i < numLights; ++i) {
        Light light = lights[i];

        if (light.type == directional_light)
            result += pbrDirectionalLight(material, light);

        else if (light.type == spot_light)
            result += pbrSpotLight(material, light);

        else if (light.type == point_light)
            result += pbrPointLight(material, light);
    }

    result += iblAmbientLight(material);

    result = result / (result + vec3(1.0));
    result = toSRGB(result);

    return result;
}

vec3 iblAmbientLight(Material material) {
    vec3 n = normalize(normal);
    vec3 v = normalize(-position);
    vec3 r = reflect(-v, n);
    r = mat3(inverse(viewMatrix)) * r;

    vec3 materialColor = toLinear(material.kD);
    float metallic = material.metallic;
    float roughness = material.roughness;

    vec3 f0 = vec3(0.04);
    f0 = mix(f0, materialColor, metallic);

    vec3 f = fresnelSchlickRoughness(max(dot(n, v), 0.0), f0, roughness);
    vec3 ks = f;
    vec3 kd = 1.0 - ks;
    kd *= 1.0 - metallic;

    vec3 irradiance = texture(irradianceMap, n).rgb;
    vec3 diffuse = irradiance * materialColor;

    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(prefilteredMap, r, roughness * MAX_REFLECTION_LOD).rgb;
    vec2 brdf = texture(brdfLUT, vec2(max(dot(n, v), 0.0), roughness)).rg;
    vec3 specular = prefilteredColor * (f * brdf.x + brdf.y);

    return (kd * diffuse + specular);
}

vec3 pbrAmbientLight(Material material, Light light) {
    return toLinear(light.iA) * toLinear(material.kA);
}


vec3 pbrPointLight(Material material, Light light) {
    vec3 n = normalize(normal);
    vec3 v = normalize(-position);
    vec3 l = normalize(light.position - position);
    vec3 h = normalize(v + l);

    float metallic = material.metallic;
    float roughness = material.roughness;
    vec3 materialColor = toLinear(material.kD);

    float distance = length(light.position - position);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = toLinear(light.iD) * attenuation;

    vec3 f0 = vec3(0.04);
    f0 = mix(f0, materialColor, metallic);

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
    float denominator = 4.0 * max(nDotV * nDotL, 0.0);
    vec3 specular = numerator / max(denominator, 0.0001);

    return (kd * materialColor / M_PI + specular) * radiance * nDotL;
}


vec3 pbrDirectionalLight(Material material, Light light) {
    vec3 n = normalize(normal);
    vec3 v = normalize(-position);
    vec3 l = normalize(-light.direction);
    vec3 h = normalize(v + l);

    float metallic = material.metallic;
    float roughness = material.roughness;
    vec3 materialColor = toLinear(material.kD);
    vec3 radiance = toLinear(light.iD);

    vec3 f0 = vec3(0.04);
    f0 = mix(f0, materialColor, metallic);

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
    float denominator = 4.0 * max(nDotV * nDotL, 0.0);
    vec3 specular = numerator / max(denominator, 0.0001);

    return (kd * materialColor / M_PI + specular) * radiance * nDotL;
}


vec3 pbrSpotLight(Material material, Light light) {
    vec3 n = normalize(normal);
    vec3 v = normalize(-position);
    vec3 l = normalize(light.position - position);
    vec3 h = normalize(v + l);

    vec3 lightDir = normalize(light.direction);
    float cosGamma = cos(light.spotAngle);
    float cosTheta = dot(-l, lightDir);

    if (cosTheta <= cosGamma) {
        return vec3(0.0);
    }

    float metallic = material.metallic;
    float roughness = material.roughness;
    vec3 materialColor = toLinear(material.kD);
    vec3 radiance = toLinear(light.iD);

    vec3 f0 = vec3(0.04);
    f0 = mix(f0, materialColor, metallic);

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
    float denominator = 4.0 * max(nDotV * nDotL, 0.0);
    vec3 specular = numerator / max(denominator, 0.0001);

    return (kd * materialColor / M_PI + specular) * radiance * nDotL;
}