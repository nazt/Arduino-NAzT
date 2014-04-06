#include <VirtualWire.h> // ver. 1.5

//global variable
#define MSG_SIZE 14
// end global variable

char buffer[MSG_SIZE];
float maxv, CO, CO_raw;
int circ = 4, heat = 5, send_round = 0;

void setup()
{
  Serial.begin(115200); //Serial communication for Arduino Serial Monitor
//  Serial.begin(115200);
//  mySerial.begin(115200); //Serial communcation for Aircasting Application
  pinMode(circ, OUTPUT);
  pinMode(heat, OUTPUT);
  vw_set_tx_pin(13);
  vw_set_ptt_inverted(true); // Required for PTT
  vw_setup(2000); // Bits per sec
}

void loop()
{
  GetCO();
  //Display of CO gas sensor
//  mySerial.print(CO);
//  mySerial.print(";InsertSensorPackageName;TGS2442;CO Gas;CO;response indicator;RI;0;25;50;75;100");
//  mySerial.print("\n");
  Serial.print(CO_raw);  
  Serial.print(" : ");
  Serial.print("CO Gas: ");
  Serial.print(CO);
  Serial.print("% ");
  Serial.println("");
  if (send_round % 5 == 0) {
    send_round = 0;
    digitalWrite(13, true); // Flash a light to show transmitting
    buffer[0] = '0'; //digitalRead(8)+48;
    buffer[1] = '0';
    buffer[2] = '0';   
    // &buffer[3]
    memcpy(buffer+3, ",5,", 3);
    dtostrf(CO_raw, 3, 2, &buffer[6]);    
    buffer[13] = '\0';
    vw_send((uint8_t *)buffer, MSG_SIZE); // transmit msg
//    vw_wait_tx(); // Wait for message to finish
    digitalWrite(13, false);
    Serial.println("send data");
  }
  send_round++;
//  delay(450);
}

void GetCO()
{
  digitalWrite(circ, LOW);
  analogWrite(heat, 245);
  delay(14);
  analogWrite(heat, 0);
  delay(981);
  digitalWrite(circ, HIGH);
  delay(3);
  CO_raw = analogRead(A1);
  CO = map(CO_raw, 0 , 1023, 0, 100);
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
