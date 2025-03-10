//
// Created by Alberto Elorza Rubio on 24/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_LOGGINGWINDOW_H
#define HETEROGENEOUS_SOLIDS_LOGGINGWINDOW_H

#include <string>
#include "../core/Window.h"
#include <memory>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/details/log_msg.h>
#include <list>
#include <mutex>

namespace hs {

    class ListCacheSink: public spdlog::sinks::base_sink<std::mutex> {
    public:
        explicit ListCacheSink(std::list<std::string>& container, size_t maxItems = 255);
    protected:
        void sink_it_(const spdlog::details::log_msg& msg) override;
        void flush_() override;
    private:
        std::list<std::string>& container;
        size_t maxItems;
    };

    class LoggingWindow: public Window {
    public:
        explicit LoggingWindow(std::string title);
        ~LoggingWindow() override;
    protected:
        void renderBody() override;
    private:
        std::shared_ptr<spdlog::sinks::sink> sink;
        std::list<std::string> messages;
        bool keepBottom;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_LOGGINGWINDOW_H
