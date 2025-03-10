//
// Created by Alberto Elorza Rubio on 24/01/2024.
//

#include "LoggingWindow.h"

#include "../../logging/logging.h"

#include <utility>
#include <string>
#include <spdlog/spdlog.h>

namespace hs {
    ListCacheSink::ListCacheSink(std::list<std::string>& container, size_t maxItems) :
        container(container), maxItems(maxItems)
    {

    }

    void ListCacheSink::sink_it_(const spdlog::details::log_msg& msg) {
        spdlog::memory_buf_t formatted;
        base_sink<std::mutex>::formatter_->format(msg, formatted);
        container.push_back(fmt::to_string(formatted));
        if (container.size() > maxItems) // don't require 'while' if it's only being updated here
            container.pop_front();
    }

    void ListCacheSink::flush_() { }

    LoggingWindow::LoggingWindow(std::string title) : Window(std::move(title)),
        sink(std::make_shared<ListCacheSink>(messages)), keepBottom(true)
    {
        logging::defaultLoggerAddSinkMt(sink);
    }

    LoggingWindow::~LoggingWindow() {
        logging::defaultLoggerRemoveSinkMt(sink);
    }

    void LoggingWindow::renderBody() {
        for (const auto& message : messages)
            ImGui::TextUnformatted(message.c_str());
        keepBottom = ImGui::GetScrollMaxY() == ImGui::GetScrollY();
        if (keepBottom) ImGui::SetScrollHereY(1);
    }
} // hs