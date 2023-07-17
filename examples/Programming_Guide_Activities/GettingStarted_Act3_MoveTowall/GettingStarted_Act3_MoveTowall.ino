#include <RN.h>

RN sensor(2, 3); // create an instance of RN class with trig pin 2 and echo pin 3
RN motor(5, 6, 9); // create a new instance of the RN class
RNCam cam(10,11);

void setup() {
  
}

void loop() {
  
  
  motor.setMotorDirection(1); // rotate the motor in one direction
  motor.setMotorSpeed(255); // set the motor speed to maximum
  float distance = sensor.getDistance();
  if(distance<50)
  {
  motor.stopMotor(); // stop the motor
  cam.getCamColorID();
  }
  
}
