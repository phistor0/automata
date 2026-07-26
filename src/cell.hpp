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
    float vx; // velocity factor X component
    float vy; // velocity factor Y component

    float x; // relative x positon
    float y; // relative y position

    int cellID;

    bool isAlive;

    Cell(int posX, int posY, int velocityXFactor, int velocityYFactor, int protons, int neutrons, int electrons, bool alive = true) {
        x = posX;
        y = posY;

        X = floor(x); // rounds down tangible X position value from the relative value
        Y = floor(y); // rounds down tangible Y position value from the relative value
        
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
        if(vx != 0) {x += (1/vx);}
        if(vy != 0) {y += (1/vy);}
 
        X = floor(x); // rounds down tangible X position value from the relative value
        Y = floor(y); // rounds down tangible Y position value from the relative value

        if (X == gridWidthX - 1 || X == 0) {
            vx = -vx;
        }

        if (Y == gridWidthY - 1 || X == 0) {
            vy = -vy;
        }

        c = P - E;

        cout << "updating: " << cellID;
    }
};