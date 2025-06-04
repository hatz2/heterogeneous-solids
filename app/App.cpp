//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#include "App.h"
#include "../ui/windows/SceneWindow.h"
#include "../heterogeneous_solids/factories/HeterogeneousSolidFactory.h"
#include "../ui/menus/SelectionMenu.h"
#include "../serialization/json/JSONSerializer.h"
#include "exceptions/ApplicationError.h"
#include "../serialization/FileDocument.h"
#include "../shaders/ShaderIOJSON.h"
#include "../ui/menus/EditMenu.h"
#include "../ui/menus/ToggleWindowsMenu.h"
#include "../ui/windows/TransformWindow.h"
#include <filesystem>
#include <utility>

namespace hs {

    App::App(GLFWwindow* window, Resources resources) :
        ui(std::make_unique<UI>()),
        io(std::make_unique<IO>(std::move(resources))),
        contextManager(std::make_unique<ContextManager>(std::make_unique<Context>(*io))),
        extensionSerializers(),
        window(window)
    {
        extensionSerializers.insert({".json", std::make_unique<JSONSerializer>()});

        auto& windowManager = ui->getWindowManager();

        windowManager.addStaticWindow(std::make_shared<CameraWindow>(ICON_MD_CAMERA_ENHANCE " Camera###camera", contextManager));
        windowManager.addStaticWindow(std::make_shared<LightsWindow>(ICON_MD_LIGHT " Lights###lights", contextManager, *ui));
        windowManager.addStaticWindow(std::make_shared<ObjectWindow>(ICON_MD_WIDGETS " Object###object", contextManager));
        windowManager.addStaticWindow(std::make_shared<RenderProcessWindow>(ICON_MD_VIDEOCAM " Render Process###renderProcess", contextManager));
        windowManager.addStaticWindow(std::make_shared<TreeViewWindow>(ICON_MD_FOREST " Tree###tree", contextManager));
        windowManager.addStaticWindow(std::make_shared<CommandHistoryWindow>(ICON_MD_LIST " Command History###commandHistory", contextManager));
        windowManager.addStaticWindow(std::make_shared<SnapshotWindow>(ICON_MD_CAMERA " Snapshot###snapshot", contextManager));
        windowManager.addStaticWindow(std::make_shared<ProfilerWindow>(ICON_MD_BAR_CHART " Profiler###profiler"));
        windowManager.addStaticWindow(std::make_shared<MaterialsWindow>(ICON_MD_TEXTURE " Materials###materials", contextManager));
        windowManager.addStaticWindow(std::make_shared<LoggingWindow>(ICON_MD_INFO " Logging###logging"));
        windowManager.addStaticWindow(std::make_shared<ShadersWindow>(ICON_MD_DATA_ARRAY " Shaders###shaders", io->getShaderManager()));
        windowManager.addStaticWindow(std::make_shared<TrimmingWindow>(ICON_MD_BUILD " Trimming###trimming", contextManager));
        windowManager.addStaticWindow(std::make_shared<CellWindow>(ICON_MD_SELECT_ALL " Cell###cell", contextManager));
        windowManager.addStaticWindow(std::make_shared<TransformWindow>(ICON_MD_TRANSFORM " Transform###transform", contextManager));

        auto isContext = [this]() { return contextManager->isContext(); };

        auto menuFile = std::make_unique<Menu>("File");
        menuFile->addItem(std::make_unique<MenuItem>(ICON_MD_ADD " New", [this]() {
            createScene();
        }));
        menuFile->addItem(std::make_unique<MenuItem>(ICON_MD_FILE_OPEN " Open...", [this]() {
            openDocument();
        }));
        menuFile->addItem(std::make_unique<MenuItem>(ICON_MD_FILE_OPEN " Open HDRI Map", [this]()
        {
            openEnvironmentMap();
        }));
        menuFile->addSeparator();
        menuFile->addItem(std::make_unique<ConditionalMenuItem>(ICON_MD_SAVE " Save", [this]() {
            saveDocument();
        }, isContext));
        menuFile->addItem(std::make_unique<ConditionalMenuItem>(ICON_MD_SAVE_AS " Save As...", [this]() {
            saveDocument(true);
        }, isContext));

        ui->getMainMenu().addItem(std::move(menuFile));

        ui->getMainMenu().addItem(std::make_unique<EditMenu>(contextManager));

        auto layoutWindow = std::make_unique<Menu>("Layout");
        layoutWindow->addItem(std::make_unique<ToggleWindowsMenu>(ui->getWindowManager()));

        ui->getMainMenu().addItem(std::move(layoutWindow));

        ui->getMainMenu().addItem(std::make_unique<SelectionMenu>(contextManager, *ui));

        createScene();
        spdlog::info("Application Initialized");
    }

