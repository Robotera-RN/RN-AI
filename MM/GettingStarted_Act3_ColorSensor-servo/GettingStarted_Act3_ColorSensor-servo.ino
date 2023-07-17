#include <RN.h>

// Define the pin connected to the servo motor
const int servoPin = 10;

// Create an instance of the RN library
RN servoController(servoPin);

// Define the pins connected to the TCS3200 color sensor
const int S0 = 2;
const int S1 = 3;
const int S2 = 4;
const int S3 = 5;
const int sensorOut = 6;

// Create an instance of the RN library
RN colorSensor(S0, S1, S2, S3, sensorOut);

void setup() {
  Serial.begin(9600);
  colorSensor.begin();
  servoController.Servobegin();
}

void loop() {
  unsigned int redValue = colorSensor.getIntensityR();
  unsigned int greenValue = colorSensor.getIntensityG();
  unsigned int blueValue = colorSensor.getIntensityB();
  
  Serial.print("Red: ");
  Serial.print(redValue);
  Serial.print(" Green: ");
  Serial.print(greenValue);
  Serial.print(" Blue: ");
  Serial.println(blueValue);
  
if (redValue >0 && redValue <78  && greenValue >0 && greenValue <157 && blueValue >0 && blueValue <128){

// Set the servo speed to control the movement speed
  servoController.setServoSpeed(1);  // Adjust the value as desired

  // Move the servo to a specific position
  servoController.setServoPosition(120);  // Adjust the value as desired
 Serial.println(" White");
  
  
}




else if (redValue >78 && redValue <130  && greenValue >157 && greenValue <320 && blueValue >128 && blueValue <255){

// Set the servo speed to control the movement speed
  servoController.setServoSpeed(1);  // Adjust the value as desired

  // Move the servo to a specific position
  servoController.setServoPosition(45);  // Adjust the value as desired
 Serial.println(" Red");
  
  
}

else if (redValue >170 && redValue <450  && greenValue >120 && greenValue <410 && blueValue >140 && blueValue <410){

// Set the servo speed to control the movement speed
  servoController.setServoSpeed(1);  // Adjust the value as desired

  // Move the servo to a specific position
  servoController.setServoPosition(195);  // Adjust the value as desired
 Serial.println(" Green");
  
  
}

else {

  // Set the servo speed to control the movement speed
  servoController.setServoSpeed(1);  // Adjust the value as desired

  // Move the servo to a specific position
  servoController.setServoPosition(120);  // Adjust the value as desired
  Serial.println(" Black");
  
}

  delay(1000);
  }

