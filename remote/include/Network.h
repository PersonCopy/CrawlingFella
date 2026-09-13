#pragma once

/**
 * @brief Configures and starts access point/hotspot.
 */
void setupHotspot();

/**
 * @brief Connects to home WiFi.
 * 
 * Credentials hard coded into secrets.h,
 * which is in the gitignore and therefore not
 * visible in this repo.
 */
void connectToWiFi();