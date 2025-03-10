//
// Created by Alberto Elorza Rubio on 18/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_INSERTITEMCOMMAND_H
#define HETEROGENEOUS_SOLIDS_INSERTITEMCOMMAND_H

#include "../Command.h"
#include "../../utils/ItemSet.h"
#include <memory>

namespace hs {

    template <class T>
    class InsertItemCommand: public Command {
    public:
        InsertItemCommand(std::shared_ptr<T> item, ItemSet<T>& container);

        void execute() override;
        void undo() override;
        const std::string& getDescription() override;
    private:
        std::shared_ptr<T> item;
        ItemSet<T>& container;
        static const std::string description;
    };

    template <class T>
    const std::string InsertItemCommand<T>::description = "Inserted Resource";

    template<class T>
    InsertItemCommand<T>::InsertItemCommand(std::shared_ptr<T> item, ItemSet<T>& container) :
        item(item), container(container)
    {

    }

    template<class T>
    void InsertItemCommand<T>::execute() {
        container.insert(item);
    }

    template<class T>
    void InsertItemCommand<T>::undo() {
        container.erase(item);
    }

    template<class T>
    const std::string& InsertItemCommand<T>::getDescription() {
        return description;
    }

} // hs

#endif //HETEROGENEOUS_SOLIDS_INSERTITEMCOMMAND_H
