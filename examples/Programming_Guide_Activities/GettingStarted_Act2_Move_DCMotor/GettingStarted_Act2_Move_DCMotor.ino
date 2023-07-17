#include <RN.h>

RN motor(7,8, 9); // create a new instance of the RN class

void setup() {
  // do nothing
}

void loop() {
  motor.setMotorDirection(1); // rotate the motor in one direction
  motor.setMotorSpeed(255); // set the motor speed to maximum
  delay(1000); // wait for one second
  motor.stopMotor(); // stop the motor
  delay(1000); // wait for one second
  motor.setMotorDirection(-1); // rotate the motor in the other direction
  motor.setMotorSpeed(128); // set the motor speed to half
  delay(1000); // wait for one second
  motor.stopMotor(); // stop the motor
  delay(1000); // wait for one second
}
