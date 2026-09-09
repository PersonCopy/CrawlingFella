#include "Common.h"

// Approximate value of controller when no input is given.
// Note that it's not in the middle of 0-4096.
const int center = 1840;

// Scale offset of controller to center no-input.
int scaleOffset(int analogVal)
{
    int scaledOutput = 0;

    // If the read value is smaller than the center,
    // Scale it to fit between the true middle and zero.
    if (analogVal < center)
    {
        // Scale so that center * const = 2048
        float c = 2048 / (float)center;

        scaledOutput = (float)analogVal * c;
    }
    // If it is larger than the center, linearly fit it
    // on the upper half of the scale.
    else
    {
        scaledOutput = analogVal - center;

        float maxValue = 4096 - center;
        float c = 2048 / maxValue;

        scaledOutput = scaledOutput * c + 2048;
    }
    return scaledOutput;
}

// Filter out small jitter while letting large changes pass through.
int filterNoise(int raw, int previous)
{
    float diff = raw - previous;
    float alpha = fabs(diff) / 10.0;

    if (alpha < 0.05) alpha = 0.05;
    if (alpha > 1.0) alpha = 1.0;

    return previous + alpha * diff;
}

// Direct analog value reading.
void AnalogStick::readInputs()
{
    // Scale from 2**12 to 2**8 by /16.
    int x  = scaleOffset(analogRead(xPin)) / 16 - 128;
    int y  = scaleOffset(analogRead(yPin)) / 16 - 128;

    
    this->click[this->clickIndex] = (int)analogRead(cPin) == 0 ? true : false;

    this->clickIndex++;
    if (this->clickIndex >= sizeof(this->click))
        this->clickIndex = 0;

    /*if (c && this->prevClick) this->click == c;
    this->prevClick = c;*/

    this->xVal = filterNoise(x, this->xPrev);
    this->yVal = filterNoise(y, this->yPrev);

    // Update previous values.
    this->xPrev = this->xVal;
    this->yPrev = this->yVal;
}

// Constructor of class. Assumes pinMode already set.
AnalogStick::AnalogStick(int xPin, int yPin, int clickPin)
{
    // Set pinModes to INPUT.
    pinMode(xPin, INPUT);
    pinMode(yPin, INPUT);
    pinMode(clickPin, INPUT);

    // Set properties.
    this->xPin = xPin;
    this->yPin = yPin;
    this->cPin = clickPin;
    this->clickIndex = 0;

    for (bool obj : this->click)
        obj = false;

    this->readInputs();
}

// Fallback constructor.
AnalogStick::AnalogStick() {}

// Getter functions.
int AnalogStick::getX()
{
    return this->xVal;
}

int AnalogStick::getY()
{
    return this->yVal;
}

bool AnalogStick::getClick()
{
    for (bool obj : this->click)
    {
        if (!obj)
            return false;
        obj = false;
    }
    return true;
}