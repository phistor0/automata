#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "window.hpp"
#include "sdl_errorhandler.hpp"
// #include <SDL3_image/SDL_image.h>
// #include <SDL3_ttf/SDL_ttf.h>

#include "window.hpp";

using namespace std;

int main(int, char**) {
    SDL_Init(SDL_INIT_VIDEO); // Initialize SDLVideo
    Window GameWindow; // Create the window using the custom Window class

    bool isRunning = true;
    SDL_Event Event;
    while (isRunning) {
        while(SDL_PollEvent(&Event)) {
            if(Event.type == SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }
    }

    SDL_Quit(); // Quit SDL

    return 0;
};