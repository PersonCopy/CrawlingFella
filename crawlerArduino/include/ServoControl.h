#pragma once
#include <ArduinoJson.h>
#include <Arduino.h>

#define MAX_ANGLE 180

void (jsonToServoControl(JsonDocument&, Servo*));
void commandServo(char, Servo*, byte);
int parseAngle(int);