#include "Buzzer.h"
#include <Arduino.h>

// Constructor that automatically sets pin mode.
Buzzer::Buzzer(int pin)
{
    pinMode(pin, OUTPUT);
    this->pin = pin;
}

// Fallback constructor.
Buzzer::Buzzer(){}

// Make buzz sound for (duration) ms.
void Buzzer::buzz(int duration)
{
    digitalWrite(this->pin, HIGH);
    delay(duration);
    digitalWrite(this->pin, LOW);
}

// Play sound when sth connects to hotspot.
void Buzzer::playConnected()
{
    buzz(50);
    delay(25);
    buzz(50);
    delay(5000);
}

// Play sound when sth disconnects from hotspot.
void Buzzer::playDisconnected()
{
    buzz(200);
}