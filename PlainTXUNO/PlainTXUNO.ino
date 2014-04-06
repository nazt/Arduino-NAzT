#include <VirtualWire.h>

#define MAX_WORDS 100
#ifndef NULL
  #define NULL 0
#endif

#define NUM_SENSOR 8
#define MAX_NODE 8
#define DEBUG 1
#define SHOW_TABLE 0


byte sensor_page(1);
byte select_pressed(0);
int sensor_nid;
int sensor_link_num;

char *words[MAX_WORDS], *aPtr, *bPtr;
int count = 0;

// user defined functions
int fromBinary(char *s) {
  return (int) strtol(s, NULL, 2);
}


// user defined types
typedef struct {
  byte type;
  byte node;
  char *str;
} sensor_t;

// initialization
sensor_t* sensor_data[NUM_SENSOR][MAX_NODE] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0} 
}; 

sensor_t* sensor_link[MAX_NODE];


/* Pro Micro Test Code
   by: Nathan Seidle
   modified by: Jim Lindblom
   SparkFun Electronics
   date: January 20, 2012
   license: Public Domain - please use this code however you'd like.
   It's provided as a learning tool.
   
   This code is provided to show how to control the SparkFun
   ProMicro's TX and RX LEDs within a sketch. It also serves
   to explain the difference between Serial.print() and
   Serial1.print().
*/
int RXLED = 17;  // The RX LED has a defined Arduino pin
// The TX LED was not so lucky, we'll need to use pre-defined
// macros (TXLED1, TXLED0) to control that.

void setup()
{
 pinMode(10, OUTPUT);  // Set RX LED as an output
 digitalWrite(10, HIGH);
 // TX LED is set as an output behind the scenes
 
  vw_set_rx_pin(4);    
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  vw_rx_start();       // Start the receiver PLL running   

 Serial.begin(9600); //This pipes to the serial monitor
}

void loop()
{
// Serial.println("Hello world");  // Print "Hello World" to the Serial Monitor
// Serial1.println("Hello!");  // Print "Hello!" over hardware UART
  count = 0;
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  if (vw_get_message(buf, &buflen)) // Non-blocking    
  {
      int l_type;
      int l_node;
      char* l_value;
      sensor_t *tmpSensor;
      sensor_t *sensor_temp;
      //SPLIT DATA WITH ,
      char *a = (char*) buf;
      while((aPtr = strsep(&a, ","))) {
          words[count++] = aPtr;
      }

      l_type = atoi(words[1]);
      l_node = fromBinary(words[0]);

      sensor_temp = sensor_data[l_type][l_node];
      if (sensor_temp != 0) {
        free(sensor_data[l_type][l_node]->str);
      }
      free(sensor_data[l_type][l_node]);

      if (DEBUG) {
        Serial.print("node: ");
        Serial.print(l_node);
        Serial.print(" type: ");
        Serial.print(l_type);
        Serial.print(" value: ");
        Serial.println(words[2]);
      }

      tmpSensor = (sensor_t*)malloc(sizeof(sensor_t));
      tmpSensor->node = l_node;
      tmpSensor->type = l_type;
      tmpSensor->str = strdup(words[2]);
      sensor_data[l_type][l_node] = tmpSensor;
       
      if (DEBUG) {
        Serial.println("==============================");
      }
      int sensor_link_idx = 0;
      sensor_link_num =0;
      for (int i = 0; i < NUM_SENSOR; ++i)
      {
        for (int j = 0; j < MAX_NODE; ++j)
        {
          if (sensor_data[i][j] == 0) {
            if (SHOW_TABLE) {
              Serial.print("null");
            }
          }
          else {
            if (SHOW_TABLE) {
              Serial.print((*sensor_data[i][j]).str);
            }
            sensor_link[sensor_link_idx++] = sensor_data[i][j];
            sensor_link_num++;
          }

          if (SHOW_TABLE) {
            if (l_type == 2) {
              Serial.print(",\t");
            }
            else {
              Serial.print(",\t");
            }
          }
        }
        if (SHOW_TABLE) {
          Serial.println();
        }
      }
      if (SHOW_TABLE) {
        Serial.println("===========================");
      }
      
      for (int i =0; i<sensor_link_num; i++) {
        Serial.print("NODE: ");
        Serial.print(sensor_link[i]->node);
        Serial.print(" TYPE: ");
        Serial.print(sensor_link[i]->type);
        Serial.print(" VALUE: [");
        Serial.print(sensor_link[i]->str);
        Serial.println("]");        
     
        
      }
      if (DEBUG) {
        Serial.println("===========================");
      }
  }
      
  
}
