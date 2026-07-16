#pragma once
#include <SDL3/SDL.h>

class Window {
public:
    Window() {
        SDL_WindowFlags Flags{
            SDL_WINDOW_RESIZABLE
        };

        SDL_Window* SDLWindow{SDL_CreateWindow(
            "Welcome", 800, 300, Flags
        )};
        
        SDL_GetWindowSurface(SDLWindow);
        SDL_UpdateWindowSurface(SDLWindow);
        SDL_SetWindowResizable(SDLWindow, true);
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    ~Window() {
        SDL_DestroyWindow(SDLWindow);
    }

private:
    SDL_Window* SDLWindow{nullptr};
};