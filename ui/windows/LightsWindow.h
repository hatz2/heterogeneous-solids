//
// Created by Alberto Elorza Rubio on 26/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_LIGHTSWINDOW_H
#define HETEROGENEOUS_SOLIDS_LIGHTSWINDOW_H

#include "../core/ContextWindow.h"
#include "../core/UI.h"

namespace hs {

    class LightsWindow: public ContextWindow {
    public:
        LightsWindow(std::string title, std::shared_ptr<ContextManager> contextManager, UI& ui);
    protected:
        void renderBody(const Context&) override;
    private:
        static void commonLightProps(LightProps& lightProps, const Context& context);
        static void positionalLightProps(LightProps&);
        static void customLightsTable(LightSet& lights, const Context& context);

        std::shared_ptr<Dialog> lightDialog;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_LIGHTSWINDOW_H
