//
// Created by Alberto Elorza Rubio on 14/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SCENENODESTATE_H
#define HETEROGENEOUS_SOLIDS_SCENENODESTATE_H

#include <string>

#include "../../bindings/IconsMaterialDesign.h"
#include "../../utils/props.h"

namespace hs {

    class SceneNodeState: public DescriptionProp, public VisibilityProp { };

    class MutableSceneNodeState: public SceneNodeState {
    protected:
        std::string defaultDescription;
        std::string description;
        bool visible;
    public:
        explicit MutableSceneNodeState(
            std::string defaultDescription = "Scene Node", bool visible = true
        );
        MutableSceneNodeState(const MutableSceneNodeState&) = default;

        [[nodiscard]] std::string getDefaultDescription() override;
        void setDefaultDescription(std::string defaultDescription) override;

        [[nodiscard]] const std::string& getDescription() const override;
        void setDescription(std::string description) override;

        [[nodiscard]] const std::string& getDescriptionOrDefault() const override;

        [[nodiscard]] bool isVisible() const override;
        void setVisible(bool visible) override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SCENENODESTATE_H
