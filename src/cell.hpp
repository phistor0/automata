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
    int s;

    // the velocity factor is the number of turns it takes for an atom to move one cell in that component direction
    float vx; // velocity factor X component
    float vy; // velocity factor Y component

    float VX;
    float VY;

    float x; // relative x positon
    float y; // relative y position

    int cellID;

    bool isAlive;

    float modX;
    float modY;

    int oldX;
    int oldY;

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

        s = 0;
    } // transfer all paramters to real variables

    void AtomVelReset() {
        vx = 0;
        vy = 0;

        modX = 0;
        modY = 0;

        s = 0;

        c = P - E;
    }

    void AtomInteraction(Cell iAtom) {
        s = P + N + iAtom.P + iAtom.N;

        modX += iAtom.X - X; 
        modY += iAtom.Y - Y; 

        // X
        if (c < 0 && iAtom.c < 0 || c > 0 && iAtom.c > 0) {
            // repel
            if (X < iAtom.X) {
                vx -= s;
            }
            if (iAtom.X < X) {
                vx += s;
            }

            if (Y < iAtom.Y) {
                vy -= s;
            }
            if (iAtom.Y < Y) {
                vy += s;
            }
        }
        else if (c < 0 && iAtom.c > 0 || c > 0 && iAtom.c < 0) {
            if (X < iAtom.X) {
                vx += s;
            }
            if (iAtom.X < X) {
                vx -= s;
            }

            if (Y < iAtom.Y) {
                vy += s;
            }
            if (iAtom.Y < Y) {
                vy -= s;
            }
        }
    }

    float Relativize(float vel, float mod) {
        float VEL = static_cast<float>(vel);

        if (mod < 0) {
            return -1/(1 + pow(2, -((VEL/mod)-3)));
        }

        if (mod > 0) {
            return 1/(1 + pow(2, -((VEL/mod)-3)));
        }

        else {
            return 0;
        }
    }

    void Update(int gridWidthX, int gridWidthY) {
        if(vx != 0) {x += Relativize(vx, modX);}
        if(vy != 0) {y += Relativize(vy, modY);}
 
        X = floor(x); // rounds down tangible X position value from the relative value
        Y = floor(y); // rounds down tangible Y position value from the relative value

        if (X == gridWidthX - 1 || X == 0) {
            vx = -vx;
        }

        if (Y == gridWidthY - 1 || Y == 0) {
            vy = -vy;
        }

        c = P - E;

        cout << "updating: " << cellID << ", MOD: " << modX << ", " << modY <<  ", VELOCITY: " << Relativize(vx, modX) << ", " << Relativize(vy, modY) << ", VF: " << vx << ", " << vy << "\n\n";
    }

    void DeterminePriority(Cell cell) {
        if (cell.P + cell.N > P + N) {
            if (Relativize(vx, modX) > Relativize(vy, modY)) {
                Y = oldY;
            }

            if (Relativize(vx, modX) < Relativize(vy, modY)) {
                X = oldX;
            }
        }
        else if (cell.P + cell.N < P + N) {
            if (cell.E > E) {
                if (Relativize(vx, modX) > Relativize(vy, modY)) {
                    Y = oldY;
                }

                if (Relativize(vx, modX) < Relativize(vy, modY)) {
                    X = oldX;
                }
            }
        }
        else {
            if (Relativize(vx, modX) > Relativize(vy, modY)) {
                Y = oldY;
            }

            if (Relativize(vx, modX) < Relativize(vy, modY)) {
                X = oldX;
            }
        }
    }
};