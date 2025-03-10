//
// Created by Alberto Elorza Rubio on 09/12/2023.
//

#include "LightGizmo.h"

#include <array>

namespace hs {
    LightGizmoResource::LightGizmoResource(): count(2) {
        glGenVertexArrays(1, &idVAO);
        glBindVertexArray(idVAO);
        glGenBuffers(1, &idVBO);
        glBindBuffer(GL_ARRAY_BUFFER, idVBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, nullptr, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);
    }

    LightGizmoResource::~LightGizmoResource() {
        if (idVAO) glDeleteVertexArrays(1, &idVAO);
        if (idVBO) glDeleteBuffers(1, &idVBO);
    }

    std::unique_ptr<LightGizmoResource> LightGizmo::lightResource = nullptr;

    LightGizmo::LightGizmo(Light& light) : light(light) {
        if (!lightResource) lightResource = std::make_unique<LightGizmoResource>();
    }

    void LightGizmo::render(RenderContext& renderContext) {
        glBindVertexArray(lightResource->idVAO);
        glBindBuffer(GL_ARRAY_BUFFER, lightResource->idVBO);
        const std::array<glm::vec3, 2> data = {
            light.getLightProps().getPosition(),
            light.getLightProps().getLookAt()
        };
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 6, data.data());

        glDrawArrays(GL_LINES, 0, lightResource->count);
    }
} // hs