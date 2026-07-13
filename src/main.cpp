#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

using namespace std;

int main(int, char**) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* Window{SDL_CreateWindow(
        "Welcome", 800, 300, 0
    )};
    SDL_GetWindowSurface(Window);
    SDL_UpdateWindowSurface(Window);

    bool isRunning = true;
    SDL_Event Event;
    while (isRunning) {
        while(SDL_PollEvent(&Event)) {
            if(Event.type = SDL_EVENT_QUIT) {
                isRunning = false;
            }
        }
    }

    SDL_DestroyWindow(Window);
    SDL_Quit();

    return 0;
};