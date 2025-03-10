//
// Created by Alberto Elorza Rubio on 13/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SCENEWINDOW_H
#define HETEROGENEOUS_SOLIDS_SCENEWINDOW_H

#include <memory>
#include "../../scene/FrameBuffer.h"
#include "../../scene/Scene.h"
#include "../../context/Context.h"
#include "../../context/ContextManager.h"
#include "../core/ContextWindow.h"

namespace hs {

    class SceneWindow: public ContextWindow {
    public:
        SceneWindow(
            std::string name,
            std::shared_ptr<Context> context,
            std::shared_ptr<ContextManager> contextManager,
            unsigned int resolution = 2048
        );
    protected:
        void renderBody(const Context&) override;
        void renderBody() override;
        void render() override;
    private:
        std::shared_ptr<Context> context;
        std::shared_ptr<FrameBuffer> sceneMultisampledFrameBuffer;
        std::unique_ptr<FrameBuffer> sceneOutputFrameBuffer;
        std::shared_ptr<FrameBuffer> selectColorFrameBuffer;

        unsigned int resolution;

        bool applyTransforms(const Context& context, ImVec2 drawPosition, ImVec2 drawSize);
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SCENEWINDOW_H
