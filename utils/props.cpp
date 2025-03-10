//
// Created by Alberto Elorza Rubio on 08/02/2024.
//

#include "props.h"

namespace hs {
    DescriptionPropImpl::DescriptionPropImpl(std::string description) : defaultDescription(std::move(description)) {

    }

    const std::string& DescriptionPropImpl::getDescription() const {
        return description;
    }

    void DescriptionPropImpl::setDescription(std::string description) {
        DescriptionPropImpl::description = std::move(description);
    }

    std::string DescriptionPropImpl::getDefaultDescription() {
        return defaultDescription;
    }

    void DescriptionPropImpl::setDefaultDescription(std::string defaultDescription) {
        DescriptionPropImpl::defaultDescription = std::move(defaultDescription);
    }

    const std::string& DescriptionPropImpl::getDescriptionOrDefault() const {
        if (description.empty()) return defaultDescription;
        return description;
    }
} // hs