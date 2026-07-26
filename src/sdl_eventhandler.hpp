#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class SDL_EventHandler {
public:
    string editingMode = "";
    bool isEditing = false;

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
            if (inBounds)
            {
                int gridSquareX = (E.button.x - windowBuffer)/(squareSize);
                int gridSquareY = (E.button.y - windowBuffer)/(squareSize);

                cout << E.button.x << ", " << E.button.y << "\n";
                cout << gridSquareX << ", " << gridSquareY << "\n" << "\n";

                grid->GridAddRemove(gridSquareY, gridSquareX, 1);
            }
        }

        // Right Click -- Delete an existing atom
        if (E.type == SDL_EVENT_MOUSE_BUTTON_UP && E.button.button == SDL_BUTTON_RIGHT) {
            int mouseX = E.button.x;
            int mouseY = E.button.y;

            if (inBounds) {
                int gridSquareX = (E.button.x - windowBuffer)/(squareSize);
                int gridSquareY = (E.button.y - windowBuffer)/(squareSize);

                cout << E.button.x << ", " << E.button.y << "\n";
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

        // Space -- Pause/Unpause
        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_SPACE) {
            grid->isSimulating = !grid->isSimulating;
        }

        // A -- Toggle Editing Mode for Velocity Factor X Component
        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_A) {
            if(inBounds) {
                if (isEditing == false) {
                    isEditing = true;
                    editingMode = "VelFactorX";
                    cout << "editing vfx";
                }
                else if (isEditing == true) {
                    isEditing = false;
                    editingMode = "";
                    cout << "not in editing mode";
                }
            }
        }

        // S -- Toggle Editing Mode for Velocity Factor Y Component
        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_S) {
            if(inBounds) {
                if (isEditing == false) {
                    isEditing = true;
                    editingMode = "VelFactorY";
                    cout << "editing vfy";
                }
                else if (isEditing == true) {
                    isEditing = false;
                    editingMode = "";
                    cout << "not in editing mode";
                }
            }
        }

        // Q -- Toggle Editing Mode for Protons
        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_Q) {
            if(inBounds) {
                if (isEditing == false) {
                    isEditing = true;
                    editingMode = "Proton";
                    cout << "editing protons";
                }
                else if (isEditing == true) {
                    isEditing = false;
                    editingMode = "";
                    cout << "not in editing mode";
                }
            }
        }

        // W -- Toggle Editing Mode for Neutrons
        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_W) {
            if(inBounds) {
                if (isEditing == false) {
                    isEditing = true;
                    editingMode = "Neutron";
                    cout << "editing neutrons";
                }
                else if (isEditing == true) {
                    isEditing = false;
                    editingMode = "";
                    cout << "not in editing mode";
                }
            }
        }

        // E -- Toggle Editing Mode for Electrons
        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_E) {
            if(inBounds) {
                if (isEditing == false) {
                    isEditing = true;
                    editingMode = "Electron";
                    cout << "editing electrons";
                }
                else if (isEditing == true) {
                    isEditing = false;
                    editingMode = "";
                    cout << "not in editing mode";
                }
            }
        }

        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_UP) {
            cout << "increased";

            grid->EditCell(editingMode, 1);
        }

        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_DOWN) {
            cout << "decreased";

            grid->EditCell(editingMode, -1);
        }
    }
};