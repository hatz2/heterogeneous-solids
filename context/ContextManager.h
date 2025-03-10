//
// Created by Alberto Elorza Rubio on 17/11/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_CONTEXTMANAGER_H
#define HETEROGENEOUS_SOLIDS_CONTEXTMANAGER_H

#include <memory>
#include "Context.h"

namespace hs {

    class ContextManager {
    private:
        std::shared_ptr<Context> defaultContext;
        std::weak_ptr<Context> activeContext;
    public:
        ContextManager() = delete;
        explicit ContextManager(std::shared_ptr<Context> defaultContext);
        ContextManager(const ContextManager&) = delete;

        [[nodiscard]] std::shared_ptr<const Context> borrowContext() const;
        [[nodiscard]] std::shared_ptr<Context> borrowContextMut();
        [[nodiscard]] std::shared_ptr<const Context> getDefaultContext() const;

        void setContext(std::shared_ptr<Context>& context);

        [[nodiscard]] bool isContext() const;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_CONTEXTMANAGER_H
