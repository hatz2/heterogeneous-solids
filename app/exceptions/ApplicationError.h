//
// Created by Alberto Elorza Rubio on 21/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_APPLICATIONERROR_H
#define HETEROGENEOUS_SOLIDS_APPLICATIONERROR_H

#include <stdexcept>

namespace hs {

    enum class ApplicationErrorTopic {
        FileSystem,
        Context,
        Unexpected,
        DefaultTopic
    };

    class ApplicationError: public std::runtime_error {
    public:
        ApplicationError(
            std::string title,
            std::string message,
            ApplicationErrorTopic topic = ApplicationErrorTopic::DefaultTopic
        );

        [[nodiscard]] const char* what() const noexcept override;

        [[nodiscard]] const std::string& getTitle() const;
        [[nodiscard]] const std::string& getMessage() const;
        [[nodiscard]] ApplicationErrorTopic getTopic() const;
    private:
        std::string title;
        std::string message;
        ApplicationErrorTopic topic;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_APPLICATIONERROR_H
