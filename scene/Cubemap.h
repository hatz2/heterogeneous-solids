//
// Created by alext on 14/04/2025.
//

#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <vector>
#include <string>
#include "RenderContext.h"

namespace hs {
    class Cubemap {
    public:
        /**
         * Order of faces:
         *
         * 1. right
         * 2. left
         * 3. top
         * 4. bottom
         * 5. front
         * 6. back
         *
         * @param faces
         */
        explicit Cubemap(const std::vector<std::string>& faces);

        void apply(RenderContext& renderContext) const;

        [[nodiscard]] int getId() const;

    private:
        unsigned int id;
    };
}




#endif //CUBEMAP_H
