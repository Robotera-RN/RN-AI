#include <RN.h>

// Define the pins for the ultrasonic sensors
const int trigPinF = 14;
const int echoPinF = 15;
const int trigPinL = 16;
const int echoPinL = 17;
const int trigPinR = 18;
const int echoPinR = 19;

// Define the pins for the servo motor
const int servoPin = 2;

// Define the pins for the motor controller
const int motorPin1 = 7;
const int motorPin2 = 8;
const int motorSpeedPin = 9;

// Create instances of the RN class for each sensor, servo, and motor
RN ultraSensorF(trigPinF, echoPinF);
RN ultraSensorL(trigPinL, echoPinL);
RN ultraSensorR(trigPinR, echoPinR);
RN servoController(servoPin);
RN motorController(motorPin1, motorPin2, motorSpeedPin);

// Define the threshold distances for obstacle avoidance
const float thresholdF = 20; // Threshold distance for front sensor
const float thresholdL = 10; // Threshold distance for left sensor
const float thresholdR = 10; // Threshold distance for right sensor

// Define the servo angle limits
const int servoMinAngle = 0;
const int servoMaxAngle = 180;

// Define the motor speed limits
const int motorMinSpeed = 0;
const int motorMaxSpeed = 255;

// Define the initial servo angle and motor speed
int servoAngle = 90;
int motorSpeed = 0;

void setup() {
  // Initialize the ultrasonic sensors
  ultraSensorF.begin();
  ultraSensorL.begin();
  ultraSensorR.begin();

  // Initialize the servo motor
  servoController.Servobegin();

  // Initialize the motor controller
  motorController.begin();
}

void loop() {
  // Read the distance from the ultrasonic sensors
  float distanceF = ultraSensorF.getDistance();
  float distanceL = ultraSensorL.getDistance();
  float distanceR = ultraSensorR.getDistance();

  // Print the distance readings to the serial monitor
  Serial.print("Distance Front: ");
  Serial.print(distanceF);
  Serial.print(" cm");
  Serial.print("  Distance Left: ");
  Serial.print(distanceL);
  Serial.print(" cm");
  Serial.print("  Distance Right: ");
  Serial.print(distanceR);
  Serial.println(" cm");

  // Check if there are any obstacles in the way
  if (distanceF <= thresholdF || distanceL <= thresholdL || distanceR <= thresholdR) {
    // Stop the car
    motorController.setMotorSpeed(0);
    delay(100);

    // Turn the servo to face the open space
    if (distanceL >= distanceR) {
      servoAngle = servoMinAngle;
    } else {
      servoAngle = servoMaxAngle;
    }
    servoController.setServoPosition(servoAngle);
    delay(100);

    // Move the car forward
    motorSpeed = motorMaxSpeed;
    motorController.setMotorSpeed(motorSpeed);
  } else {
    // Move the car forward
    motorSpeed = motorMaxSpeed;
    motorController.setMotorSpeed(motorSpeed);

    // Adjust the servo angle based on the distance readings
    if (distanceL >= distanceR) {
      servoAngle -= (distanceL - distanceR) * 2;
    } else {
      servoAngle += (distanceR - distanceL) * 2;
    }
    servoAngle = constrain(servoAngle, servoMinAngle, servoMaxAngle);
    servoController.setServoPosition(servoAngle);
  }
}