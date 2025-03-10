//
// Created by Alberto Elorza Rubio on 18/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_MATERIALSWINDOW_H
#define HETEROGENEOUS_SOLIDS_MATERIALSWINDOW_H

#include "../core/ContextWindow.h"

namespace hs {

    class MaterialsWindow: public ContextWindow {
    public:
        MaterialsWindow(std::string title, std::shared_ptr<ContextManager> contextManager);
    protected:
        void renderBody(const hs::Context &) override;
    private:
        static void renderHeterogeneousMaterial(const Context& context, HeterogeneousMaterial& hsMaterial);
        static void renderMaterial(const Context& context, Material& material);
        static void materialsProperties(Material& material);
        static void pickMaterial(MaterialEditor& materialEditor, HeterogeneousMaterial& hsMaterial, bool primary);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_MATERIALSWINDOW_H
