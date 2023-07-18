#include <RN.h>

RN ultraSensorF(14,15); // create an instance of RN class with trig pin 2 and echo pin 3
RN ultraSensorL(16,17); // create an instance of RN class with trig pin 2 and echo pin 3
RN ultraSensorR(18,19); // create an instance of RN class with trig pin 2 and echo pin 3
RN motor(7, 8, 9); // create a new instance of the RN class

// Define the pin connected to the servo motor
const int servoPin = 2;
int degStraight=75;
int degRange=50;


// Create an instance of the RN library
RN servoController(servoPin);


void setup() {
   Serial.begin(9600);
   servoController.Servobegin();
}

void loop() {
  
  
  motor.setMotorDirection(1); // rotate the motor in one direction
  motor.setMotorSpeed(255); // set the motor speed to maximum
  float distanceF = ultraSensorF.getDistance();
  float distanceR = ultraSensorR.getDistance();
  float distanceL = ultraSensorL.getDistance();
  
 Serial.print("Distance Front: ");
  Serial.print(distanceF);
  Serial.print(" cm");
   Serial.print("  Distance Right: ");
  Serial.print(distanceR);
  Serial.print(" cm");
   Serial.print("  Distance Left: ");
  Serial.print(distanceL);
  Serial.println(" cm");
  

 if (distanceF <= 80 && distanceF > 30){
    motor.setMotorDirection(1); // rotate the motor in one direction
  motor.setMotorSpeed(255); // set the motor speed to maximum

  // Set the servo speed to control the movement speed
  servoController.setServoSpeed(10);  // Adjust the value as desired

  // Move the servo to a specific position
  servoController.setServoPosition(degStraight-degRange);  // Adjust the value as desired

  delay(1); // wait for one second
  Serial.println("case Left");

}else if (distanceF > 80){
  motor.setMotorDirection(1); // rotate the motor in one direction
  motor.setMotorSpeed(255); // set the motor speed to maximum
 // Set the servo speed to control the movement speed
  servoController.setServoSpeed(10);  // Adjust the value as desired
  
 if (distanceL >50){
   distanceL =80;
 }

 if (distanceR > 50){
   distanceR =80;
 }

 float distanceTarget=(distanceL+distanceR)/2;
 float deg=degStraight-degRange+distanceR*degRange/distanceTarget;


  // Move the servo to a specific position
  servoController.setServoPosition(deg);  // Adjust the value as desired

  
  Serial.println(deg);
  Serial.println("case Forward");
  delay(1); // wait for one second

}else{
  motor.stopMotor(); // stop the motor
  delay(1000); // wait for one second`
  Serial.println("case  Stop");

}
}