#pragma once

#include "Common.h"

/** @brief Approximate value of controller when no input is given.
 * 
* Note that it's not in the middle of 0-4096.
*/
const int center = 1840;

/**
 * @brief Handles the joystick attached to the ESP32.
 * 
 * Specifically configured as it is a cheap component that
 * frequently returns inaccurate results. Data has to therefore
 * be parsed through this class.
 * 
 * Joystick can measure X and Y axis positions, as well as clicking
 * in the joystick.
 */
class AnalogStick
{
    private:
        /// @brief GPIO pin for x-axis input.
        int xPin;
        /// @brief GPIO pin for y-axis input.
        int yPin;
        /// @brief GPIO pin for joystick-click input.
        int cPin;

        /// @brief Processed and filtered value of x-input.
        int xVal;
        /// @brief Previous value of x-input.
        int xPrev;

        /// @brief Processed and filtered value of y-input.
        int yVal;
        /// @brief Previous value of x-input.
        int yPrev;

        /// @brief Array of last 50 clicks logged.
        bool click[50];
        /// @brief Index of most current click input.
        byte clickIndex;

        /**
         * @brief Fits the sensor value (12 bit) into [-128, 127].
         * 
         * Linear interpolation is done as the centered joystick value
         * is NOT the center value of 2^12.
         * @param analogVal Analog value of sensor straight from ADC.
         * @return Fitted and centered value in [-128, 127],
         * where 0 means "neutral input".
         */
        int scaleOffset(int);

        /**
         * @brief Applies 1D kalman filter to sensor
         * input to smooth out the sensor noise.
         * 
         * Note that slow input changes will here be mistaken for
         * noise and not registered.
         * @param raw Raw (unfiltered) value with noise.
         * @param previous previous value of sensor.
         * This one will be overwritten with the new value at the end.
         * @return Integer value of filtered data.
         */
        int filterNoise(int, int*);
    
    public:
        /**
         * @brief Constructor for analog stick that takes the GPIO
         * pins of the sensor to initialize the object.
         * @param xPin GPIO pin for x-axis (connect to ADC).
         * @param yPin GPIO pin for x-axis (connect to ADC).
         * @param clickPin GPIO pin for click-pin (connect to ADC).
         */
        AnalogStick(int, int, int);

        /// @brief Fallback constructor for uninitialized objects.
        AnalogStick();

        /**
         * @brief Reads inputs from defined GPIO pins and filters the values.
         * 
         * The values for the x- and y-axis are scaled to fit between -128 and +127
         */
        void readInputs();

        // Getter functions.

        /// @brief Get x-Axis sensor value.
        /// @return Filtered and fitted x-axis sensor value.
        int getX();

        /// @brief Get y-Axis sensor value.
        /// @return Filtered and fitted y-axis sensor value.
        int getY();
        /// @brief Get click sensor value.
        /// @return True if button clicked, else false.
        bool getClick();
};