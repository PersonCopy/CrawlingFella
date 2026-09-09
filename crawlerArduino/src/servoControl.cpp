#include "Common.h"

// Takes the instructions in JSON document and
// converts them into servo output.
void jsonToServoControl(JsonDocument &doc, Servo *servo)
{
    // Cast into JSON object.
    JsonObjectConst jsonObj = doc.as<JsonObjectConst>();

    for (JsonPairConst row : jsonObj)
    {
        // Separate into key value pair.
        String key = row.key().c_str();
        byte value = row.value().as<int>();

        // Separate key into command and servo index.
        char command = key.charAt(0);
        byte servoIndex = key.substring(1).toInt();

        // Execite command.
        commandServo(command, &servo[servoIndex], value);
    }
}

// Due to the nonlinearity of the servos,
// A wrapper function needed to be made which
// interpolates the weird behaviour of the potentiometer
// after 135 degrees.
int parseAngle(int angle)
{
    // Wrap safety to prevent overshoot.
    angle %= 360;
    if (angle > MAX_ANGLE)
        angle = MAX_ANGLE;

    // Since the REELY servos I'm using are nonlinear
    // after 135-180 deg (wrapping to 180 at input 165),
    // The output has to be scaled after that point.
    if (angle > 135)
         angle = map(angle, 135, 180, 135, 165);
    return angle;
}

// Function to command servo motor.
// command  :   A for absolute angle
//              R for relative angle
// *servo   :   Servo that is to be commanded.
// value    :   Angle value in case of absolute angle "A"
//              or in case of "R", change in angle.
void commandServo(char command, Servo *servo, byte value)
{
    byte angle = 0;
    // Set absolute angle.
    if (command == 'A'){
    Serial.println(value);
        angle = parseAngle(value);}
    
    // Change relative angle.
    else if (command == 'R')
        angle = parseAngle(servo->read() + value);
    
    servo->write(angle);
}