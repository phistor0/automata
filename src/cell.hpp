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

    float volatilityfactor = 256.0f;


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

        if (iAtom.X - X != 0) {
            modX += 1.0f/(iAtom.X - X);
        }
        
        if (iAtom.Y - Y != 0){
            modY += 1.0f/(iAtom.Y - Y);
        }

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

    float Relativize(float vel, float modx, float mody, int setting) {
        vE = (2.0/3.14159f)*(std::atanf(/*(1.0f)/*/((sqrt(pow(modx, 2) + pow(mody, 2)))*(pow(vel, 3.0f)))/volatilityfactor));
        float angle = std::atanf((mody/modx));

        if (setting == 1) {
            if (modx == 0) {
                return 0;
            }
            
            if (mody == 0) {
                return vE*std::copysignf(1.0f, modx);
            }

            else {
                return std::abs(std::sinf(angle))*vE*std::copysignf(1.0f, modx);
            }  
        }
        
        if (setting == 2) {
            if (mody == 0) {
                return 0;
            }

            if (modx == 0) {
                return vE*std::copysignf(1.0f, mody);
            }

            else {
                return std::abs(std::cosf(angle))*vE*std::copysignf(1.0f, mody);
            }  
        }

        else {
            return 0;
        }
    }

    void Update(int gridWidthX, int gridWidthY) {
        modE = sqrt((pow(modX, 2) + pow(modY, 2)));
        modT = abs(modX) + abs(modY);

        x += Relativize(v, modX, modY, 1);
        y += Relativize(v, modX, modY, 2);
        
        // Clamp the relative positions
        x = max(0.0f, min(x, static_cast<float>(gridWidthX) - 0.001f));
        y = max(0.0f, min(y, static_cast<float>(gridWidthY) - 0.001f));

        X = floor(x); // rounds down tangible X position value from the relative value
        Y = floor(y); // rounds down tangible Y position value from the relative value

        c = P - E;

    }
};