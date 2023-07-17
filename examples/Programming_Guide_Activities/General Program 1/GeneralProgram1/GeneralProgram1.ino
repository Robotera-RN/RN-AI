
#include <RN.h>
const int servoPin = 2;//servo
RN servoController(servoPin);

HUSKYLENS huskylens;//camera
SoftwareSerial mySerial(10, 11);
int ledPin = 13;
int camColorID=0;



void setup() {

    servoController.Servobegin();//servo

    Serial.begin(115200);//camera
    mySerial.begin(9600);
    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the Protocol Type in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
}

void loop() //main Loop
{
  
  // Set the servo speed to control the movement speed
  servoController.setServoSpeed(10);  // Adjust the value as desired

  if (getCamColorID()==1){

  // Move the servo to a specific position
  servoController.setServoPosition(0);  // Adjust the value as desired
  Serial.println("Case 1");
  delay(2000);  // Wait for 2 seconds

  }

  if (getCamColorID()==2){

  // Move the servo to a specific position
  servoController.setServoPosition(180);  // Adjust the value as desired
  Serial.println("Case 2");
  delay(2000);  // Wait for 2 seconds

  }
  

  else {
  
    // Move the servo to another position
  servoController.setServoPosition(90);  // Adjust the value as desired
  Serial.println("Case 3");
  delay(2000);  // Wait for 2 seconds

  }

  

  




}


int getCamColorID() //camera
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



