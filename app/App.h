//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_APP_H
#define HETEROGENEOUS_SOLIDS_APP_H

#include <memory>
#include "../ui/core/UI.h"
#include "../context/ContextManager.h"
#include "../ui/windows/CameraWindow.h"
#include "../io/dialogs/DialogsFacade.h"
#include "../ui/windows/LightsWindow.h"
#include "../ui/windows/RenderProcessWindow.h"
#include "../ui/windows/TreeViewWindow.h"
#include "../ui/windows/ObjectWindow.h"
#include "../ui/windows/CommandHistoryWindow.h"
#include "../ui/windows/SnapshotWindow.h"
#include "../ui/windows/ProfilerWindow.h"
#include "../ui/windows/MaterialsWindow.h"
#include "../serialization/Serializer.h"
#include "../ui/windows/LoggingWindow.h"
#include "../ui/windows/ShadersWindow.h"
#include "../ui/windows/TrimmingWindow.h"
#include "../ui/windows/CellWindow.h"
#include "../io/Resources.h"
#include <unordered_map>
#include <GLFW/glfw3.h>

namespace hs {

    class App {
    public:
        App(GLFWwindow* window, Resources resources);
        App(const App&) = delete;

        void run();
    private:
        std::unique_ptr<UI> ui;
        std::unique_ptr<IO> io;
        std::shared_ptr<ContextManager> contextManager;
        std::unordered_map<std::string, std::unique_ptr<Serializer>> extensionSerializers;
        GLFWwindow* window;

        std::shared_ptr<Context> createScene();

        void saveDocument(bool asNew = false);
        void openDocument();
        void openEnvironmentMap();
        void updateTitle();
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_APP_H
