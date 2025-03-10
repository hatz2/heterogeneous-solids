uniform struct CellData {
    float[64] a0;
    vec3[64] p;

    ivec3 perlinPeriod;
} cellData;

#define MAX_FEATURE_POINTS 10

uniform struct CompositeMaterial {
    float minValue;
    float maxValue;

    vec4 coefs;

    vec3 points[MAX_FEATURE_POINTS];
    int pointCount;
    bool is2D; // TODO: use it
} compositeMaterial;

uniform struct MaterialCoef {
    float a0;
    vec3 p;
};

float B(int i, float t) {
    switch (i) {
        case 0: return pow(1.0 - t, 3.0);
        case 1: return 3.0 * (pow(1.0 - t, 2.0)) * t;
        case 2: return 3.0 * pow(t, 2.0) * (1.0 - t);
        case 3: return pow(t, 3.0);
        default: return 0.0;
    }
}

float BD(int i, float t) {
    switch (i) {
        case 0: return -3.0 * pow(1.0 - t, 2.0);
        case 1: return (3.0 * pow(1.0 - t, 2.0)) - (6.0 * (1.0 - t) * t);
        case 2: return (6.0 * (1.0 - t) * t) - (3.0 * pow(t, 2.0));
        case 3: return 3.0 * pow(t, 2.0);
        default: return 0.0;
    }
}

MaterialCoef calculateMaterialCoef() {
    MaterialCoef materialCoef;
    materialCoef.a0 = 0;
    materialCoef.p = vec3(0);

    for (int i = 0; i <= 3; i++) {
        float bi = B(i, uvw.x);
        int ii = i*16;
        for (int j = 0; j <= 3; j++) {
            float bj = B(j, uvw.y);
            int jj = j*4;
            for (int k = 0; k <= 3; k++) {
                float bk = B(k, uvw.z);
                int idx = ii + jj + k;
                materialCoef.a0 += bi * bj * bk * cellData.a0[idx];
                materialCoef.p += bi * bj * bk * cellData.p[idx];
            }
        }
    }

    materialCoef.p = round(materialCoef.p);

    return materialCoef;
}

subroutine(SelectMaterial)
Material selectPrimaryMaterial() {
    return materials[0];
}

subroutine(SelectMaterial)
Material selectContinuousMaterial() {
    MaterialCoef materialCoef = calculateMaterialCoef();
    Material material;
    material.kA = mix(materials[0].kA, materials[1].kA, materialCoef.a0);
    material.kD = mix(materials[0].kD, materials[1].kD, materialCoef.a0);
    material.kS = mix(materials[0].kS, materials[1].kS, materialCoef.a0);
    material.shininess = mix(materials[0].shininess, materials[1].shininess, materialCoef.a0);
    return material;
}

subroutine(SelectMaterial)
Material selectFunctionallyGradedMaterial() {
    MaterialCoef materialCoef = calculateMaterialCoef();
    float r = perlinNoise(uvw, cellData.perlinPeriod);
    return materials[int(step(r, materialCoef.a0))];
}

subroutine(SelectMaterial)
Material selectCompositeMaterial() {
    MaterialCoef materialCoef = calculateMaterialCoef();
    float F1 = 1000.0, F2 = 1000.0, F3 = 1000.0, F4 = 1000.0;

    // TODO: handle 2D composite

    for (int i = 0; i < compositeMaterial.pointCount; i++) {
        float u = fract(uvw.x * materialCoef.p.x); u = u - floor(u);
        float v = fract(uvw.y * materialCoef.p.y); v = v - floor(v);
        float w = fract(uvw.z * materialCoef.p.z); w = w - floor(w);
        float d = distance(vec3(u, v, w), compositeMaterial.points[i]);
        if (d < F1) {
            F4 = F3;
            F3 = F2;
            F2 = F1;
            F1 = d;
        } else if (d < F2) {
            F4 = F3;
            F3 = F2;
            F2 = d;
        } else if (d < F3) {
            F4 = F3;
            F3 = d;
        } else if (d < F4) {
            F4 = d;
        }
    }

    float F = compositeMaterial.coefs.x * F1 + compositeMaterial.coefs.y * F2 +
        compositeMaterial.coefs.z * F3 + compositeMaterial.coefs.w * F4;
    F = (F - compositeMaterial.minValue) / (compositeMaterial.maxValue - compositeMaterial.minValue);

    return materials[int(step(F, materialCoef.a0))];
}