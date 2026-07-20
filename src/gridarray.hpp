#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

using namespace std;

class GridArray {
public:
    vector<vector<int>> arrayIndex;
    int WidthX;
    int WidthY;

    GridArray(int widthX, int widthY) {
        WidthX = widthX;
        WidthY = widthY;

        for (int y = 0; y < widthY; y++) {
            vector<int> newRow = {};

            for (int x = 0; x < widthX; x++) {
                newRow.push_back(1);
            }

            arrayIndex.push_back(newRow);
        }
    }

    void GridModify(int rowY, int columnX, int value) {
        arrayIndex[rowY][columnX] = value;

        cout << "grid has been modified";
    }

    int RetrieveValue(int rowY, int columnX) {
        return arrayIndex[rowY][columnX];
    }
};