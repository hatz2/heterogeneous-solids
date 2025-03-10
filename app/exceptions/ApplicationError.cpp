//
// Created by Alberto Elorza Rubio on 21/01/2024.
//

#include "ApplicationError.h"

namespace hs {
    ApplicationError::ApplicationError(std::string title, std::string message, ApplicationErrorTopic topic) : std::runtime_error (""),
        title(std::move(title)), message(std::move(message)), topic(topic)
    {

    }

    const char* ApplicationError::what() const noexcept {
        return message.c_str();
    }

    const std::string& ApplicationError::getTitle() const {
        return title;
    }

    const std::string& ApplicationError::getMessage() const {
        return message;
    }

    ApplicationErrorTopic ApplicationError::getTopic() const {
        return topic;
    }
} // hs