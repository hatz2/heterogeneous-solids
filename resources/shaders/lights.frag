uniform struct Light {
    vec3 iA;
    vec3 iD;
    vec3 iS;

    vec3 position;
    vec3 direction;
    float spotAngle;
} light;

uniform bool usePbr;

vec3 defaultPointLight(Material material);
vec3 defaultDirectionalLight(Material material);
vec3 defaultSpotLight(Material material);


subroutine(LightMethod)
vec3 ambientLight(Material material) {
    return light.iA * material.kA;
}


subroutine(LightMethod)
vec3 pointLight(Material material) {
    if (usePbr) {
        return pbrPointLight(material);
    }
    
    return defaultPointLight(material);
}


subroutine(LightMethod)
vec3 directionalLight(Material material) {
    if (usePbr) {
        return pbrDirectionalLight(material);
    }

    return defaultDirectionalLight(material);
}


subroutine(LightMethod)
vec3 spotLight(Material material) {
    if (usePbr) {
        return pbrSpotLight(material);
    }

    return defaultSpotLight(material);
}


vec3 defaultPointLight(Material material) {
    vec3 n = normalize(normal);

    vec3 l = normalize(light.position - position);
    vec3 v = normalize(-position);
    vec3 r = reflect(-l, n);

    vec3 diffuse = (light.iD * material.kD * max(dot(l,n), 0.0));
    vec3 specular = (light.iS * material.kS * pow(max(dot(r,v), 0.0), material.shininess));

    return diffuse + specular;
}


vec3 defaultDirectionalLight(Material material) {
    vec3 n = normalize(normal);

    vec3 l = normalize(-light.direction);
    vec3 v = normalize(-position);
    vec3 r = reflect(-l, n);

    vec3 diffuse = (light.iD * material.kD * max(dot(l,n), 0.0));
    vec3 specular = (light.iS * material.kS * pow(max(dot(r,v), 0.0), material.shininess));

    return diffuse + specular;
}


vec3 defaultSpotLight(Material material) {
    vec3 n = normalize(normal);

    vec3 l = normalize(light.position - position);
    vec3 v = normalize(-position);
    vec3 r = reflect(-l, n);

    vec3 diffuse = (light.iD * material.kD * max(dot(l,n), 0.0));
    vec3 specular = (light.iS * material.kS * pow(max(dot(r,v), 0.0), material.shininess));

    vec3 d = normalize(light.direction);
    float cosGamma = cos(light.spotAngle);
    float spotFactor = float(cos(dot(-l, d)) >= cosGamma);

    return spotFactor * (diffuse + specular);
}