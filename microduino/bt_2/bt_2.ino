/*
 * Use SoftwareSerial to talk to BlueSMiRF module
 * note pairing code is 1234
 */

#include <SoftwareSerial.h>

const int rxpin = 9;           // pin used to receive
const int txpin = 10;           // pin used to send to
SoftwareSerial bluetooth(rxpin, txpin); // new serial port on given pins

void setup()
{
  Serial.begin(9600);  
  bluetooth.begin(9600); // initialize the software serial port
  Serial.println("Serial ready");
  bluetooth.println("Bluetooth ready");  
}

void loop()
{
  if (bluetooth.available())
  {
    char c = (char)bluetooth.read();
    Serial.write(c);
  }
  if (Serial.available())
  {
    char c = (char)Serial.read();
    bluetooth.write(c);
  }
}
