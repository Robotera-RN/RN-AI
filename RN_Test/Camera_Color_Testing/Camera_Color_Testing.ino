
#include <RN.h>
#include <HUSKYLENS.h>
#include <SoftwareSerial.h>
HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11);
int ledPin = 13;
int camColorID=0;
RN motor(7,8,9);
const int servoPin =2;
RN servoController(servoPin);
int servoPosition = 70;

void setup() {
  // Initialize the servo
  servoController.setServoPosition(servoPosition);
       servoController.Servobegin();

    Serial.begin(115200);
    mySerial.begin(9600);
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
Serial.println(getCamColorID());
camColorID=0;
if(getCamColorID()==2){
servoPosition=140;
servoController.setServoPosition(servoPosition);

}
else if(getCamColorID()==1){
servoPosition=0;
servoController.setServoPosition(servoPosition);

}
}


int getCamColorID() 
{
    if (!huskylens.request()) 
Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));

    else if(!huskylens.isLearned()) 
Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));

    else if(!huskylens.available()) 
Serial.println(F("No block or arrow appears on the screen!"));

    else
    {
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
    if (result.command == COMMAND_RETURN_BLOCK){
        camColorID=result.ID;
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        camColorID=result.ID;
    }
           
        }    
    }
    return(camColorID);
}



