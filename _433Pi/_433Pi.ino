  /*
  Simple example for receiving
  
  http://code.google.com/p/rc-switch/
  
  Need help? http://forum.ardumote.com
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
unsigned long received_data;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);
  Serial.println("BEGIN");
  // Receiver on inerrupt 0 => that is pin #2
  // Digital Pin 2
  mySwitch.enableReceive(0);
}

void loop() {
  if (mySwitch.available()) {
    
    int received_data = mySwitch.getReceivedValue();
    
    if (received_data == 0) {
      Serial.print("Unknown encoding");
    } else {
      Serial.print("Received ");
      Serial.print( received_data );
      
      if (received_data == 5000) {
        Serial.println("HIGH");
        digitalWrite(13, HIGH);
      }
      else if (received_data == 5001) {
        digitalWrite(13, LOW);
        Serial.println("LOW");
      }
      
      
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
    }

    mySwitch.resetAvailable();
  }
}
