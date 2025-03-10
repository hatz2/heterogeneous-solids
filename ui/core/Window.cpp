//
// Created by Alberto Elorza Rubio on 11/11/2023.
//

#include "Window.h"

#include <utility>
#include <imgui.h>

namespace hs {
    Window::Window(std::string title): title(std::move(title)), open(true), flags(ImGuiWindowFlags_None) {

    }

    void Window::render() {
        ImGui::Begin(title.c_str(), &open, flags);
        renderBody();
        ImGui::End();
    }

    bool Window::isOpen() const {
        return this->open;
    }

    void Window::setOpen(bool open) {
        this->open = open;
    }

    void Window::toggleOpen() {
        this->open = !open;
    }

    const std::string& Window::getTitle() const {
        return title;
    }

    void Window::setTitle(const std::string& title) {
        Window::title = title;
    }

    ImGuiWindowFlags Window::getFlags() const {
        return flags;
    }

    void Window::setFlags(ImGuiWindowFlags flags) {
        Window::flags = flags;
    }
} // hs