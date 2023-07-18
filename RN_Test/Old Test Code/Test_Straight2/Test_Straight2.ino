#include <RN.h>
#include "NewPing.h"
// Create instances of RN classes for ultrasonic sensors, motor, and servo
NewPing ultraSensorF(14, 15);
NewPing ultraSensorR(16, 17);
NewPing ultraSensorL(18,19);
RN motor(7, 8, 9);
const int servoPin =2;
RN servoController(servoPin);
float distanceF = 0;
float distanceR = 0;
float distanceL = 0;
// Set initial servo position to straight
int servoPosition = 75;

void setup() {
  // Initialize the servo
  servoController.setServoPosition(servoPosition);
     servoController.Servobegin();


  // Initialize the serial monitor
  Serial.begin(9600);
}

void loop() {
  // Read the distances from the ultrasonic sensors
  distanceF = ultraSensorF.ping_cm();
  distanceR = ultraSensorR.ping_cm();
  distanceL = ultraSensorL.ping_cm();

  /* Print the distances to the serial monitor*/
  Serial.println("Front Sensor");
  Serial.println(distanceF);
  Serial.println("Right Sensor ");
  Serial.println(distanceR);
  Serial.println("Left Sensor");
  Serial.println(distanceL);

  // Determine the servo position based on the distances
  if (distanceF > 40) {
    if (distanceL > distanceR && (distanceR < 15 || distanceL < 15)) {
      servoPosition = 25;
      servoController.setServoPosition(servoPosition);

      Serial.println("Left");
    } else if (distanceR > distanceL && (distanceR < 15 || distanceL < 15)) {
      servoPosition = 125;
      servoController.setServoPosition(servoPosition);
      Serial.println("Right");
    } else {
      servoPosition = 75;
      servoController.setServoPosition(servoPosition);
      Serial.println("Straight");
    }

    // Set the servo position and move forward at a slower speed
    motor.setMotorDirection(1);
    motor.setMotorSpeed(200);
    Serial.println("Forward");
  } else {
    if (distanceL < distanceR && (distanceR < 15 || distanceL < 15)) {
      servoPosition = 25;
      servoController.setServoPosition(servoPosition);
      Serial.println("Right");
    } else if (distanceR < distanceL && (distanceR < 15 || distanceL < 15)) {
      servoPosition = 125;
      servoController.setServoPosition(servoPosition);
      Serial.println("Left");
    } else {
      servoPosition = 75;
      servoController.setServoPosition(servoPosition);
      Serial.println("Straight");
    }

    // Set the servo position and move backward at a slower speed
    motor.setMotorDirection(-1);
    motor.setMotorSpeed(200);
    delay(2000);
    Serial.println("Reverse");
  }
}
