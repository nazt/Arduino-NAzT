#include <Shifter.h>

#define SER_Pin 11 //SER_IN
#define RCLK_Pin 8 //L_CLOCK
#define SRCLK_Pin 12 //CLOCK

#define NUM_REGISTERS 6 //how many registers are in the chain

int i = 0;

int state = 0;

//initaize shifter using the Shifter library
Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS); 

void setup(){
  Serial.begin(9600);
  Serial.println("BEGIN");
}

void loop(){
//  shifter.clear(); //set all pins on the shift register chain to LOW
//  shifter.write(); //send changes to the chain and display them

//  delay(1000);
  
  Serial.print("VAL: ");
  Serial.println(i%2);
  shifter.fakeSetPin(i, HIGH);
  shifter.setPin(i, HIGH); //set pin 1 in the chain(second pin) HIGH
  Serial.println("+++++++");
  Serial.println(shifter.getCurrentVal(i), BIN);

  
  shifter.write(); //send changes to the chain and display them
  //notice how you only call write after you make all the changes you want to make
  
  delay(400);
  
  
//  shifter.setAll(HIGH); //Set all   pins on the chain high
//  shifter.write(); //send changes to the chain and display them

  
  Serial.println("=================");
  i++;
  if (i>NUM_REGISTERS * 8) { 
    i =0; 
    shifter.clear(); //set all pins on the shift register chain to LOW
    shifter.write(); //send changes to the chain and display them
    Serial.println("==RESET==");

};
  
}
