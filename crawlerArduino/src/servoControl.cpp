#include "Common.h"

// Takes the instructions in JSON document and
// converts them into servo output.
void jsonToServoControl(JsonDocument &doc, Servo *servo)
{
    serializeJsonPretty(doc, Serial);

    // Set servos to 90deg to confirm logic works.
    for (byte i = 0; i < SERVO_COUNT; i++)
        servo[i].write(90);

    delay(2000);

    for (byte i = 0; i < SERVO_COUNT; i++)
        servo[i].write(0);
}