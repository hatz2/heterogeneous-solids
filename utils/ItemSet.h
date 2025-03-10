//
// Created by Alberto Elorza Rubio on 18/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_ITEMSET_H
#define HETEROGENEOUS_SOLIDS_ITEMSET_H

#include <set>
#include <memory>
#include <functional>
#include "Observer.h"

namespace hs {

    enum class ItemSetEvent {
        Inserted,
        Erased
    };

    template <class T>
    class ItemSet: public Subject<ItemSetEvent, std::shared_ptr<T>> {
    public:
        using iterator = typename std::set<std::shared_ptr<T>>::iterator;

        ItemSet() = default;
        ItemSet(const ItemSet<T>&) = delete;

        void insert(const std::shared_ptr<T>& item);
        void erase(const std::shared_ptr<T>& item);
        void erase_if(std::function<bool(const std::shared_ptr<T>&)> cond);

        iterator begin();
        iterator end();
    private:
        std::set<std::shared_ptr<T>> items;
    };

    template<class T>
    void ItemSet<T>::insert(const std::shared_ptr<T>& item) {
        items.insert(item);
        Subject<ItemSetEvent, std::shared_ptr<T>>::updateSubject(ItemSetEvent::Inserted, item);
    }

    template<class T>
    void ItemSet<T>::erase(const std::shared_ptr<T>& item) {
        items.erase(item);
        Subject<ItemSetEvent, std::shared_ptr<T>>::updateSubject(ItemSetEvent::Erased, item);
    }

    template<class T>
    void ItemSet<T>::erase_if(std::function<bool(const std::shared_ptr<T>&)> cond) {
        for (
            auto iter = items.begin();
            iter != items.end();
            cond(*iter) ? iter = items.erase(iter) : ++iter
        );
    }

    template<class T>
    typename ItemSet<T>::iterator ItemSet<T>::begin() {
        return items.begin();
    }

    template<class T>
    typename ItemSet<T>::iterator ItemSet<T>::end() {
        return items.end();
    }

} // hs

#endif //HETEROGENEOUS_SOLIDS_ITEMSET_H
