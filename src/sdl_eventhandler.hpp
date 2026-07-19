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

    void HandleEvent(SDL_Event& E) {
        if (E.type == SDL_EVENT_KEY_DOWN) {
            cout << "Keydown." << E.key.key << "\n";
            KeyIn(E.key.key, true);
        }
        if (E.type == SDL_EVENT_KEY_UP) {
            cout << "Keydown." << E.key.key << "\n";
            KeyIn(E.key.key, false);
        }
    }
};