#include "Common.h"

Servo servos[SERVO_COUNT];
//byte angle = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 booted successfully via VS Code!");
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
  // Run webserver function that checks for clients.
  //webServer(servos);

  // Run UDP server to recieve data.
  UDPServer(servos);
  //int mapped = map(servos[i].read(), 0, 180, 0, SERVO_MAX_ANGLE);
  /*
  servos[2].write(45);
  delay(2000);
  servos[2].write(90);
  delay(2000);
  servos[2].write(135);
  delay(2000);
  servos[2].write(90);
  delay(2000);*/
}