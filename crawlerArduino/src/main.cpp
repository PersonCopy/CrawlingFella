#include "Common.h"

Servo servos[SERVO_COUNT];

void setup() {
  Serial.begin(115200);
  Serial.println("Successfully booted!");

  // Attach servo motors & add to array.
  servos[0].attach(10, 440, 2800);
  servos[1].attach(11, 440, 2800);
  servos[2].attach(12);

  // Network connectivity.
  connectWiFi();
  printWiFiStatus();

  // Prime servos.
  for (byte i = 0; i < 2; i++)
    servos[i].write(0);
}

void loop() {
  // Run UDP server to recieve data.
  UDPServer(servos);
}