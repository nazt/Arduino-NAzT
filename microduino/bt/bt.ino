#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(3, 2); //RX,TX
 
String tmp; 
 
void setup() {
  Serial.begin(9600);
  mySerial.setTimeout(100);
  mySerial.begin(9600); 
  Serial.println("Arduino -Test");
};
 
void loop() {
//  Serial.println("LOOP");
 
  while (mySerial.available() > 0)  {
    tmp += char(mySerial.read());
    Serial.println(tmp);
    delay(2);
  }
 
  if(tmp.length() > 0) {
    Serial.println(tmp);
    tmp = "";
  }
 
  if (Serial.available()) {
    Serial.println("GO IN TO WRITE THE SERIAL");
    mySerial.write(Serial.read());
  }
  else {
//    mySerial.write("AT");
  }
}
