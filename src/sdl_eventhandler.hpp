#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <iostream>
#include <vector>

using namespace std;

class SDL_EventHandler {
public:
    SDL_EventHandler() {

    }
    
    bool MouseInBoudnds(GridArray* grid, int windowBuffer, int squareSize) {
        float mouseX;
        float mouseY;

        SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseX > windowBuffer && 
            mouseY > windowBuffer && 
            mouseX < ((grid->WidthX * squareSize) + windowBuffer) &&
            mouseY < ((grid->WidthY * squareSize) + windowBuffer)
        ) {
            return true;
        }
        else {
            return false;
        }
    }

    void HandleEvent(SDL_Event& E, GridArray* grid, int windowBuffer, int squareSize, int lineSize) {
        bool inBounds = MouseInBoudnds(grid, windowBuffer, squareSize);
        
        // Left Click -- Create a new atom
        if (E.type == SDL_EVENT_MOUSE_BUTTON_UP && E.button.button == SDL_BUTTON_LEFT) {
            int mouseX = E.button.x;
            int mouseY = E.button.y;
            
            if (inBounds)
            {
                int gridSquareX = (mouseX - windowBuffer)/(squareSize);
                int gridSquareY = (mouseY - windowBuffer)/(squareSize);

                cout << mouseX << ", " << mouseY << "\n";
                cout << gridSquareX << ", " << gridSquareY << "\n" << "\n";

                grid->GridAddRemove(gridSquareY, gridSquareX, 1);
            }
        }

        // Right Click -- Delete an existing atom
        if (E.type == SDL_EVENT_MOUSE_BUTTON_UP && E.button.button == SDL_BUTTON_RIGHT) {
            int mouseX = E.button.x;
            int mouseY = E.button.y;

            if (inBounds) {
                int gridSquareX = (mouseX - windowBuffer)/(squareSize);
                int gridSquareY = (mouseY - windowBuffer)/(squareSize);

                cout << mouseX << ", " << mouseY << "\n";
                cout << gridSquareX << ", " << gridSquareY << "\n" << "\n";

                grid->GridAddRemove(gridSquareY, gridSquareX, 0);
            }
        }

        // Left CTRL -- Inspect an atom
        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_LCTRL) {
            float mouseX;
            float mouseY;

            SDL_GetMouseState(&mouseX, &mouseY);

            if (inBounds) {
                cout << "inspector opened" << "\n";

                grid->inspectorOpened = true;

                int gridSquareX = (mouseX - windowBuffer)/(squareSize);
                int gridSquareY = (mouseY - windowBuffer)/(squareSize);

                grid->UpdateInspectedCell(gridSquareX, gridSquareY);
            }
        }
    }
};