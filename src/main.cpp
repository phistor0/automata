#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_keyboard.h>
#include "window.hpp"
#include "sdl_errorhandler.hpp"
// #include <SDL3_image/SDL_image.h>
// #include <SDL3_ttf/SDL_ttf.h>

#include "window.hpp";

using namespace std;


void HandleEvent(SDL_Event& E) {
    if (E.type == SDL_EVENT_KEY_DOWN) {
        cout << "Keydown." << "\n";
    }
}

int main(int, char**) {
    // Initialization
    
    SDL_Init(SDL_INIT_VIDEO); // Initialize SDLVideo
    Window GameWindow; // Create the window using the custom Window class

    // Application Loop
    SDL_Event Event;
    bool isRunning = true;
    while (isRunning) {
        while(SDL_PollEvent(&Event)) {
            // Exit application loop if SDL detects a quit call
            if(Event.type == SDL_EVENT_QUIT) { 
                isRunning = false;
            }

            HandleEvent(Event);
        }

        // Update objects

        // Render Changes
    }


    // Shutdown
    SDL_Quit(); // Quit SDL

    return 0;
};