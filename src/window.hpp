#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include "colors.hpp"
#include "sdl_errorhandler.hpp"
#include "gridarray.hpp"

using namespace std;

class Window {
public:
    int windowBuffer{50};
    int squareSize{50};
    int lineSize{5};

    // Window constructor
    Window() {
        SDL_WindowFlags Flags{
            SDL_WINDOW_RESIZABLE
        }; // Flags for the SDL window

        SDLWindow = SDL_CreateWindow(
            "Automata", 800, 300, Flags
        ); // Create the window       
    } 

    // Simple function to get the window surface
    SDL_Surface* GetSurface() const {
        return SDL_GetWindowSurface(SDLWindow);
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Removes existing data on the back buffer by painting it backgroundcolor
    void BufferClear() {
        const SDL_PixelFormatDetails* PixelFmtDetails{
            SDL_GetPixelFormatDetails(GetSurface()->format)
        };

        SDL_FillSurfaceRect(
            GetSurface(),
            nullptr,
            GetColor(0, PixelFmtDetails)
        );
    }

    // Draws objects onto the back buffer
    void Render(GridArray grid) {
        const SDL_PixelFormatDetails* PixelFmtDetails{
            SDL_GetPixelFormatDetails(GetSurface()->format)
        };

        const SDL_Rect background{windowBuffer, windowBuffer, squareSize * grid.WidthX, squareSize * grid.WidthY};
        SDL_FillSurfaceRect(GetSurface(), &background, GetColor(2, PixelFmtDetails));  

        for (int x = 0; x < (grid.WidthY + 1); x++) {
            const SDL_Rect line{windowBuffer, windowBuffer + (squareSize * x), grid.WidthX * squareSize, lineSize};
            SDL_FillSurfaceRect(GetSurface(), &line, GetColor(1, PixelFmtDetails));
        }

        for (int y = 0; y < (grid.WidthX + 1); y++) {
            const SDL_Rect line{windowBuffer + (squareSize * y), windowBuffer, lineSize, grid.WidthY * squareSize};
            SDL_FillSurfaceRect(GetSurface(), &line, GetColor(1, PixelFmtDetails));
        }

        const SDL_Rect line{windowBuffer + (squareSize * grid.WidthX), windowBuffer + (squareSize * grid.WidthY), lineSize, lineSize};
        SDL_FillSurfaceRect(GetSurface(), &line, GetColor(1, PixelFmtDetails));        
    }

    // Updates the back buffer onto the screen
    void Update() {
        SDL_UpdateWindowSurface(SDLWindow);
    }

    // Window destructor
    ~Window() {
        cout << "Destructor Called" << '\n!';

        SDL_DestroyWindow(SDLWindow); // Remove the Window
    }

private:
    SDL_Window* SDLWindow{nullptr};
};