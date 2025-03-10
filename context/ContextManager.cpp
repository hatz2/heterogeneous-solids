//
// Created by Alberto Elorza Rubio on 17/11/2023.
//

#include "ContextManager.h"

namespace hs {
    ContextManager::ContextManager(std::shared_ptr<Context> defaultContext) :
        defaultContext(std::move(defaultContext)), activeContext()
    {

    }

    std::shared_ptr<const Context> ContextManager::borrowContext() const {
        return activeContext.lock();
    }

    std::shared_ptr<Context> ContextManager::borrowContextMut() {
        return activeContext.lock();
    }

    std::shared_ptr<const Context> ContextManager::getDefaultContext() const {
        return defaultContext;
    }

    void ContextManager::setContext(std::shared_ptr<Context>& context) {
        activeContext = context;
    }

    bool ContextManager::isContext() const {
        return borrowContext() != nullptr;
    }
} // hs