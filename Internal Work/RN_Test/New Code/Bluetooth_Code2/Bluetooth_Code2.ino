// Bluetooth Tutorial By Robo India
// Bluetooth module used - HC-06

#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(2, 3); // (TXD, RXD) of HC-06
#define ledPin 5
int BT_input; // to store input character received via BT.

void setup()  
{
  pinMode(ledPin, OUTPUT);     // Arduino Board LED Pin
  BlueTooth.begin(9600);  
}

void loop() 
{
  if (BlueTooth.available())
 
  {
    BT_input=(BlueTooth.read());
    if (BT_input=='1')
    {
      digitalWrite(ledPin, HIGH);
      BlueTooth.println("Now LED is ON");
    }
    else if (BT_input=='0')
    {
      digitalWrite(ledPin, LOW);
      BlueTooth.println("Now LED is OFF");
    }
   else if (BT_input=='?')
    {
      BlueTooth.println("Send '1' to turn LED ON");
      BlueTooth.println("Send '0' to turn LED OFF");
    }   
   // You may add other if else condition here. 
  }
}