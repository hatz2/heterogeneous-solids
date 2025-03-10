//
// Created by Alberto Elorza Rubio on 14/12/2023.
//

#include "SceneNodeState.h"

namespace hs {
    MutableSceneNodeState::MutableSceneNodeState(std::string defaultDescription, bool visible) :
        defaultDescription(std::move(defaultDescription)), description(), visible(visible)
    {

    }

    std::string MutableSceneNodeState::getDefaultDescription() {
        return defaultDescription;
    }

    void MutableSceneNodeState::setDefaultDescription(std::string defaultDescription) {
        MutableSceneNodeState::defaultDescription = std::move(defaultDescription);
    }

    const std::string& MutableSceneNodeState::getDescription() const {
        return description;
    }

    void MutableSceneNodeState::setDescription(std::string description) {
        MutableSceneNodeState::description = description;
    }

    const std::string& MutableSceneNodeState::getDescriptionOrDefault() const {
        if (description.empty()) return defaultDescription;
        return description;
    }

    bool MutableSceneNodeState::isVisible() const {
        return visible;
    }

    void MutableSceneNodeState::setVisible(bool visible) {
        MutableSceneNodeState::visible = visible;
    }
} // hs