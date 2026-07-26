#pragma once
#include <cmath>

using namespace std;

class Cell {
public:
    int X; // position in X
    int Y; // position in Y

    int P; // number of protons
    int N; // number of neutrons
    int E; // number of electrons

    int c; // charge

    // the velocity factor is the number of turns it takes for an atom to move one cell in that component direction
    int vx; // velocity factor X component
    int vy; // velocity factor Y component

    int x; // relative x positon
    int y; // relative y position

    int cellID;

    bool isAlive;

    Cell(int posX, int posY, int velocityXFactor, int velocityYFactor, int protons, int neutrons, int electrons, bool alive = true) {
        X = posX;
        Y = posY;
        
        P = protons;
        N = neutrons;
        E = electrons;

        vx = velocityXFactor;
        vy = velocityYFactor;
        c = protons - electrons;

        isAlive = alive;

        cellID = rand() % 100000000001;
    } // transfer all paramters to real variables

    void Update(int gridWidthX, int gridWidthY) {
        x = x + (1/vx);
        y = y + (1/vy);

        if (X == gridWidthX - 1) {
            vx = -vx;
        }

        if (Y == gridWidthY - 1) {
            vy = -vy;
        }
 
        X = floor(x); // rounds down tangible X position value from the relative value
        Y = floor(y); // rounds down tangible Y position value from the relative value

        c = P - E;
    }
};