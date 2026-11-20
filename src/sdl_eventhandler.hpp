#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <iostream>
#include <vector>
#include <string>
#include "colors.hpp"

using namespace std;
class SDL_EventHandler {
public:
    string editingMode = "";
    bool isEditing = false;
    int windowCond = 0;

    bool debugInputsEnabled = true;

    float fillpercent = 0.16f;

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

    void UpdateInspectedCellHandler(GridArray* grid) {
        grid->UpdateInspectedCell(grid->inspectedCell.cellID, 0, 1);
    }

    void HandleEvent(SDL_Event& E, GridArray* grid, int windowBuffer, int squareSize, int lineSize) {
        bool inBounds = MouseInBoudnds(grid, windowBuffer, squareSize);
        
        // Left Click -- Create a new atom
        if (E.type == SDL_EVENT_MOUSE_BUTTON_UP && E.button.button == SDL_BUTTON_LEFT) {
            if (inBounds)
            {
                int gridSquareX = (E.button.x - windowBuffer)/(squareSize);
                int gridSquareY = (E.button.y - windowBuffer)/(squareSize);
 
                cout << "FROM INPUT STACK (LEFT-CLICK CALL): " << std::endl
                << "Input (left-click) registered (x, y): " << E.button.x << "px., " << E.button.y << "px." << std::endl 
                << "Corresponds to input for new atom to be created at (x, y): " << gridSquareX << ", " << gridSquareY << std::endl << std::endl;

                grid->GridAddRemove(gridSquareY, gridSquareX, 1);
                grid->UpdateInspectedCell(gridSquareX, gridSquareY);
                grid->UpdateGrid();
            }
        }

        // Right Click -- Delete an existing atom
        if (E.type == SDL_EVENT_MOUSE_BUTTON_UP && E.button.button == SDL_BUTTON_RIGHT) {
            int mouseX = E.button.x;
            int mouseY = E.button.y;

            if (inBounds) {
                int gridSquareX = (E.button.x - windowBuffer)/(squareSize);
                int gridSquareY = (E.button.y - windowBuffer)/(squareSize);

                cout << "FROM INPUT STACK (RIGHT CLICK CALL): " << std::endl
                << "Input (right-click) registered (x, y): " << E.button.x << "px., " << E.button.y << "px." << std::endl 
                << "Corresponds to input for grid to be cleared at (x, y): " << gridSquareX << ", " << gridSquareY << std::endl << std::endl;

                grid->GridAddRemove(gridSquareY, gridSquareX, 0);
                grid->UpdateInspectedCell(gridSquareX, gridSquareY);
                grid->UpdateGrid();
            }
        }

        // Left CTRL -- Inspect an atom
        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_LCTRL) {
            float mouseX;
            float mouseY;

            SDL_GetMouseState(&mouseX, &mouseY);

            if (inBounds) {
                int gridSquareX = (mouseX - windowBuffer)/(squareSize);
                int gridSquareY = (mouseY - windowBuffer)/(squareSize);

                cout << "FROM INPUT STACK (CTRL/MOUSE HOVER CALL): " << std::endl
                << "Input (right-click) registered (x, y): " << mouseX << "px., " << mouseY << "px." << std::endl 
                << "Corresponds to input for cell to be inspected at (x, y): " << gridSquareX << ", " << gridSquareY << std::endl << std::endl;

                grid->UpdateInspectedCell(gridSquareX, gridSquareY);
                grid->UpdateGrid();
            }
        }

        // Space -- Pause/Unpause
        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_SPACE) {
            grid->isSimulating = !grid->isSimulating;

            if (grid->isSimulating) {
                windowCond = -1;
            }
            else if (grid->isSimulating == false) {
                windowCond = 0;
                grid->UpdateGrid();
            }
        }

        // Q -- Toggle Editing Mode for Protons
        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_Q) {
            if(inBounds) {
                if (isEditing == false) {
                    isEditing = true;
                    windowCond = 1;
                    editingMode = "Proton";
                    cout << "editing protons";
                }
                else if (isEditing == true) {
                    isEditing = false;
                    windowCond = 0;
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
                    windowCond = 2;
                    editingMode = "Neutron";
                    cout << "editing neutrons";
                }
                else if (isEditing == true) {
                    isEditing = false;
                    windowCond = 0;
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
                    windowCond = 3;
                    editingMode = "Electron";
                    cout << "editing electrons";
                }
                else if (isEditing == true) {
                    isEditing = false;
                    windowCond = 0;
                    editingMode = "";
                    cout << "not in editing mode";
                }
            }
        }

        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_R) {
            grid->RandomizeGrid(0.006f);
            grid->UpdateGrid();
        }

        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_C) {
            grid->FullResetGrid();
            grid->UpdateGrid();
        }

        if(debugInputsEnabled) {
            if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_A) {
                grid->PrintCellInfo();
            }
        }
        
        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_UP) {
            cout << "increased";

            grid->EditCell(editingMode, 1);

            grid->UpdateInspectedCell(grid->inspectedCell.cellID, 0, 1);
            grid->UpdateGrid();
        }

        if (E.type == SDL_EVENT_KEY_DOWN && E.key.key == SDLK_DOWN) {
            cout << "decreased";

            grid->EditCell(editingMode, -1);

            grid->UpdateInspectedCell(grid->inspectedCell.cellID, 0, 1);
            grid->UpdateGrid();
        }
    }
};