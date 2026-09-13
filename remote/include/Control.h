#pragma once
#include "Stick.h"

/**
 * @brief Sends command from joystick to robot via UDP.
 * 
 * @param stick The joystick element who's position is to
 * be parsed into a command.
 */
void sendStickCommand(AnalogStick);