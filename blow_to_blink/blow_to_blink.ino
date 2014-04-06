int should_on = 0;
int previous_state = 0;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  
  if (digitalRead(7) == 0) {
    Serial.println("READ OK!");
      if (should_on == 0) {
        should_on = 1;
      }
      else {
         should_on = 0;
      }
  }
  
  ////// 
  if (should_on && previous_state == 0) {
    digitalWrite(13, HIGH);
    previous_state = 1;
  }
  else {
    digitalWrite(13, LOW);
    previous_state = 0;
  }
  
//  delay(100);
}
