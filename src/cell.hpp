#pragma once
#include <cmath>
#include <iostream>

using namespace std;

class Cell {
public:
    int X; // position in X
    int Y; // position in Y

    int P; // number of protons
    int N; // number of neutrons
    int E; // number of electrons

    int c; // charge
    int s;

    float v;

    float x; // relative x positon
    float y; // relative y position

    int cellID;

    bool isAlive;

    float modX = 0;
    float modY = 0;
    float modE = 0;
    float modT = 0;

    int oldX;
    int oldY;

    int oldx;
    int oldy;

    float vE = 0;

    Cell(int posX, int posY, int velocity, int velocityYFactor, int protons, int neutrons, int electrons, bool alive = true) {
        x = posX;
        y = posY;

        X = floor(x); // rounds down tangible X position value from the relative value
        Y = floor(y); // rounds down tangible Y position value from the relative value
        
        P = protons;
        N = neutrons;
        E = electrons;

        v = velocity;
        c = protons - electrons;

        isAlive = alive;

        cellID = rand() % 100000000001;

        s = 0;
    } // transfer all paramters to real variables

    void AtomVelReset() {
        v = 0;

        modX = 0;
        modY = 0;
        modE = 0;
        modT = 0;
        vE = 0;

        s = 0;

        c = P - E;

        oldX = X;
        oldY = Y;

        oldx = x;
        oldy = y;
    }

    void AtomInteraction(Cell iAtom) {
        s = P + N + iAtom.P + iAtom.N;

        modX += iAtom.X - X; 
        modY += iAtom.Y - Y; 

        // X
        if (c < 0 && iAtom.c < 0 || c > 0 && iAtom.c > 0) {
            // repel
            v -= s;
        }

        else if (c < 0 && iAtom.c > 0 || c > 0 && iAtom.c < 0) {
            // attract
            v += s;
        }

        cout << "s" << s;
    }

    float Relativize(float vel, float mod, float euc, float tot) {
        vE = (2.0/3.14159f)*(std::atanf(((1.0f)/(72.0f * euc))*(pow(vel, 3.0f))));
        
        if (mod == 0) {
            return 0;
        }
        else {
            return (mod/tot)*vE;
            // return 0.05f*vel*mod;
        }   
    }

    void Update(int gridWidthX, int gridWidthY) {
        modE = sqrt((pow(modX, 2) + pow(modY, 2)));
        modT = abs(modX) + abs(modY);

        x += Relativize(v, modX, modE, modT);
        y += Relativize(v, modY, modE, modT);
        
        // Clamp the relative positions
        x = max(0.0f, min(x, static_cast<float>(gridWidthX) - 0.001f));
        y = max(0.0f, min(y, static_cast<float>(gridWidthY) - 0.001f));

        X = floor(x); // rounds down tangible X position value from the relative value
        Y = floor(y); // rounds down tangible Y position value from the relative value

        c = P - E;

        cout << "updating: " << cellID << ", MOD: " << modX << ", " << modY << ", " << modE << ", VELOCITY: " << Relativize(v, modX, modE, modT) << ", " << Relativize(v, modY, modE, modT) << ", " << vE << ", VF: " << v << ", Pos: " << x << ", " << y << "charge:" << c <<"\n\n";
    }

    /*
    void DeterminePriority(const Cell& cell) {
        int thisMass = P + N;
        int otherMass = cell.P + cell.N;

        // Return if the other atom has lower priority.
        // cellID breaks ties so exactly one atom yields.
        bool otherWins =
            otherMass > thisMass ||
            (otherMass == thisMass && cell.E > E) ||
            (otherMass == thisMass && cell.E == E &&
            cell.cellID < cellID);

        if (!otherWins) {
            return;
        }

        float moveX = abs(Relativize(v, modX, modE, modT));
        float moveY = abs(Relativize(v, modY, modE, modT));

        // Prefer undoing movement on the axis with the
        // smaller contribution, but fall back if necessary.
        if (moveX >= moveY) {
            if (Y != oldY) {
                Y = oldY;
                y = oldy;
            }
            else if (X != oldX) {
                X = oldX;
                x = oldx;
            }
        }
        else {
            if (X != oldX) {
                X = oldX;
                x = oldx;
            }
            else if (Y != oldY) {
                Y = oldY;
                y = oldy;
            }
        }
    }*/
};