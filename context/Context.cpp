//
// Created by Alberto Elorza Rubio on 17/11/2023.
//

#include "Context.h"

namespace hs {
    unsigned int Context::ContextIdCounter = 0;

    Context::Context(IO& io) :
        contextId(ContextIdCounter++),
        scene(std::make_unique<Scene>()),
        renderer(std::make_unique<Renderer>(io.getShaderManager())),
        renderProfile(std::make_unique<RenderProfile>()),
        commandHistory(std::make_unique<CommandHistory>()),
        macroSet(std::make_unique<MacroSet>()),
        snapshot(std::make_unique<Snapshot>(*Context::renderer, HDReady, io)),
        materialEditor(std::make_unique<MaterialEditor>()),
        sceneStatus(std::make_unique<SceneStatus>()),
        sceneTools(std::make_unique<SceneTools>()),
        selector(std::make_unique<Selector>(*Context::scene, *Context::materialEditor, *Context::commandHistory)),
        eventManager(std::make_unique<EventManager>(*Context::scene, *Context::selector, *Context::commandHistory)),
        document(std::nullopt),
        io(io)
    {

    }

    unsigned int Context::getContextId() const {
        return contextId;
    }

    Scene& Context::getScene() const {
        return *scene;
    }

    Renderer& Context::getRenderer() const {
        return *renderer;
    }

    RenderProfile& Context::getRenderProfile() const {
        return *renderProfile;
    }

    CommandHistory& Context::getCommandHistory() const {
        return *commandHistory;
    }

    MacroSet& Context::getMacroSet() const {
        return *macroSet;
    }

    Snapshot& Context::getSnapshot() const {
        return *snapshot;
    }

    MaterialEditor& Context::getMaterialEditor() const {
        return *materialEditor;
    }

    SceneStatus& Context::getSceneStatus() const {
        return *sceneStatus;
    }

    SceneTools& Context::getSceneTools() const {
        return *sceneTools;
    }

    Selector& Context::getSelector() const {
        return *selector;
    }

    EventManager& Context::getEventManager() const {
        return *eventManager;
    }

    std::optional<std::reference_wrapper<Document>> Context::getDocument() const {
        if (document) return std::ref(*document.value());
        return std::nullopt;
    }

    IO& Context::getIO() const {
        return io;
    }

    void Context::setDocument(std::unique_ptr<Document> document) {
        Context::document = std::move(document);
    }
} // hs