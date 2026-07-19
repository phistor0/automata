#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>

class Keys {
public:
    bool KEYS[322];

    Keys() {
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
};