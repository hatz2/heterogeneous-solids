//
// Created by Alberto Elorza Rubio on 12/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_DIALOG_H
#define HETEROGENEOUS_SOLIDS_DIALOG_H

#include <string>

namespace hs {

    class Dialog {
    public:
        using DoClose = bool;

        Dialog() = delete;
        explicit Dialog(std::string title);
        virtual ~Dialog() = default;

        virtual void render();

        void show();
        virtual void reset();
    protected:
        virtual DoClose renderBody() = 0;
        std::string title;
        bool requestShow;
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_DIALOG_H
