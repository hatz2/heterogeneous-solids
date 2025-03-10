//
// Created by Alberto Elorza Rubio on 28/12/2023.
//

#ifndef HETEROGENEOUS_SOLIDS_RESOLUTION_H
#define HETEROGENEOUS_SOLIDS_RESOLUTION_H

#include <string>
#include <array>

namespace hs {

    struct Resolution {
        std::string name;
        unsigned int width;
        unsigned int height;
    } const
        square320 {"Square 320", 320, 320},
        square512 {"Square 512", 512, 512},
        square640 {"Square 640", 640, 640},
        SDTV {"SDTV", 640, 480},
        HDTV {"HDTV", 720, 576},
        square800 {"Square 800", 800, 800},
        square1024 {"Square 1024", 1024, 1024},
        tv1024_4_3 {"1024 4:3", 1024, 768},
        HDReady {"HD ready", 1280, 720},
        fullHD {"Full HD", 1920, 1080},
        HD_4_3 {"HD 4:3", 1920, 1440},
        HDVert_4_3 {"HD vertical 4:3", 1440, 1920},
        UWQHD {"UWQHD 21:9", 3440, 1440},
        full4K {"Full 4K (Cinema)", 4096, 2160},
        UHDV4K {"UHDV 4K (TV)", 3840, 2160}
    ;

    const std::array<const Resolution, 15> defaultResolutions = {
        square320, square512, square640, SDTV, HDTV, square800, square1024,
        tv1024_4_3, HDReady, fullHD, HD_4_3, HDVert_4_3, UWQHD, full4K, UHDV4K
    };

} // hs

#endif //HETEROGENEOUS_SOLIDS_RESOLUTION_H
