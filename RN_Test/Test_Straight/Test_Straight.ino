#include <RN.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
// Create instances of RN classes for ultrasonic sensors, motor, and servo
NewPing ultraSensorF(14, 15);
NewPing ultraSensorR(16, 17);
NewPing ultraSensorL(18,19);
RN motor(8, 9, 10);
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

Serial.println("Forward: ");
Serial.println(distanceF);

Serial.println("Left: ");
Serial.println(distanceL);

Serial.println("Right: ");
Serial.println(distanceR);
  /* Print the distances to the serial monitor
  Serial.println("Front Sensor");
  Serial.println(distanceF);
  Serial.println("Right Sensor ");
  Serial.println(distanceR);
  Serial.println("Left Sensor");
  Serial.println(distanceL);
*/
  // Determine the servo position based on the distances
  if (distanceF > 100) {
      servoPosition = 75;
      servoController.setServoPosition(servoPosition);
    // Set the servo position and move forward at a slower speed
    motor.setMotorDirection(1);
    motor.setMotorSpeed(200);
    Serial.println("Forward");
  }
 else if(distanceF < 100 && distanceF > 50){
    servoController.setServoPosition(25);
      Serial.println("Turn Leff");
 }
   else if(distanceL < 30 && distanceR < 39){
     motor.stopMotor();
  } 
  else{
     motor.stopMotor();
     

  }
delayMicroseconds(1);
    
  }
