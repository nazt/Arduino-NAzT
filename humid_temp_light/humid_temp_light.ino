// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"

// BH1750
#include <Wire.h>
#include <BH1750.h>


// RCSWITCH
#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();


#define DHTPIN 10     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

void setup() {
  Serial.begin(9600); 
  
  // Data
  pinMode(13, OUTPUT);  // Either way, we'll use pin 7 to drive the data pin of the transmitter.  
  
  //lightMeter.begin();  
  dht.begin();
  mySwitch.enableTransmit(13);

}

void loop() {
  // lightMeter
  // uint16_t lux = lightMeter.readLightLevel();

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("NODE: 2 TYPE: 1 VALUE: [");    
    Serial.print(h);
    Serial.print(":");  
    Serial.print(t);
    Serial.println("]");

  }
  char nat[10] = {'h','e','l','l','o',' ','#'};
  // NODE: 2 TYPE: 2 VALUE: [25.00:44.20]
  //Serial.print("NODE: 2 TYPE: 3 VALUE: [");
  //Serial.print(lux);
  //Serial.println("]");
   mySwitch.send((long unsigned int)nat, 24);
//   mySwitch.send((long unsigned int)1234, 24);   
}
