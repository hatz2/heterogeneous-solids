//
// Created by Alberto Elorza Rubio on 17/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_CONTEXT_H
#define HETEROGENEOUS_SOLIDS_CONTEXT_H

#include <memory>
#include "../scene/Scene.h"
#include "../scene/Renderer.h"
#include "../command/CommandHistory.h"
#include "EventManager.h"
#include "Snapshot.h"
#include "../utils/ItemSet.h"
#include "../heterogeneous_solids/trimmed_cells/TrimmingNode.h"
#include "MaterialEditor.h"
#include "Document.h"
#include "SceneStatus.h"
#include "../io/IO.h"
#include "SceneTools.h"

namespace hs {

    class Context {
    public:
        explicit Context(IO& io);

        [[nodiscard]] unsigned int getContextId() const;
        [[nodiscard]] Scene& getScene() const;
        [[nodiscard]] Renderer& getRenderer() const;
        [[nodiscard]] RenderProfile& getRenderProfile() const;
        [[nodiscard]] CommandHistory& getCommandHistory() const;
        [[nodiscard]] MacroSet& getMacroSet() const;
        [[nodiscard]] Snapshot& getSnapshot() const;
        [[nodiscard]] MaterialEditor& getMaterialEditor() const;
        [[nodiscard]] SceneStatus& getSceneStatus() const;
        [[nodiscard]] SceneTools& getSceneTools() const;
        [[nodiscard]] Selector& getSelector() const;
        [[nodiscard]] EventManager& getEventManager() const;
        [[nodiscard]] std::optional<std::reference_wrapper<Document>> getDocument() const;
        [[nodiscard]] IO& getIO() const;

        void setDocument(std::unique_ptr<Document> document);

    private:
        unsigned int contextId;
        std::unique_ptr<Scene> scene;
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<RenderProfile> renderProfile;
        std::unique_ptr<CommandHistory> commandHistory;
        std::unique_ptr<Snapshot> snapshot;
        std::unique_ptr<MacroSet> macroSet;
        std::unique_ptr<MaterialEditor> materialEditor;
        std::unique_ptr<SceneStatus> sceneStatus;
        std::unique_ptr<SceneTools> sceneTools;
        std::unique_ptr<Selector> selector;
        std::unique_ptr<EventManager> eventManager;
        std::optional<std::unique_ptr<Document>> document;
        IO& io;

        static unsigned int ContextIdCounter;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CONTEXT_H
