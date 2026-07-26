#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_keyboard.h>
// #include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "window.hpp"
#include "sdl_errorhandler.hpp"
#include "sdl_eventhandler.hpp"

using namespace std;


int main(int, char**) {
    // Initialization
    
    SDL_Init(SDL_INIT_VIDEO); // Initialize SDLVideo
    TTF_Init(); // Initialize SDL Text

    Window Win; // Create the window using the custom Window class
    SDL_EventHandler EventHandler;
    GridArray Grid{24, 14};

    // Application Loop
    SDL_Event Event;

    bool isRunning = true;


    while (isRunning) {
        while(SDL_PollEvent(&Event)) {
            // Exit application loop if SDL detects a quit call
            if(Event.type == SDL_EVENT_QUIT) { 
                isRunning = false;
            }

            Win.inspectorOpened = Grid.inspectorOpened;
            Win.cellExists = Grid.cellExists;
            Win.inspectedCell = Grid.inspectedCell;

            EventHandler.HandleEvent(Event, &Grid, Win.windowBuffer, Win.squareSize, Win.lineSize);
        }

        // Update objects
        Grid.UpdateGrid();

        // Removes existing data on the back buffer by painting it backgroundcolor
        Win.BufferClear(); 

        // Draws objects onto the back buffer
        Win.Render(&Grid);

        // Updates the back buffer onto the screen
        Win.Update();
    }


    // Shutdown
    TTF_Quit(); // Quit SDL Text
    SDL_Quit(); // Quit SDL

    return 0;
};