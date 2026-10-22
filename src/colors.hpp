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
            67,
            67,
            92
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

    else if (colorValue == 4) { // status
        Uint32 statusColor {SDL_MapRGB(
            formatDetails,
            nullptr,
            255,
            0,
            0
        )};

        return statusColor;
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

Uint32 DetermineCellColor(int protons, int neutrons, int electrons, const SDL_PixelFormatDetails* formatDetails) {
    Uint32 cellColor {SDL_MapRGB(
        formatDetails,
        nullptr,
        (protons * 50),
        (neutrons * 50),
        (electrons * 50)
    )};

    return cellColor;
}

SDL_Color UintToColor(Uint32 color)
{
	SDL_Color tempcol;
	tempcol.a = 255;
	tempcol.r = (color >> 16) & 0xFF;
	tempcol.g = (color >> 8) & 0xFF;
	tempcol.b = color & 0xFF;
	return tempcol;
}
