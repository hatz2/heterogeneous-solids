//
// Created by Alberto Elorza Rubio on 24/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_LOGGING_H
#define HETEROGENEOUS_SOLIDS_LOGGING_H

#include <spdlog/sinks/sink.h>

namespace hs::logging {

    void setupLogging();

    void defaultLoggerAddSinkMt(const std::shared_ptr<spdlog::sinks::sink>&);

    void defaultLoggerRemoveSinkMt(const std::shared_ptr<spdlog::sinks::sink>&);

} // logging

#endif //HETEROGENEOUS_SOLIDS_LOGGING_H
