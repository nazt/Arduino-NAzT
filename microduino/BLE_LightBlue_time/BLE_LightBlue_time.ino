unsigned long timer=millis();

void setup() {
  Serial1.begin(9600); 
  Serial.begin(9600);   
}

void loop() {
  if(millis()-timer>1000)
  {
    Serial.println("OK");
    Serial1.print("BLE,Time: "); 
    Serial.print(millis()/1000); 
    delay(100);
  }
}