    void App::run() {
        try {
            ui->render();
            updateTitle();
        } catch (const ApplicationError& appError) {
            spdlog::error("Got Application Error: {}", appError.getMessage());
            ui->recoverFromError();
            io->getDialogsFacade().message(appError.getTitle(), appError.getMessage(), DialogButton::Ok, DialogIcon::Error);
        } catch (const std::runtime_error& unexpected) {
            spdlog::error("Got Unexpected Error: {}", unexpected.what());
            ui->recoverFromError();
        }
    }

    std::shared_ptr<Context> App::createScene() {
        static unsigned int id = 0;
        try {
            auto context = std::make_shared<Context>(*io);
            ui->getWindowManager().addDynamicWindow(std::make_shared<SceneWindow>(
                "Scene##" + std::to_string(id++),
                context,
                contextManager
            ));
            return context;
        } catch (const std::runtime_error& ex) {
            throw ApplicationError("Error creating context", ex.what(), ApplicationErrorTopic::Context);
        }
    }

    void App::saveDocument(bool asNew) {
        auto context = contextManager->borrowContextMut();
        if (asNew || !context->getDocument()) {
            if (auto result = io->getDialogsFacade().saveFile("Create a file", ".", { { "JSON", "*.json" } })) {
                auto path = std::filesystem::path(result.value());
                auto serializer = extensionSerializers.find(path.extension().string());
                if (serializer == extensionSerializers.end())
                    throw ApplicationError("Error saving file", "Invalid extension", ApplicationErrorTopic::Unexpected);

                context->setDocument(std::make_unique<FileDocument>(path.string(), *serializer->second, *context));
            }
        }
        if (auto document = context->getDocument())
            document->get().save();
    }

    void App::openDocument() {
        if (auto result = io->getDialogsFacade().openFile("Open a file", ".", { { "JSON", "*.json" } })) {
            auto path = std::filesystem::path(result.value());
            auto serializer = extensionSerializers.find(path.extension().string());
            if (serializer == extensionSerializers.end())
                throw ApplicationError("Error opening file", "Invalid extension", ApplicationErrorTopic::Unexpected);

            auto context = createScene();
            context->setDocument(std::make_unique<FileDocument>(path.string(), *serializer->second, *context));
            if (auto document = context->getDocument())
                document->get().load();
        }
    }

    void App::openEnvironmentMap()
    {
        if (auto result = io->getDialogsFacade().openFile(
    "Open HDR environment map", ".", {{ "HDR", "*.hdr"}}
        ))
        {
            contextManager->borrowContext()->getRenderer().loadEnvMap(result.value());
        }
    }

    void App::updateTitle() {
        if (auto context = contextManager->borrowContext()) {
            if (auto document = context->getDocument())
                glfwSetWindowTitle(window, document->get().getResource().c_str());
            else
                glfwSetWindowTitle(window, "New Heterogeneous Solid");
        } else
            glfwSetWindowTitle(window, "Heterogeneous Solid Framework");
    }
} // hs