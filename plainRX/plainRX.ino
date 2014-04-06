#include <LiquidCrystal.h>
#include <DFR_LCDKeypad.h>
#include <VirtualWire.h>
#include <stdio.h>
#include <string.h>
 
#define MAX_WORDS 100
#ifndef NULL
#define NULL 0
#endif

// Values are midpoints between analog value of key press.

#define NUM_SENSOR 8
#define MAX_NODE 8
#define DEBUG 0
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


// Character display is occuring once in setup, then only again in the button routines
// no need to refresh in update loop unless there is a change.  For now just redisplay all 
// text instead of additional logic to update only chagned value and display character.
// it is by far fast enough.
void charDisplay() {
    sensor_t *sensor_ptr; 
    // display characters mode
    // lcd.print("Vert: ");
    // lcd.print(sensor_nid);
    // lcd.print(printStr);
    sensor_ptr = sensor_data[sensor_page%NUM_SENSOR][sensor_nid%MAX_NODE];
}

void setup() {
  sensor_nid = 0;
  Serial.begin(9600);
  // Initialise the IO and ISR
  vw_set_rx_pin(13);    
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
  vw_rx_start();       // Start the receiver PLL running  
  
}

void loop() {
  // updates current key press value and calls button callbacks if necessary  
  count = 0;
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  vw_wait_rx();

  if (vw_get_message(buf, &buflen)) // Non-blocking    
  {
//      digitalWrite(13, true); // Flash a light to show received good message
      int l_type;
      int l_node;
      char* l_value;
      sensor_t *tmpSensor;
      sensor_t *sensor_temp;

//      Serial.println((char*) buf);

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
//      digitalWrite(13, false); // Flash a light to show received good message
  }

  unsigned long current = millis();
  // Serial.println(current);
  
}
