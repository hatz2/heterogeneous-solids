//
// Created by alext on 27/05/2025.
//

#ifndef DATA_H
#define DATA_H

#include <GL/glew.h>

namespace hs::ibl
{
    struct Data
    {
        GLuint environmentMap = 0;
        GLuint irradianceMap = 0;
        GLuint prefilteredMap = 0;
        GLuint brdfLUT = 0;
    };
}

#endif //DATA_H
