#include "Common.h"
#include "../../crawlerArduino/include/secrets.h"


// put function declarations here:
//void wrapServo(int);

// Use ADC1 pins (GPIO 32 - 39), as ADC2
// is used by the WiFi access point.
int xPin  = 33;
int yPin  = 32;
int inPin = 35;
int buzzerPin = 15;

bool clientsConnected = false;

// Values of analog stick.
int16_t xVal;
int16_t yVal;
int16_t pressedIn;
//Servo myServo;
AnalogStick stick;
Buzzer buzzer;

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 booted successfully via VS Code!");
  
  // Initialize analog stick.
  stick = AnalogStick(xPin, yPin, inPin);
  Serial.println("Input defined.");

  buzzer = Buzzer(buzzerPin);
  // Start WiFi hotspot.
  setupHotspot();

  // Connect to WiFi.
  //connectToWiFi();
}

void loop() {
  // Toggle bool indicating change in state.
  byte clientCount = WiFi.softAPgetStationNum();
  if (clientCount != clientsConnected)
  {
    clientsConnected = clientCount;
    Serial.println("Clients?: " + (String)clientsConnected);

    // Play status change sound.
    if (clientsConnected)
      buzzer.playConnected();
    else buzzer.playDisconnected();
  }

  // Send commands only if someone is connected to AP.
  if (clientsConnected)
  {
    // Update stick inputs.
    stick.readInputs();

    // Send UDP commands to robot.
    sendStickCommand(stick);
    //delay(DT);
  }
}