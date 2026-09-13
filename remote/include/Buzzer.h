#pragma once

//#include "Common.h"

/**
 * @brief Active buzzer element for the microcontroller.
 * 
 * Will play fixed sounds on a buzzer element when adequate
 * method is called. Intent here is to have a buzzer play a
 * "connected" and "disconnected" sound.
 */
class Buzzer
{
    private:
        /// @brief GPIO pin of buzzer.
        int pin;
    
    public:
        /// @brief Initializes buzzer component given a GPIO pin.
        /// @param  pin GPIO pin at which the buzzer is attached to. Use ADC pin.
        Buzzer(int);

        /// @brief Fallback constructor for uninitialized objects.
        Buzzer();

        /// @brief Make a sound for n miliseconds.
        /// @param duration Buzz duration in ms.
        void buzz(int);

        // Specific sounds for when client
        // connects or disconnects to AP.

        /**
         * @brief Plays a unique two chime sound.
         * 
         * Intended for when a client connects to the AP.
         */
        void playConnected();

        /**
         * @brief plays a slightly long buzz sound.
         * 
         * Intended for when a client disconnects from the AP.
         */
        void playDisconnected();
};