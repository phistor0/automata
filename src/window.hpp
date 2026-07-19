#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include "colors.hpp"
#include "sdl_errorhandler.hpp"

using namespace std;

class Window {
public:
    // Window constructor
    Window() {
        SDL_WindowFlags Flags{
            SDL_WINDOW_RESIZABLE
        }; // Flags for the SDL window

        SDLWindow = SDL_CreateWindow(
            "Automata", 800, 300, Flags
        ); // Create the window

        // Creates the format details for when we draw on the surface
        const SDL_PixelFormatDetails* PixelFmtDetails{
            SDL_GetPixelFormatDetails(GetSurface()->format)
        };

        SDL_FillSurfaceRect(
            GetSurface(),
            nullptr,
            GetColor(0, PixelFmtDetails)
        );

        SDL_UpdateWindowSurface(SDLWindow);
    }

    // Simple function to get the window surface
    SDL_Surface* GetSurface() const {
        return SDL_GetWindowSurface(SDLWindow);
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Window destructor
    ~Window() {
        cout << "Destructor Called" << '\n!';

        SDL_DestroyWindow(SDLWindow); // Remove the Window
    }

private:
    SDL_Window* SDLWindow{nullptr};
};