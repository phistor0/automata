#pragma once

#include <SDL3/SDL.h>

#include <iostream>
#include <vector>

#include "colors.hpp"
#include "sdl_errorhandler.hpp"
#include "gridarray.hpp"
#include "text.hpp"
#include "cell.hpp"

using namespace std;

class Window {
public:
    int windowBuffer{50};
    int squareSize{50};
    int lineSize{5};
    int boxSizeX{400};
    int boxSizeY{500};

    int textBuffer{30};
    float textHeaderSize{38.0f};
    float textBodySize{25.0f};

    bool inspectorOpened = false;
    bool cellExists = false;

    Cell inspectedCell{0, 0, 0, 0, 0, 0, 0, false};

    // Window constructor
    Window() {
        SDL_WindowFlags Flags{
            SDL_WINDOW_RESIZABLE
        }; // Flags for the SDL window

        SDLWindow = SDL_CreateWindow(
            "Automata", 800, 300, Flags
        ); // Create the window       
    } 

    // Simple function to get the window surface
    SDL_Surface* GetSurface() const {
        return SDL_GetWindowSurface(SDLWindow);
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    // Removes existing data on the back buffer by painting it backgroundcolor
    void BufferClear() {
        const SDL_PixelFormatDetails* PixelFmtDetails{
            SDL_GetPixelFormatDetails(GetSurface()->format)
        };

        SDL_FillSurfaceRect(
            GetSurface(),
            nullptr,
            GetColor(0, PixelFmtDetails)
        );
    }

    // Draws objects onto the back buffer
    void Render(GridArray* grid) {
        const SDL_PixelFormatDetails* PixelFmtDetails{
            SDL_GetPixelFormatDetails(GetSurface()->format)
        };

        const SDL_Rect background{windowBuffer, windowBuffer, squareSize * grid->WidthX, squareSize * grid->WidthY};
        SDL_FillSurfaceRect(GetSurface(), &background, GetColor(2, PixelFmtDetails));  

        for (int y = 0; y < (grid->WidthY); y++) {
            vector<int> row;
            row = grid->arrayIndex[y];
            for (int x = 0; x < (grid->WidthX); x++) {
                if (row[x] == 1) {
                    const SDL_Rect cell{windowBuffer + (x * squareSize), windowBuffer + (y * squareSize), squareSize, squareSize};
                    SDL_FillSurfaceRect(GetSurface(), &cell, GetColor(3, PixelFmtDetails));
                }
            }
        }

        for (int x = 0; x < (grid->WidthY + 1); x++) {
            const SDL_Rect line{windowBuffer, windowBuffer + (squareSize * x), grid->WidthX * squareSize, lineSize};
            SDL_FillSurfaceRect(GetSurface(), &line, GetColor(1, PixelFmtDetails));
        }

        for (int y = 0; y < (grid->WidthX + 1); y++) {
            const SDL_Rect line{windowBuffer + (squareSize * y), windowBuffer, lineSize, grid->WidthY * squareSize};
            SDL_FillSurfaceRect(GetSurface(), &line, GetColor(1, PixelFmtDetails));
        }

        const SDL_Rect line{windowBuffer + (squareSize * grid->WidthX), windowBuffer + (squareSize * grid->WidthY), lineSize, lineSize};
        SDL_FillSurfaceRect(GetSurface(), &line, GetColor(1, PixelFmtDetails));  

        const SDL_Rect infobox{(windowBuffer * 2) + (squareSize * grid->WidthX), windowBuffer, boxSizeX, boxSizeY};
        SDL_FillSurfaceRect(GetSurface(), &infobox, GetColor(1, PixelFmtDetails));

        Text headerText{"Inspector: ", (windowBuffer * 2) + textBuffer + (squareSize * grid->WidthX), windowBuffer + textBuffer, textHeaderSize};
        headerText.Render(GetSurface());

        if (inspectorOpened == false) {
            Text inspectorHeader{"No atom inspected yet.", (windowBuffer * 2) + textBuffer + (squareSize * grid->WidthX), windowBuffer + static_cast<int>(std::round(textHeaderSize)) + (textBuffer * 2), textBodySize};
            inspectorHeader.Render(GetSurface());
        }

        else if (inspectorOpened == true && cellExists == false) {
            Text inspectorHeader{"No atom exists in this space.", (windowBuffer * 2) + textBuffer + (squareSize * grid->WidthX), windowBuffer + static_cast<int>(std::round(textHeaderSize)) + (textBuffer * 2), textBodySize};
            
            inspectorHeader.Render(GetSurface());
        }
        else if (inspectorOpened == true && cellExists == true) {
            Text inspectorHeader{"Atom #: " + std::to_string(inspectedCell.cellID), (windowBuffer * 2) + textBuffer + (squareSize * grid->WidthX), windowBuffer + static_cast<int>(std::round(textHeaderSize)) + (textBuffer * 2), textBodySize};

            Text trans{"Transform: " + std::to_string(inspectedCell.X) + ", " + std::to_string(inspectedCell.Y), (windowBuffer * 2) + textBuffer + (squareSize * grid->WidthX), windowBuffer + static_cast<int>(std::round(textBodySize)) + static_cast<int>(std::round(textHeaderSize)) + (textBuffer * 4), textBodySize};
            Text vel{"Velocity: " + std::to_string(inspectedCell.vx) + ", " + std::to_string(inspectedCell.vy), (windowBuffer * 2) + textBuffer + (squareSize * grid->WidthX), windowBuffer + static_cast<int>(std::round(textBodySize * 2)) + static_cast<int>(std::round(textHeaderSize)) + (textBuffer * 4), textBodySize};
            
            Text pro{"Protons: " + std::to_string(inspectedCell.P), (windowBuffer * 2) + textBuffer + (squareSize * grid->WidthX), windowBuffer + static_cast<int>(std::round(textBodySize * 3)) + static_cast<int>(std::round(textHeaderSize)) + (textBuffer * 5), textBodySize};
            Text neu{"Neutrons: " + std::to_string(inspectedCell.N), (windowBuffer * 2) + textBuffer + (squareSize * grid->WidthX), windowBuffer + static_cast<int>(std::round(textBodySize * 4)) + static_cast<int>(std::round(textHeaderSize)) + (textBuffer * 5), textBodySize};
            Text elec{"Electrons: " + std::to_string(inspectedCell.E), (windowBuffer * 2) + textBuffer + (squareSize * grid->WidthX), windowBuffer + static_cast<int>(std::round(textBodySize * 5)) + static_cast<int>(std::round(textHeaderSize)) + (textBuffer * 5), textBodySize};
            
            inspectorHeader.Render(GetSurface());
            trans.Render(GetSurface());
            vel.Render(GetSurface());
            pro.Render(GetSurface());
            neu.Render(GetSurface());
            elec.Render(GetSurface());
        }
    }

    // Updates the back buffer onto the screen
    void Update() {
        SDL_UpdateWindowSurface(SDLWindow);
    }

    // Window destructor
    ~Window() {
        cout << "Destructor Called" << '\n!';

        SDL_DestroyWindow(SDLWindow); // Remove the Window
    }

private:
    SDL_Window* SDLWindow{nullptr};
};