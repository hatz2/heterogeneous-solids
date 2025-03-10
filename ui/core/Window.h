//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_WINDOW_H
#define HETEROGENEOUS_SOLIDS_WINDOW_H

#include <string>
#include <imgui.h>

namespace hs {

    class Window {
    public:
        explicit Window(std::string title);
        virtual ~Window() = default;
        Window() = delete;
        Window(const Window&) = default;

        virtual void render();

        [[nodiscard]] bool isOpen() const;
        void setOpen(bool open);
        void toggleOpen();

        [[nodiscard]] const std::string& getTitle() const;
        void setTitle(const std::string& title);

        [[nodiscard]] ImGuiWindowFlags getFlags() const;
        void setFlags(ImGuiWindowFlags flags);
    protected:
        virtual void renderBody() = 0;
    private:
        std::string title;
        ImGuiWindowFlags flags;
        bool open;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_WINDOW_H
