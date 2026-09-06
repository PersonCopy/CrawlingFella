#include "Common.h"

Servo servo1;
int angle = 0;

// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 booted successfully via VS Code!");

  int result = myFunction(2, 3);
  servo1.attach(10);

  connectWiFi();
}

void loop() {
  servo1.write(angle);
  angle += 10;
  angle %= 180;

  delay(1000);
  printWiFiStatus();
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}