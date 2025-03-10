//
// Created by Alberto Elorza Rubio on 01/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_EVENTHANDLER_H
#define HETEROGENEOUS_SOLIDS_EVENTHANDLER_H

namespace hs {

    template <typename T>
    class EventHandler {
    public:
        virtual void handle(T event) = 0;
        virtual ~EventHandler() = default;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_EVENTHANDLER_H
