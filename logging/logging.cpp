//
// Created by Alberto Elorza Rubio on 24/01/2024.
//

#include "logging.h"

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace hs::logging {

    static std::mutex defaultLoggerMutex;

    void setupLogging() {
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("./log.txt");
        file_sink->set_level(spdlog::level::warn);
        auto console_sink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
        #ifdef NDEBUG
        console_sink->set_level(spdlog::level::info);
        #else
        console_sink->set_level(spdlog::level::trace);
        #endif

        auto logger = std::make_shared<spdlog::logger>("HSF");
        logger->set_level(spdlog::level::trace);
        logger->sinks().push_back(file_sink);
        logger->sinks().push_back(console_sink);

        spdlog::set_default_logger(logger);
    }

    void defaultLoggerAddSinkMt(const std::shared_ptr<spdlog::sinks::sink>& sink) {
        defaultLoggerMutex.lock();
        auto logger = spdlog::default_logger();
        auto found = std::find(logger->sinks().begin(), logger->sinks().end(), sink);
        if (found == logger->sinks().end())
            logger->sinks().push_back(sink);
        defaultLoggerMutex.unlock();
    }

    void defaultLoggerRemoveSinkMt(const std::shared_ptr<spdlog::sinks::sink>& sink) {
        defaultLoggerMutex.lock();
        auto logger = spdlog::default_logger();
        logger->sinks().erase(
            std::remove(logger->sinks().begin(), logger->sinks().end(), sink),
            logger->sinks().end()
        );
        defaultLoggerMutex.unlock();
    }

} // logging