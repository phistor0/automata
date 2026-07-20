#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <iostream>
#include <vector>

using namespace std;

class SDL_EventHandler {
public:
    bool KEYS[322];

    SDL_EventHandler() {
        for (int i = 0; i < 322; i++) {
            KEYS[i] = false;
        } 
    }

    void KeyIn(int key, bool status) {
        KEYS[key] = status;
    };

    bool KeyOut(int key) {
        return KEYS[key];
    }

    void HandleEvent(SDL_Event& E, GridArray* grid, int windowBuffer, int squareSize, int lineSize) {
        if (E.type == SDL_EVENT_MOUSE_BUTTON_UP && E.button.button == SDL_BUTTON_LEFT) {
            int mouseX = E.button.x;
            int mouseY = E.button.y;

            if (mouseX > windowBuffer && 
                mouseY > windowBuffer && 
                mouseX < ((grid->WidthX * squareSize) + windowBuffer) &&
                mouseY < ((grid->WidthY * squareSize) + windowBuffer)
            ) {
                int gridSquareX = (mouseX - windowBuffer)/(squareSize);
                int gridSquareY = (mouseY - windowBuffer)/(squareSize);

                cout << mouseX << ", " << mouseY << "\n";
                cout << gridSquareX << ", " << gridSquareY << "\n" << "\n";

                grid->GridModify(gridSquareY, gridSquareX, 2);
            }
        }
    }
};