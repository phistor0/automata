#pragma once

#include "cell.hpp"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class GridArray {
public:
    vector<vector<int>> arrayIndex;

    vector<Cell> cellIndex;

    int WidthX;
    int WidthY;

    int numCells = 0;

    bool inspectorOpened = false;
    bool cellExists = false;
    Cell inspectedCell{0, 0, 0, 0, 1, 1, 1, false};
    Cell* inspectedCellPtr;

    bool isSimulating = false;

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

    void UpdateInspectedCell(int xORcellID, int y, int mode = 0) {
        for (int i = 0; i < cellIndex.size(); i++) {
            if (mode == 0) {
                if (cellIndex[i].X == xORcellID && cellIndex[i].Y == y) {
                    inspectedCellPtr = &cellIndex[i];
                    inspectedCell = *inspectedCellPtr;
                    
                    cellExists = true;
                    break;
                }
                else {
                    cellExists = false;
                }
            }
            if (mode == 1) {
                if (cellIndex[i].cellID == xORcellID) {
                    inspectedCellPtr = &cellIndex[i];
                    inspectedCell = cellIndex[i];
                    
                    cellExists = true;
                    break;
                }
                else {
                    cellExists = false;
                }
            }
        }
    }

    void EditCell(string editMode, int modifier) {
        if (editMode == "Proton") {
            inspectedCellPtr->P = inspectedCellPtr->P + modifier;
            UpdateInspectedCell(inspectedCellPtr->X, inspectedCellPtr->Y);
        }
        if (editMode == "Neutron") {
            inspectedCellPtr->N = inspectedCellPtr->N + modifier;
            UpdateInspectedCell(inspectedCellPtr->X, inspectedCellPtr->Y);
        }
        if (editMode == "Electron") {
            inspectedCellPtr->E = inspectedCellPtr->E + modifier;
            UpdateInspectedCell(inspectedCellPtr->X, inspectedCellPtr->Y);
        }
        else {
            cout << "not editing";
        }
    }

    bool HasOverlaps() {
        for (int a = 0; a < static_cast<int>(cellIndex.size()); a++) {
            for (int b = a + 1;
                b < static_cast<int>(cellIndex.size());
                b++) {

                if (cellIndex[a].X == cellIndex[b].X &&
                    cellIndex[a].Y == cellIndex[b].Y) {
                    return true;
                }
            }
        }

        return false;
    }

    bool IsOccupied(int x, int y, int exceptIndex) const {
        for (int i = 0; i < static_cast<int>(cellIndex.size()); i++) {
            if (i == exceptIndex) {
                continue;
            }

            if (cellIndex[i].X == x && cellIndex[i].Y == y) {
                return true;
            }
        }

        return false;
    }

    bool MoveToNearestFreeSquare(int index) {
        Cell& movingCell = cellIndex[index];

        int bestX = -1;
        int bestY = -1;
        int bestDistance = WidthX + WidthY + 1;

        // Search every square on the grid.
        for (int y = 0; y < WidthY; y++) {
            for (int x = 0; x < WidthX; x++) {

                if (IsOccupied(x, y, index)) {
                    continue;
                }

                // Manhattan distance from the current square.
                int distance =
                    abs(x - movingCell.X) +
                    abs(y - movingCell.Y);

                if (distance < bestDistance) {
                    bestDistance = distance;
                    bestX = x;
                    bestY = y;
                }
            }
        }

        // No unoccupied square exists.
        if (bestX == -1) {
            return false;
        }

        // Update both grid and relative positions.
        movingCell.X = bestX;
        movingCell.Y = bestY;

        // Place the atom at the center of the new square.
        movingCell.x = bestX + 0.5f;
        movingCell.y = bestY + 0.5f;

        return true;
    }

    bool HasHigherPriority(int a, int b) const {
        const Cell& A = cellIndex[a];
        const Cell& B = cellIndex[b];

        int massA = A.P + A.N;
        int massB = B.P + B.N;

        if (massA != massB) {
            return massA > massB;
        }

        if (A.E != B.E) {
            return A.E > B.E;
        }

        // Deterministic tie-breaker.
        if (A.cellID != B.cellID) {
            return A.cellID < B.cellID;
        }

        // Handle the unlikely event of duplicate cell IDs.
        return a < b;
    }

    void UpdateGrid() {
        // reset arrayIndex
        arrayIndex.clear();

        for (int y = 0; y < WidthY; y++) {
            vector<int> newRow = {};

            for (int x = 0; x < WidthX; x++) {
                newRow.push_back(0);
            }

            arrayIndex.push_back(newRow);
        }

        if (isSimulating) {
            // modify positions of all atoms
            cout << "Updating all cells: " << "\n";

            // reset velocities
            for (int a = 0; a < cellIndex.size(); a++) {
                cellIndex[a].AtomVelReset();
            }

            // calculate velocity of each cell based on neighbors
            for (int a = 0; a < cellIndex.size(); a++) {
                for (int b = a + 1; b < cellIndex.size(); b++) {
                    cellIndex[a].AtomInteraction(cellIndex[b]);
                    cellIndex[b].AtomInteraction(cellIndex[a]);
                }
            }
            
            // update positions of all cells
            for (int a = 0; a < cellIndex.size(); a++) {
                cellIndex[a].Update(WidthX, WidthY);
            }

            int iterations = 0;
            const int maxIterations =
                static_cast<int>(cellIndex.size() * cellIndex.size()) + 1;

            bool failed = false;

            while (HasOverlaps() &&
                iterations < maxIterations &&
                !failed) {

                bool changed = false;

                for (int a = 0;
                    a < static_cast<int>(cellIndex.size()) && !failed;
                    a++) {

                    for (int b = a + 1;
                        b < static_cast<int>(cellIndex.size());
                        b++) {

                        if (cellIndex[a].X != cellIndex[b].X ||
                            cellIndex[a].Y != cellIndex[b].Y) {
                            continue;
                        }

                        // Keep the higher-priority atom in place.
                        int loser = HasHigherPriority(a, b) ? b : a;

                        if (MoveToNearestFreeSquare(loser)) {
                            changed = true;
                        }
                        else {
                            cout << "Collision resolution failed: "
                                << "no free grid square exists.\n";
                            failed = true;
                            break;
                        }
                    }
                }

                if (!changed && HasOverlaps()) {
                    cout << "Collision resolution stalled.\n";
                    break;
                }

                iterations++;
            }

            if (HasOverlaps()) {
                cout << "WARNING: Overlaps remain after "
                    << iterations << " iterations.\n";
            }

            cout << "Updated all cells." << "\n\n";
        }
        
        int inspCellID = inspectedCell.cellID;
        UpdateInspectedCell(inspCellID, 0, 1);
            
        // update arrayIndex with positions of all atoms
        for (int i = 0; i < cellIndex.size(); i++) {
            arrayIndex[cellIndex[i].Y][cellIndex[i].X] = 1;
        }
    }
};