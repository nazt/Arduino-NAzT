String tmp="";

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); 
};

void loop() {

  while (Serial1.available() > 0)  {
    tmp += char(Serial1.read());
    delay(2);
  }

  if(tmp.length() > 0) {
    Serial.println("");
    Serial.print(">>");
    Serial.println(tmp);
    tmp = "";
  }

  if (Serial.available()) {
    char c = Serial.read();
    //Serial.print(">> ");
    Serial.print(c);
    Serial1.write(c);
  }
}

