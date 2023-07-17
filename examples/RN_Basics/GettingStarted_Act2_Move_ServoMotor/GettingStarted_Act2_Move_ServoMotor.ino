#include <RN.h>

// Define the pin connected to the servo motor
const int servoPin = 2;

// Create an instance of the RN library
RN servoController(servoPin);

void setup() {
  servoController.Servobegin();
}

void loop() {
  // Set the servo speed to control the movement speed
  servoController.setServoSpeed(10);  // Adjust the value as desired

  // Move the servo to a specific position
  servoController.setServoPosition(90);  // Adjust the value as desired

  delay(2000);  // Wait for 2 seconds

  // Move the servo to another position
  servoController.setServoPosition(0);  // Adjust the value as desired

  delay(2000);  // Wait for 2 seconds
}
