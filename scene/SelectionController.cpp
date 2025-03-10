//
// Created by Alberto Elorza Rubio on 22/12/2023.
//

#include "SelectionController.h"

#include "objects/SceneNode.h"

namespace hs {
    SelectionController::SelectionController(Uniform selectionUniform) :
        selectionUniform(selectionUniform), indexCounter(0), subscriptions(), lastIndex(createNext())
    {

    }

    void SelectionController::subscribeNextObject(Selectable selectable) {
        lastIndex = createNext();
        selectionUniform.set(glm::vec3(lastIndex)/255.f);
        subscriptions.insert({ lastIndex, selectable });
    }

    glm::vec3 SelectionController::getLast() {
        return lastIndex;
    }

    std::optional<SelectionController::Selectable> SelectionController::getResult(glm::vec2 coords) {
        glFlush();
        glFinish();

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        unsigned char data[3];
        glReadPixels((int)coords.x, (int)coords.y,1,1, GL_RGB, GL_UNSIGNED_BYTE, &data);
        glm::ivec3 index { data[0], data[1], data[2] };

        auto item = subscriptions.find(index);
        if (item != subscriptions.end()) return item->second;
        return std::nullopt;
    }

    glm::ivec3 SelectionController::createNext() {
        unsigned id = indexCounter++;
        auto r = id%256;
        auto g = (id/256)%256;
        auto b = ((id/256)/256)%256;
        return { r, g, b };
    }

    Uniform SelectionController::getSelectionUniform() const {
        return selectionUniform;
    }

    void SelectionController::setSelectionUniform(Uniform selectionUniform) {
        SelectionController::selectionUniform = selectionUniform;
    }
} // hs