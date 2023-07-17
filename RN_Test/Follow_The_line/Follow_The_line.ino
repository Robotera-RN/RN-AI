#include "HUSKYLENS.h"
#include "RN.h"

RN motor(7, 8, 9);  // Initialize RN class for motor control
HUSKYLENS huskylens; 
int ID1 = 1;

void setup() {
  Serial.begin(9600);                                         
  Wire.begin();                                                 
  while (!huskylens.begin(Wire)) {
    Serial.println(F("Begin failed!"));
    Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protol Type>>I2C)"));
    Serial.println(F("2.Please recheck the connection."));
    delay(100);
  }
  huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);            
  motor.setMotorSpeed(0);                                        
  motor.setMotorDirection(0);
  motor.begin();
}

void loop() {
  if (!huskylens.request(ID1)) {
    Serial.println(F("Check connection to Huskeylens"));
    motor.setMotorSpeed(0); 
  } else if(!huskylens.isLearned()) {
    Serial.println(F("No object has been learned"));
    motor.setMotorSpeed(0); 
  } else if(!huskylens.available()) {
    Serial.println(F("No arrow on the screen yet"));
  } else {
    HUSKYLENSResult result = huskylens.read();                  
    printResult(result);
    
    if (result.xTarget < 160) {
      // turn left
      motor.setMotorSpeed(60);                                  
      motor.setMotorDirection(1);
    } else if (result.xTarget > 160) {
      // turn right
      motor.setMotorSpeed(60);                                  
      motor.setMotorDirection(2);
    } else {
      // move forward
      motor.setMotorSpeed(60);                                  
      motor.setMotorDirection(0);
    }
  }
}

void printResult(HUSKYLENSResult result) {                    
    if (result.command == COMMAND_RETURN_BLOCK) {
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    } else if (result.command == COMMAND_RETURN_ARROW) {
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    } else {
        Serial.println("Object unknown!");
    }
}