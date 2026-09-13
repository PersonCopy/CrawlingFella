#include "Common.h"

int AnalogStick::scaleOffset(int analogVal)
{
    int scaledOutput = 0;

    // If the read value is smaller than the center,
    // scale it to fit between the true middle and zero.
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

int AnalogStick::filterNoise(int raw, int* previous)
{
    float diff = raw - *previous;
    float alpha = fabs(diff) / 10.0;

    if (alpha < 0.05) alpha = 0.05;
    if (alpha > 1.0) alpha = 1.0;

    // Set new "previous" value.
    *previous = *previous + (int)(alpha * diff);
    return *previous;
}

void AnalogStick::readInputs()
{
    // Scale from 2**12 to 2**8 by /16.
    int x  = this->scaleOffset(analogRead(xPin)) / 16 - 128;
    int y  = this->scaleOffset(analogRead(yPin)) / 16 - 128;

    // Click-sensor will output exactly 0 when clicked in.
    this->click[this->clickIndex] = (int)analogRead(cPin) == 0 ? true : false;

    // Updates index of the clicks array.
    // The current click value can only be true if all the entries
    // (so past n entries)
    // are also TRUE to avoid sensor noise misinput.
    this->clickIndex++;
    if (this->clickIndex >= sizeof(this->click))
        this->clickIndex = 0;

    /*if (c && this->prevClick) this->click == c;
    this->prevClick = c;*/

    // Filter out sensor noise.
    this->xVal = this->filterNoise(x, &this->xPrev);
    this->yVal = this->filterNoise(y, &this->yPrev);
}

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

    // Initialize all entries as false.
    for (bool obj : this->click)
        obj = false;

    // Get data.
    this->readInputs();
}

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