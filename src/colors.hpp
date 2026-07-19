#pragma once
#include <SDL3/SDL.h>

Uint32 GetColor(int colorValue, const SDL_PixelFormatDetails* formatDetails) {
    if (colorValue == 0) { // background
        Uint32 backgroundColor {SDL_MapRGB(
            formatDetails,
            nullptr,
            8,
            8,
            87
        )};

        return backgroundColor;
    }

    else if (colorValue == 1) { // grid
        Uint32 gridColor {SDL_MapRGB(
            formatDetails,
            nullptr,
            180,
            180,
            180
        )};

        return gridColor;
    }

    else if (colorValue == 2) { // empty cells
        Uint32 cellColor {SDL_MapRGB(
            formatDetails,
            nullptr,
            35,
            35,
            35
        )};

        return cellColor;
    }

    else if (colorValue == 3) { // life
        Uint32 lifeColor {SDL_MapRGB(
            formatDetails,
            nullptr,
            255,
            255,
            255
        )};

        return lifeColor;
    }

    else { // else
        Uint32 backgroundColor {SDL_MapRGB(
            formatDetails,
            nullptr,
            8,
            8,
            87
        )};

        return backgroundColor;
    }
}