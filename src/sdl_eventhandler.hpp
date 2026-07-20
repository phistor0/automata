#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <iostream>

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

    void HandleEvent(SDL_Event& E, int windowBuffer, int squareSize, int lineSize, int gridWidthX, int gridWidthY) {
        if (E.type == SDL_EVENT_MOUSE_BUTTON_UP && E.button.button == SDL_BUTTON_LEFT) {
            int mouseX = E.button.x;
            int mouseY = E.button.y;

            if (mouseX > windowBuffer && 
                mouseY > windowBuffer && 
                mouseX < ((gridWidthX * squareSize) + (gridWidthX * lineSize) - windowBuffer) &&
                mouseY < ((gridWidthY * squareSize) + (gridWidthX * lineSize) - windowBuffer)
            ) {
                // int gridSquareX = (mouseX - windowBuffer)/(squareSize + lineSize);

                cout << mouseX << ", " << mouseY << "\n";
            }
        }
    }
};