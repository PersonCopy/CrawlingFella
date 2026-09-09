#pragma once

//#include "Common.h"

class Buzzer
{
    private:
        int pin;
    
    public:
        // Constructor of class.
        Buzzer(int);

        // Fallback constructor
        Buzzer();

        // Make a sound for n miliseconds.
        void buzz(int);

        // Specific sounds for when client
        // connects or disconnects to AP.
        void playConnected();
        void playDisconnected();
};