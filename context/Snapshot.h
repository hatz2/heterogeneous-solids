//
// Created by Alberto Elorza Rubio on 29/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_SNAPSHOT_H
#define HETEROGENEOUS_SOLIDS_SNAPSHOT_H

#include "../utils/Resolution.h"
#include "../scene/FrameBuffer.h"
#include "../scene/Renderer.h"
#include "../io/dialogs/DialogsFacade.h"
#include "../io/IO.h"

#include <memory>

#define FOLDER_SNAPSHOT_FILE_PREFIX "snapshot_"

namespace hs {

    enum class SnapshotMode {
        AskFile,
        Folder
    };

    class Snapshot {
    public:
        Snapshot() = delete;
        Snapshot(Renderer& renderer, Resolution resolution, IO& io);
        Snapshot(const Snapshot&) = delete;

        [[nodiscard]] const Resolution& getResolution() const;
        void setResolution(const Resolution& resolution);

        [[nodiscard]] SnapshotMode getMode() const;
        void setSnapshotMode(SnapshotMode snapshotMode);

        [[nodiscard]] const std::string& getOutputFolder() const;
        void requestOutputFolder();

        [[nodiscard]] unsigned int getCounter() const;
        void setCounter(unsigned int counter);

        void takeSnapshot(const RenderProfile& profile, const Scene& scene);
    private:
        void updateFrameBuffer();
        std::optional<std::string> getNextFile();

        Renderer& renderer;
        Resolution resolution;
        IO& io;

        SnapshotMode snapshotMode;
        std::string outputFolder;
        unsigned int counter;
        std::shared_ptr<FrameBuffer> multisampledFrameBuffer;
        std::shared_ptr<FrameBuffer> frameBuffer;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_SNAPSHOT_H
