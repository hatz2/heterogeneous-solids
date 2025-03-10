//
// Created by Alberto Elorza Rubio on 29/12/2023.
//

#include "Snapshot.h"
#include "../app/exceptions/ApplicationError.h"

#include <utility>
#include <filesystem>
#include <lodepng.h>
#include <spdlog/spdlog.h>

namespace hs {
    Snapshot::Snapshot(Renderer& renderer, Resolution resolution, IO& io) :
        renderer(renderer), resolution(std::move(resolution)), io(io),
        multisampledFrameBuffer(nullptr), frameBuffer(nullptr),
        snapshotMode(SnapshotMode::AskFile), counter(0)
    {
        updateFrameBuffer();
    }

    SnapshotMode Snapshot::getMode() const {
        return snapshotMode;
    }

    void Snapshot::setSnapshotMode(SnapshotMode snapshotMode) {
        Snapshot::snapshotMode = snapshotMode;
    }

    const Resolution& Snapshot::getResolution() const {
        return resolution;
    }

    void Snapshot::setResolution(const Resolution& resolution) {
        Snapshot::resolution = resolution;
        updateFrameBuffer();
    }

    const std::string& Snapshot::getOutputFolder() const {
        return outputFolder;
    }

    void Snapshot::requestOutputFolder() {
        if (auto folder = io.getDialogsFacade().selectFolder("Select Output Folder", "."))
            outputFolder = folder.value();
    }

    unsigned int Snapshot::getCounter() const {
        return counter;
    }

    void Snapshot::setCounter(unsigned int counter) {
        Snapshot::counter = counter;
    }

    void Snapshot::takeSnapshot(const RenderProfile& profile, const Scene& scene) {
        auto file = getNextFile();
        if (!file) return;

        multisampledFrameBuffer->begin();
        scene.getCamera().setAspect(multisampledFrameBuffer->getAspect());
        renderer.render(profile, scene);
        glFlush();
        glFinish();
        multisampledFrameBuffer->end();

        multisampledFrameBuffer->copyTo(*frameBuffer);

        frameBuffer->begin();
        std::vector<unsigned char> img(resolution.width * resolution.height * 4);

        for (int i = 0; i < resolution.height; i++)
            glReadPixels(
                0, i, (int)resolution.width, 1,
                GL_RGBA, GL_UNSIGNED_BYTE, &img[(resolution.height-1-i)*resolution.width*4]
            );
        frameBuffer->end();

        if (auto err = lodepng::encode(file.value(), img, resolution.width, resolution.height))
            throw ApplicationError(
                "Snapshot saving error", lodepng_error_text(err), ApplicationErrorTopic::FileSystem
            );
        spdlog::info("Snapshot successfully stored at: {}", file.value());
    }

    void Snapshot::updateFrameBuffer() {
        multisampledFrameBuffer = FrameBuffer::getSharedFrameBuffer((GLint)resolution.width, (GLint)resolution.height, true);
        frameBuffer = FrameBuffer::getSharedFrameBuffer((GLint)resolution.width, (GLint)resolution.height);
    }

    std::optional<std::string> Snapshot::getNextFile() {
        switch (snapshotMode) {
            case SnapshotMode::AskFile:
                return io.getDialogsFacade().saveFile("Save snapshot", ".", { { "PNG Image", "*.png" } });
            case SnapshotMode::Folder:
                if (outputFolder.empty()) requestOutputFolder();
                if (outputFolder.empty()) return std::nullopt;
                return std::filesystem::path(outputFolder)
                    .append(FOLDER_SNAPSHOT_FILE_PREFIX + std::to_string(counter++) + ".png").string();
            default:
                return std::nullopt;
        }
    }
} // hs