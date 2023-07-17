#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include <RN.h>

RN_Motor motor(5, 6, 9); // create a new instance of the RN class

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11);
int ledPin = 13;
void printResult(HUSKYLENSResult result);

void setup() {
    Serial.begin(115200);
    mySerial.begin(9600);
   pinMode(ledPin, OUTPUT); 



    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the Protocol Type in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
}

void loop() 
{
    if (!huskylens.request()) 
Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));

    else if(!huskylens.isLearned()) 
Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));

    else if(!huskylens.available()) 
Serial.println(F("No block or arrow appears on the screen!"));

    else
    {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);
            driveBot(result);
        }    
    }
}


void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}

void driveBot(HUSKYLENSResult result)
{
  if(result.xCenter<=140)
  {
    left();
  }

  else if(result.xCenter>=200)
  {
    right();
  }

    else if((result.xCenter>=140)&&(result.xCenter<=200))
  {
    if(result.width<=20)
    {
      forward();
    }

    else if(result.width>20)
    {
      stop();
    }
  }
  
}


void stop()
{
motor.stopMotor(); // stop the motor
delay(10); // wait for one second
digitalWrite(ledPin, LOW);
Serial.println("Stop");
}
void right()
{
motor.setMotorDirection(1); // rotate the motor in one direction
motor.setMotorSpeed(128); // set the motor speed to maximum
delay(10); // wait for one second
digitalWrite(ledPin, HIGH);
Serial.println(" Rotate Right");
}
void left()
{
motor.setMotorDirection(-1); // rotate the motor in one direction
motor.setMotorSpeed(128); // set the motor speed to maximum
delay(10); // wait for one second
digitalWrite(ledPin, HIGH);
Serial.println(" Rotate Left");
}

void forward()
{
motor.setMotorDirection(1); // rotate the motor in one direction
motor.setMotorSpeed(128); // set the motor speed to maximum
delay(10); // wait for one second
digitalWrite(ledPin, HIGH);
Serial.println("Forward");
}

void backward()
{
motor.setMotorDirection(-1); // rotate the motor in the other direction
motor.setMotorSpeed(128); // set the motor speed to half
delay(10); // wait for one second
digitalWrite(ledPin, HIGH);
Serial.println("Backward");
}