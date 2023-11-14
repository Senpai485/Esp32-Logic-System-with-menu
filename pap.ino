#include <Wire.h>
#include <SPI.h>
#include "BluetoothSerial.h"



#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
String message = "";
char incomingChar;


int value = 0;
void setup()
{
  Serial.begin(115200);
  while (!Serial);

  SerialBT.begin("Senpai"); // Nome Para o bluetooth
  Serial.println("Pronto");
  

  
}

void loop()
{

  if (Serial.available())
  {
    SerialBT.write(Serial.read());
  }

  if (SerialBT.available())
  {
    char incomingChar = SerialBT.read();
    if (incomingChar != '\n')
    {
      message += String(incomingChar);
    }
    else
    {
      message = "";
    }
    Serial.write(incomingChar);
  }

  fact();
  act();

  delay(500);
}

// Funções



void act()
{

  switch (value)
  {
  case 1:
  
    break;
  case 2:
    
    break;
  
 case 3:
    
    break;

  case 4:
    
    
     break;

  case 5:
   
    
    break;

  case 6:
    
    
    delay(650);
    break;

  case 7 :
   
    
    break;
  }
}

void fact()
{

  if (message == "1")
  {
    
    value = 1;
    message = "";
  }

  if (message == "2")
  {

    
    value = 2;
    message = "";
  }

  if (message == "3")
  {

    value = 3;
    message = "";
  }
  if (message == "4")
  {
    value = 4;
    message = "";
  }

  if (message == "5")
  {
    value = 5;
    message = "";
  }

  if (message == "6")
  {
    value = 6;
    message = "";
  }
  if (message == "7")
  {
    value = 7;
    message = "";
  }
 Serial.println(value);
}
