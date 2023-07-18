#include <RN.h>

// Define the pins connected to the TCS3200 color sensor
const int S0 = 3;
const int S1 = 4;
const int S2 = 5;
const int S3 = 6;
const int sensorOut = 7;
const int servoPin = 2;
// Create an instance of the RN library
RN colorSensor(S0, S1, S2, S3, sensorOut);
RN servoController(servoPin);

  bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}

void setup() {
  Serial.begin(9600);
  colorSensor.begin();
  servoController.Servobegin();
}

void loop() {
  unsigned int redValue = colorSensor.getIntensityR();
  unsigned int greenValue = colorSensor.getIntensityG();
  unsigned int blueValue = colorSensor.getIntensityB();
  
        

  servoController.setServoPosition(80);


  if ( inRange(redValue, 0, 487) && inRange(greenValue, 0, 615) && inRange(blueValue, 0, 521)){
   
   Serial.print("White Color");

    }
    else if ( inRange(redValue, 450, 860) && inRange(greenValue, 900, 1105) && inRange(blueValue,700, 867)){
   
   Serial.print("Red Color");
   servoController.setServoPosition(130);

    }

    else if ( inRange(redValue, 860, 1140) && inRange(greenValue, 615, 960) && inRange(blueValue, 690, 963)){
   
   Serial.print("Green Color");
   servoController.setServoPosition(30);

    }

    else if ( inRange(redValue,1140, 1215) && inRange(greenValue,1105, 1233) && inRange(blueValue, 521, 785)){
   
   Serial.print("Blue Color");

    }

    else if ( inRange(redValue, 1215, 1500) && inRange(greenValue, 1233, 1500) && inRange(blueValue, 963, 1500)){
   
   Serial.print("Black Color");

    }

    else {
   
   Serial.print("Other Color");

    }

  delay(1000);


}
