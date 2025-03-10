//
// Created by Alberto Elorza Rubio on 18/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_MATERIALEDITOR_H
#define HETEROGENEOUS_SOLIDS_MATERIALEDITOR_H

#include "../utils/ItemSet.h"
#include "../scene/Material.h"
#include "../heterogeneous_solids/HeterogeneousMaterial.h"

#include <variant>

namespace hs {

    class MaterialEditor:
        private Observer<ItemSetEvent, std::shared_ptr<HeterogeneousMaterial>>,
        private Observer<ItemSetEvent, std::shared_ptr<Material>>
    {
    public:
        MaterialEditor();
        ~MaterialEditor() override;

        std::optional<std::variant<std::shared_ptr<Material>, std::shared_ptr<HeterogeneousMaterial>>> getSelected();
        void setSelected(std::variant<std::shared_ptr<Material>, std::shared_ptr<HeterogeneousMaterial>> selected);
        void unselect();

        ItemSet<Material>& getMaterials();
        ItemSet<HeterogeneousMaterial>& getHeterogeneousMaterials();
    private:
        std::optional<std::variant<std::shared_ptr<Material>, std::shared_ptr<HeterogeneousMaterial>>> selected;

        ItemSet<Material> materials;
        ItemSet<HeterogeneousMaterial> heterogeneousMaterials;

        void updateObserver(ItemSetEvent, std::shared_ptr<HeterogeneousMaterial>) override;
        void updateObserver(ItemSetEvent, std::shared_ptr<Material>) override;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MATERIALEDITOR_H
