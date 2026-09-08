#include "Common.h"
#include "../../crawlerArduino/include/secrets.h"


// put function declarations here:
//void wrapServo(int);

// Use ADC1 pins (GPIO 32 - 39), as ADC2
// is used by the WiFi access point.
int xPin  = 33;
int yPin  = 32;
int inPin = 35;

// Values of analog stick.
int16_t xVal;
int16_t yVal;
int16_t pressedIn;
//Servo myServo;
AnalogStick stick;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 booted successfully via VS Code!");
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(inPin, INPUT);

  // Start WiFi hotspot.
  setupHotspot();

  // Connect to WiFi.
  //connectToWiFi();
  
  // Initialize analog stick.
  stick = AnalogStick(xPin, yPin, inPin);
  Serial.println("Input defined.");
}

void loop() {
  // Output takes form (x, y, click)
  /*
  Serial.printf("(");
  Serial.print(stick.getX());
  Serial.printf(",");
  Serial.print(stick.getY());
  Serial.printf(",");
  Serial.print(stick.getClick());
  Serial.println(")");
  */
  sendStickCommand(stick);
  delay(DT);
}