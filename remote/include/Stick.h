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

        bool click;
        bool prevClick;

        // Direct analog value reading.
        void readInputs();
    
    public:
        // Constructor of class. Assumes pinMode already set.
        AnalogStick(int, int, int);

        // Fallback.
        AnalogStick();

        // Getter functions.
        int getX();
        int getY();
        int getClick();
};