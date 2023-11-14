#include <Wire.h>
#include <SPI.h>
#include "BluetoothSerial.h"



#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT;
String message = "";
char incomingChar;


float x = 0;
int ldrValue = 0;
void setup()
{
  Serial.begin(115200);
  while (!Serial);

  SerialBT.begin("IntelliVest");
  Serial.println("Pronto");
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  Wire.begin();
  initializeADXL();
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

  x = readX();
  ldrValue = analogRead(LDR_PIN);
  checkValue();
  ldr();
  fact();
  act();

  delay(500);
}

// Funções

void initializeADXL()
{
  writeRegister(0x2C, 0x08);
  writeRegister(0x31, 0x08);
  writeRegister(0x2D, 0x08);
}

void writeRegister(byte reg, byte value)
{
  Wire.beginTransmission(ADXL_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

float readX()
{
  if (check == 1)
  {
    /* code */

    byte lowByte, highByte;
    int16_t value;

    Wire.beginTransmission(ADXL_ADDR);
    Wire.write(0x32);
    Wire.endTransmission();
    Wire.requestFrom(ADXL_ADDR, 2);

    lowByte = Wire.read();
    highByte = Wire.read() & 0x03;

    value = (highByte << 8) + lowByte;
    if (value > 511)
      value -= 1024;
    return value * SCALE;
  }
}

void checkValue()

{
if(check == 1){
  
  if (x >= 0.70 && x <= 1.10)
  {
    digitalWrite(LED_PIN2, LOW);
    // Serial.println("CERTO");
  }
  else 
  {

    //  Serial.println("ERRADO");
    digitalWrite(LED_PIN2, HIGH);
    delay(500);
    digitalWrite(LED_PIN2, LOW);
  }
}
}

void ldr()
{
  if (check1 == 1)
  {

    if (ldrValue < 1000)
    {
      digitalWrite(LED_PIN1, HIGH);
    }
    else
    {
      digitalWrite(LED_PIN1, LOW);
    }

    if (check1 == 0)
    {
    digitalWrite(LED_PIN1, LOW);
    }
  

  }
}

void act()
{

  switch (value)
  {
  case 1:
    digitalWrite(LED_PIN, HIGH);
    break;
  case 2:
    digitalWrite(LED_PIN, LOW);
    break;
  
 case 3:
    check = 0;
    SerialBT.println("Giroscopio desativado");
    delay(650);
    break;

  case 4:
    check = 1;
    SerialBT.print(x);
    delay(650);
     break;

  case 5:
    check1 = 0;
    SerialBT.println("LDR Desativada");
    delay(650);
    break;

  case 6:
    check1 = 1;
    SerialBT.println(ldrValue);
    delay(650);
    break;

  case 7 :
    SerialBT.println("Menu Resetado!");
    check = 0;
    check1 = 0;
     digitalWrite(LED_PIN, LOW);
     digitalWrite(LED_PIN1, LOW);
     digitalWrite(LED_PIN2, LOW);
    delay(650);
    break;
  }
}

void fact()
{

  if (message == "1")
  {
    digitalWrite(LED_PIN, HIGH);
    value = 1;
    message = "";
  }

  if (message == "2")
  {

    digitalWrite(LED_PIN, LOW);
    value = 2;
    message = "";
  }

  if (message == "3")
  {
    digitalWrite(LED_PIN, LOW);
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
