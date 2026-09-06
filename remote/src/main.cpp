#include "Common.h"

// put function declarations here:
//void wrapServo(int);
int xPin  = 27;
int yPin  = 26;
int inPin = 25;

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

  // Initialize analog stick.
  stick = AnalogStick(xPin, yPin, inPin);
  Serial.println("Input defined.");
}

void loop() {
  Serial.println("Loop works.");
  Serial.printf("X value: ");
  Serial.print(stick.getX());
  Serial.printf(", Y value: ");
  Serial.println(stick.getY());
  Serial.println(stick.getClick());
  delay(DT);
}