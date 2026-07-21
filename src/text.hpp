#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>

class Text {
public:
    Text(const std::string& Content, int posX, int posY, float FontSize = 100.0f) : Font{LoadFont(FontSize)} {
        CreateSurface(Content);

        DestinationRectangle.x = posX;
        DestinationRectangle.y = posY;
    }

    void SetFontSize(float NewSize) {
        TTF_SetFontSize(Font, NewSize);
    }

    void Render(SDL_Surface* DestinationSurface) {
        if (!TextSurface) return;

        SDL_BlitSurface(
            TextSurface, nullptr,
            DestinationSurface, &DestinationRectangle
        );
    }

    ~Text() {
        SDL_DestroySurface(TextSurface);
        if (TTF_WasInit()) {
            TTF_CloseFont(Font);
        }
    }

    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;

protected:
    Text(float FontSize) : Font{LoadFont(FontSize)} {}

    TTF_Font* LoadFont(float FontSize) {
        TTF_Font* LoadedFont{TTF_OpenFont("Arimo-VariableFont_wght.ttf", FontSize)};

        if (!LoadedFont) {
            std::cout << "Error loading font: " << SDL_GetError() << '\n';
        }

        return LoadedFont;
    }

    void CreateSurface(const std::string& Content) {
        SDL_DestroySurface(TextSurface);

        TextSurface = TTF_RenderText_Blended(Font, Content.c_str(), 0, {255, 255, 255, 255});
        if (!TextSurface) {
            std::cout << "Error creating TextSurface: " << SDL_GetError() << '\n';
        }
    }

    TTF_Font* Font{nullptr};
    SDL_Surface* TextSurface{nullptr};
    SDL_Rect DestinationRectangle{0, 0, 0, 0};
};