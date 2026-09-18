#pragma once

/**
 * @brief Attempts to connect to the remotes AP.
 * If that doesn't work after 20 attempts, it will try
 * to connect to the fallback WiFi network (home WiFi). 
 */
void connectWiFi();

/**
 * @brief Prints information on WiFi connection, such as
 * the SSID and the IP adress, into the serial output.
 */
void printWiFiStatus();

/**
 * @brief Starts a UDP server & listens for sent to it's port.
 * The commands are expected in a JSON format.
 * @param servo Array of servos to control via UDP commands.
 */
void UDPServer(Servo *servo);