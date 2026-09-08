#pragma once
#include <ArduinoJson.h>

#define MAX_ANGLE 177

void (jsonToServoControl(JsonDocument&, Servo*));
void commandServo(char, Servo*, byte);