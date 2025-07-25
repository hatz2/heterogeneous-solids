// "Enums" for light type
const int ambient_light = 0;
const int point_light = 1;
const int directional_light = 2;
const int spot_light = 3;

uniform bool usePbr;
uniform bool useIbl;
uniform uint numLights;

uniform struct Light {
    int type;

    vec3 iA;
    vec3 iD;
    vec3 iS;

    vec3 position;
    vec3 direction;
    float spotAngle;
    bool shadow;
} lights[max_lights];

uniform sampler2D shadowMaps[max_lights];


vec3 defaultAmbientLight(Material material, Light light);
vec3 defaultPointLight(Material material, Light light);
vec3 defaultDirectionalLight(Material material, Light light);
vec3 defaultSpotLight(Material material, Light light);
vec3 iblAmbientLight(Material material);

vec3 pbrLighting(Material material);
vec3 defaultLighting(Material material);

float isPointInShadow(vec4 fragPosLightSpace, sampler2D shadowMap, Light light) {
    vec3 normal = normalize(normal);
    vec3 lightDir = normalize(-light.direction);
    // perspective division
    vec3 projectionCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // to [0, 1] range
    projectionCoords = projectionCoords * 0.5 + 0.5;

    if (projectionCoords.z > 1.0) {
        return 0.0;
    }

    float closestDepth = texture(shadowMap, projectionCoords.xy).r;
    float currentDepth = projectionCoords.z;

    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -2; x <= 2; ++x) {
        for(int y = -2; y <= 2; ++y) {
            float pcfDepth = texture(shadowMap, projectionCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
        }
    }
    shadow /= 25.0;

    return shadow;
}


vec3 toLinear(vec3 color) {
    return pow(color, vec3(2.2));
}


vec3 toSRGB(vec3 color) {
    return pow(color, vec3(1.0/2.2));
}


// Entry point lighting function
vec3 lightMethod(Material material) {
    if (usePbr)
        return pbrLighting(material);
    else
        return defaultLighting(material);
}


vec3 defaultLighting(Material material) {
    vec3 result = vec3(0, 0, 0);

    for (uint i = 0; i < numLights; ++i) {
        Light light = lights[i];

        if (light.type == ambient_light)
            result += defaultAmbientLight(material, light);

        else if (light.type == directional_light) {
            float isInShadow = 0.0;

            if (light.shadow) {
                isInShadow = isPointInShadow(lightSpacePositions[i], shadowMaps[i], light);
            }

            result += defaultDirectionalLight(material, light) * (1.0 - isInShadow);
        }

        else if (light.type == spot_light)
            result += defaultSpotLight(material, light);

        else if (light.type == point_light)
            result += defaultPointLight(material, light);

    }

    return result;
}


vec3 defaultAmbientLight(Material material, Light light) {
    return light.iA * material.kA;
}


vec3 defaultPointLight(Material material, Light light) {
    vec3 n = normalize(normal);

    vec3 l = normalize(light.position - position);
    vec3 v = normalize(-position);
    vec3 r = reflect(-l, n);

    vec3 diffuse = (light.iD * material.kD * max(dot(l,n), 0.0));
    vec3 specular = (light.iS * material.kS * pow(max(dot(r,v), 0.0), material.shininess));

    return diffuse + specular;
}


vec3 defaultDirectionalLight(Material material, Light light) {
    vec3 n = normalize(normal);

    vec3 l = normalize(-light.direction);
    vec3 v = normalize(-position);
    vec3 r = reflect(-l, n);

    vec3 diffuse = (light.iD * material.kD * max(dot(l,n), 0.0));
    vec3 specular = (light.iS * material.kS * pow(max(dot(r,v), 0.0), material.shininess));

    return diffuse + specular;
}


vec3 defaultSpotLight(Material material, Light light) {
    vec3 n = normalize(normal);

    vec3 l = normalize(light.position - position);
    vec3 v = normalize(-position);
    vec3 r = reflect(-l, n);

    vec3 diffuse = (light.iD * material.kD * max(dot(l,n), 0.0));
    vec3 specular = (light.iS * material.kS * pow(max(dot(r,v), 0.0), material.shininess));

    vec3 d = normalize(light.direction);
    float cosGamma = cos(light.spotAngle);
    float spotFactor = float(dot(-l, d) >= cosGamma);

    return spotFactor * (diffuse + specular);
}