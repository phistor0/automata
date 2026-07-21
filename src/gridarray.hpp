#pragma once

#include "cell.hpp"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

using namespace std;

class GridArray {
public:
    vector<vector<int>> arrayIndex;

    vector<Cell> cellIndex;

    int WidthX;
    int WidthY;

    int numCells = 0;

    GridArray(int widthX, int widthY) {
        WidthX = widthX;
        WidthY = widthY;

        for (int y = 0; y < widthY; y++) {
            vector<int> newRow = {};

            for (int x = 0; x < widthX; x++) {
                newRow.push_back(0);
            }

            arrayIndex.push_back(newRow);
        }
    }

    void GridAddRemove(int rowY, int columnX, int value) {
        if (value == 0 && arrayIndex[rowY][columnX] == 1) {
            for (int i = 0; i < cellIndex.size(); i++) {
                if (cellIndex[i].X == columnX && cellIndex[i].Y == rowY) {
                    cellIndex.erase(cellIndex.begin() + i);
                    break;
                }
            }

            cout << cellIndex.size() << "\n";
        }

        if (value == 1 && arrayIndex[rowY][columnX] == 0) {            
            cellIndex.push_back(Cell{columnX, rowY, 0, 0, 1, 1, 1});

            cout << cellIndex.size() << "\n";
        }

        arrayIndex[rowY][columnX] = value;

        cout << "grid has been modified";
    }

    int RetrieveValue(int rowY, int columnX) {
        return arrayIndex[rowY][columnX];
    }

    void UpdateGrid() {
        for (int y = 0; y < WidthY; y++) {
            vector<int> newRow = {};

            for (int x = 0; x < WidthX; x++) {
                newRow.push_back(0);
            }

            arrayIndex.push_back(newRow);
        }

        for (int i = 0; i < cellIndex.size(); i++) {
            arrayIndex[cellIndex[i].Y][cellIndex[i].X] = 1;
        }
    }
};