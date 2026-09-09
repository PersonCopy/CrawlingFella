#pragma once

//#include "Common.h"

class AnalogStick
{
    private:
        int xPin;
        int yPin;
        int cPin;

        int xVal;
        int xPrev;

        int yVal;
        int yPrev;

        bool click[50];
        byte clickIndex;
    
    public:
        // Constructor of class. Assumes pinMode already set.
        AnalogStick(int, int, int);

        // Fallback.
        AnalogStick();

        // Direct analog value reading.
        void readInputs();

        // Getter functions.
        int getX();
        int getY();
        bool getClick();
};