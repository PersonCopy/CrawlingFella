#include "Buzzer.h"
#include <Arduino.h>

Buzzer::Buzzer(int pin)
{
    // PinMode is set in case it hasn't been already.
    pinMode(pin, OUTPUT);
    this->pin = pin;
}
Buzzer::Buzzer(){}

void Buzzer::buzz(int duration)
{
    // A single sound is played and stopped.
    digitalWrite(this->pin, HIGH);
    delay(duration);
    digitalWrite(this->pin, LOW);
}

void Buzzer::playConnected()
{
    // Sound is played twice to indicate "connected" status.
    buzz(50);
    delay(25);
    buzz(50);
    delay(5000);
}

void Buzzer::playDisconnected()
{
    // One longer sound is played for "disconnected".
    buzz(200);
}