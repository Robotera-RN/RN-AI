#include <RN.h>
#include <NewPing.h>

NewPing ultraSensorF(14, 15); // create an instance of RN class with trig pin 2 and echo pin 3
NewPing ultraSensorL(16, 17); // create an instance of RN class with trig pin 2 and echo pin 3
NewPing ultraSensorR(18, 19); // create an instance of RN class with trig pin 2 and echo pin 3
RN motor( 8, 9, 10); // create a new instance of the RN class

// Define the pin connected to the servo motor
const int servoPin = 2;
int degStraight = 80;
int degRange = 50;
int rCount = 0;
int wallDist = 80;
int stopDist = 40;
int rightDist=40;

// Create an instance of the RN library
RN servoController(servoPin);

void setup() {
  Serial.begin(9600);
  servoController.Servobegin();
  rCount = 0;
}

void loop() {
  float distanceF = ultraSensorF.ping_cm();
  float distanceR = ultraSensorR.ping_cm();
  float distanceL = ultraSensorL.ping_cm();

  Serial.print("Distance Front: ");
  Serial.print(distanceF);
  Serial.print(" cm");
  Serial.print("  Distance Right: ");
  Serial.print(distanceR);
  Serial.print(" cm");
  Serial.print("  Distance Left: ");
  Serial.println(distanceL);

  if (distanceF < stopDist || distanceL < 10 || distanceR < 10 ) {
    // Stop the motor immediately
    motor.stopMotor();
    Serial.println("Distance Front is less than stop distance, stopping motor.");
    delay(2000);
  }

  else if (distanceF < wallDist) {

    motor.setMotorDirection(1); // rotate the motor in one direction
    motor.setMotorSpeed(200); // set the motor speed to maximum

    // Set the servo speed to control the movement speed
    servoController.setServoSpeed(10);  // Adjust the value as desired

    // Move the servo to a specific position
    servoController.setServoPosition(50);  // Adjust the value as desired
    for (int i = 0; i <= 50; i++) {
        distanceF = ultraSensorF.ping_cm();
       if (distanceF < stopDist ) {
       break;
        }
        delay(1); // wait for one second
         }
    
    servoController.setServoPosition(degStraight);  // Adjust the value as desired

       for (int i = 0; i <= 200; i++) {
        distanceF = ultraSensorF.ping_cm();
        if (distanceF < stopDist ) {
       break;
        }
        delay(1); // wait for one second
         }

   Serial.println("case Left");

  } 
  else if(distanceL < 25){
    servoController.setServoPosition(100);
     motor.setMotorDirection(1); // rotate the motor in one direction
    motor.setMotorSpeed(255); // set the motor speed to maximum
    for (int i = 0; i <= 200; i++) {
        distanceF = ultraSensorF.ping_cm();
        if (distanceF < stopDist ) {
       break;
        }
        delay(1); // wait for one second
         }

  }
  else if (distanceF > wallDist) {
    motor.setMotorDirection(1); // rotate the motor in one direction
    motor.setMotorSpeed(255); // set the motor speed to maximum
    // Set the servo speed to control the movement speed
    servoController.setServoSpeed(10);  // Adjust the value as desired
    // Move the servo to a specific position


 float deg=degStraight-degRange+distanceR*degRange/rightDist;

 if (deg >= degStraight + degRange){
  deg = degStraight + degRange;

 }

  // Move the servo to a specific position
  servoController.setServoPosition(deg);  // Adjust the value as desired

  Serial.print("deg: ");
  Serial.println(deg);
  Serial.println("case Forward");

   // Serial.println(deg);
    delay(1); // wait for one second
  } 
    else {
    motor.stopMotor(); // stop the motor
    delay(2000); // wait for one second
    Serial.println("case  Stop");

  }
}