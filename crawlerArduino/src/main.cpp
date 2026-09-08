#include "Common.h"

Servo servos[SERVO_COUNT];
//byte angle = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 booted successfully via VS Code!");
  servos[0].attach(10);
  servos[1].attach(11);
  servos[2].attach(12);

  // Network connectivity.
  connectWiFi();
  printWiFiStatus();

  // Prime servos.
  for (byte i = 0; i < SERVO_COUNT; i++)
    servos[i].write(0);
}

void loop() {
  /* Servo test loop.
  for (int i = 0; i < SERVO_COUNT; i++)
  {
    int angle = servos[i].read();
    servos[i].write(angle + 30 % 160);
    delay(500);
  }*/

  // Run webserver function that checks for clients.
  //webServer(servos);
  printWiFiStatus();
}