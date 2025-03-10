//
// Created by Alberto Elorza Rubio on 18/01/2024.
//

#include "MaterialEditor.h"

namespace hs {
    MaterialEditor::MaterialEditor() {
        heterogeneousMaterials.attachObserver(this);
        materials.attachObserver(this);
    }

    MaterialEditor::~MaterialEditor() {
        heterogeneousMaterials.detachObserver(this);
        materials.detachObserver(this);
    }

    std::optional<std::variant<std::shared_ptr<Material>, std::shared_ptr<HeterogeneousMaterial>>>
    MaterialEditor::getSelected() {
        return selected;
    }

    void MaterialEditor::setSelected(
        std::variant<std::shared_ptr<Material>, std::shared_ptr<HeterogeneousMaterial>> selected
    ) {
        MaterialEditor::selected = selected;
    }

    void MaterialEditor::unselect() {
        selected = std::nullopt;
    }

    ItemSet<Material>& MaterialEditor::getMaterials() {
        return materials;
    }

    ItemSet<HeterogeneousMaterial>& MaterialEditor::getHeterogeneousMaterials() {
        return heterogeneousMaterials;
    }

    void MaterialEditor::updateObserver(ItemSetEvent event, std::shared_ptr<HeterogeneousMaterial> material) {
        if (
            selected &&
            event == ItemSetEvent::Erased &&
            std::holds_alternative<std::shared_ptr<HeterogeneousMaterial>>(selected.value()) &&
            std::get<std::shared_ptr<HeterogeneousMaterial>>(selected.value()) == material
        ) selected = std::nullopt;
    }

    void MaterialEditor::updateObserver(ItemSetEvent event, std::shared_ptr<Material> material) {
        if (
            selected &&
            event == ItemSetEvent::Erased &&
            std::holds_alternative<std::shared_ptr<Material>>(selected.value()) &&
            std::get<std::shared_ptr<Material>>(selected.value()) == material
        ) selected = std::nullopt;
    }
} // hs