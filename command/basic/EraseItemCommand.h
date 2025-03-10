//
// Created by Alberto Elorza Rubio on 18/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_INSERTRESOURCECOMMAND_H
#define HETEROGENEOUS_SOLIDS_INSERTRESOURCECOMMAND_H

#include "../Command.h"
#include "../../utils/ItemSet.h"
#include <memory>

namespace hs {

    template <class T>
    class EraseItemCommand: public Command {
    public:
        EraseItemCommand(std::shared_ptr<T> item, ItemSet<T>& container);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;
    private:
        std::shared_ptr<T> item;
        ItemSet<T>& container;
        static const std::string description;
    };

    template <class T>
    const std::string EraseItemCommand<T>::description = "Erased Resource";

    template<class T>
    EraseItemCommand<T>::EraseItemCommand(std::shared_ptr<T> item, ItemSet<T>& container) :
        item(item), container(container)
    {

    }

    template<class T>
    void EraseItemCommand<T>::execute() {
        container.erase(item);
    }

    template<class T>
    void EraseItemCommand<T>::undo() {
        container.insert(item);
    }

    template<class T>
    const std::string& EraseItemCommand<T>::getDescription() {
        return description;
    }

} // hs

#endif //HETEROGENEOUS_SOLIDS_INSERTRESOURCECOMMAND_H
