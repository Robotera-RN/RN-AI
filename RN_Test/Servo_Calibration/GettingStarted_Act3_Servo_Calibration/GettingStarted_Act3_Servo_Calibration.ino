#include <RN.h>

// Define the pin connected to the servo motor
const int servoPin = 2;

// Create an instance of the RN library
RN servoController(servoPin);

void setup() {
  servoController.Servobegin();
}

void loop() {

  
  // Move the servo to position
  servoController.setServoPosition(80);  // Adjust the value as desired

  delay(2000);  // Wait for 2 seconds
  
  // Move the servo to another position
  servoController.setServoPosition(130);  // Adjust the value as desired

  delay(2000);  // Wait for 2 seconds

    // Move the servo to another position
  servoController.setServoPosition(80);  // Adjust the value as desired

  delay(2000);  // Wait for 2 seconds
  
  // Move the servo to another position
  servoController.setServoPosition(30);  // Adjust the value as desired

  delay(2000);  // Wait for 2 seconds
}
