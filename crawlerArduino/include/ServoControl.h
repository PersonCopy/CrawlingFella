#pragma once
#include <ArduinoJson.h>
#include <Arduino.h>

/**
 * @brief Takes the instructions in JSON document and
 * converts them into servo movement.
 * @param doc JSON document containing properly parsed instructions.
 * Expects each row to look like {"AB" : C}, where
 * A is either 'A' or 'R' (check jsonToServoControl for more info)
 * B is the index of the servo that is to be moved.
 * C is the value that is passed to the command.
 * @param servos array of all controllable servos.
 */
void jsonToServoControl(JsonDocument&, Servo*);

/**
 * @brief Function to command a specific servo motor.
 * @param command Send character of command you want to execute.
 * 'A' for "absolute angle": Set servo to exactly this angle.
 * 'R' for "relative angle": Change servo by this angle (+ or -)
 * @param servo specific servo motor that is to be controlled.
 * @param value Angle value set or change servo by.
 * Note that "value" can be negative, representing a clockwise movement.
 */
void commandServo(char, Servo*, byte);

/**
 * @brief Wrapper function that linearizes the angles.
 * This function exists due to the nonlinearity of the used
 * REELY servos. They map the weird behaviour after 135deg
 * to linearly continue.
 * Also has wrap safety to prevent overshoot.
 * @param angle The actual angle that is to be achieved.
 * @return Angle that needs to be sent in order to get to the
 * desired angle (see parameter).
 */
int parseAngle(int);