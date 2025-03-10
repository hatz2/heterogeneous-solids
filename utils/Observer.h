//
// Created by Alberto Elorza Rubio on 29/01/2024.
//

#ifndef HETEROGENEOUS_SOLIDS_OBSERVER_H
#define HETEROGENEOUS_SOLIDS_OBSERVER_H

#include <set>

namespace hs {

    template <class ...T>
    class Subject;

    /*
     * In order to safely work with this observer implementation you must ensure that the
     * observer is detached before being deleted since is handled in the subject as a raw pointer
     * */
    template <class ...T>
    class Observer {
    public:
        virtual void updateObserver(T...) = 0;

        virtual ~Observer() = default;
    };

    template <class ...T>
    class Subject {
    public:
        Subject() = default;
        Subject(const Subject<T...>&) = delete; // Prevent from cloning the whole observer list

        virtual void updateSubject(T...);

        virtual void attachObserver(Observer<T...>* observer);
        virtual void detachObserver(Observer<T...>* observer);

        virtual ~Subject() = default;
    private:
        std::set<Observer<T...>*> attachedObservers;
    };

    template<class... T>
    void Subject<T...>::updateSubject(T... args) {
        for (const auto& observer : attachedObservers)
            observer->updateObserver(std::forward<T>(args)...);
    }

    template<class... T>
    void Subject<T...>::attachObserver(Observer<T...>* observer) {
        attachedObservers.insert(observer);
    }

    template<class... T>
    void Subject<T...>::detachObserver(Observer<T...>* observer) {
        attachedObservers.erase(observer);
    }

} // hs

#endif //HETEROGENEOUS_SOLIDS_OBSERVER_H
