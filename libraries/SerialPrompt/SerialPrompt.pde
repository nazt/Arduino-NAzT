#include <EEPROM.h>

#include "ConsoleMenu.h"
#include "ConsoleListMenu.h"
#include "ConsoleListMenuIntInput.h"
#include "config.h"

// Time user has to press a key to enter configuration (in ms)
#define BOOT_TIMEOUT 3000

typedef struct {
  int pin;
  int timeOn;
  int timeOff;
} 
ledConfig;

struct {
  unsigned int version;

  bool active;
  int test1;
  int test2;

  struct {
    int test;
    int testToo;
  } 
  sub1;

  int ledConfigCount;
  ledConfig* ledConfigs;
} 
config;

void loadConfig(int argc, char** argv) {
  int n = 0;

  load_uint(&config.version, &n);
  if(config.version != CONFIG_STRUCT_VERSION)
  	return;
  load_bool(&config.active, &n);
  load_int(&config.test1, &n);
  load_int(&config.test2, &n);
  load_int(&config.sub1.test, &n);
  load_int(&config.sub1.testToo, &n);
  load_int(&config.ledConfigCount, &n);
  
  free(config.ledConfigs);
  config.ledConfigs = (ledConfig*)malloc(sizeof(ledConfig) * config.ledConfigCount);
  
  for(int j=0; j<config.ledConfigCount; j++) {
    load_int(&config.ledConfigs[j].pin, &n);
    load_int(&config.ledConfigs[j].timeOn, &n);
    load_int(&config.ledConfigs[j].timeOff, &n);
  }

  Serial.print("Loaded ");
  Serial.print(n);
  Serial.println(" bytes");
}

void saveConfig(int argc, char** argv) {
  int n = 0;

  save_uint(&config.version, &n);
  save_bool(&config.active, &n);
  save_int(&config.test1, &n);
  save_int(&config.test2, &n);
  save_int(&config.sub1.test, &n);
  save_int(&config.sub1.testToo, &n);
  save_int(&config.ledConfigCount, &n);
  for(int j=0; j<config.ledConfigCount; j++) {
    save_int(&config.ledConfigs[j].pin, &n);
    save_int(&config.ledConfigs[j].timeOn, &n);
    save_int(&config.ledConfigs[j].timeOff, &n);
  }

  Serial.print("Saved ");
  Serial.print(n);
  Serial.println(" bytes");
}

void printLedConfig(int i, void* target) {
		ledConfig* config = (ledConfig*)target;
    Serial.print("config.ledConfigs["); 
    Serial.print(i); 
    Serial.print("].pin: ");
    Serial.println(config->pin);
    Serial.print("config.ledConfigs["); 
    Serial.print(i); 
    Serial.print("].timeOn: ");
    Serial.println(config->timeOn);
    Serial.print("config.ledConfigs["); 
    Serial.print(i); 
    Serial.print("].timeOff: ");
    Serial.println(config->timeOff);
}

void printConfig(int argc, char** argv) {
  Serial.print("config.version: ");
  Serial.println(config.version);

  Serial.print("config.active: ");
  Serial.println(b2c(config.active));

  Serial.print("config.test1: ");
  Serial.println(config.test1);

  Serial.print("config.test2: ");
  Serial.println(config.test2);

  Serial.print("config.sub1.test: ");
  Serial.println(config.sub1.test);

  Serial.print("config.sub1.testToo: ");
  Serial.println(config.sub1.testToo);

  for(int i=0; i<config.ledConfigCount; i++) {
  	printLedConfig(i, &config.ledConfigs[i]);
  }
}

void printRawMem(int argc, char** argv) {
  if(argc <= 0) {
    Serial.println("mem <bytes> [format] [per line]");
    Serial.println("bytes     Number of bytes to print");
    Serial.println("format    d for dec, x for hex");
    Serial.println("per line  Bytes per line");
    return;
  }
  
  int bytes = 10;
  int format = DEC;
  int breakAt = -1;
  if(argc > 0) {
    bytes = atoi(argv[0]);
  }  
  if(argc > 1) {
    if(argv[1][0] == 'x') format = HEX;
    else if(argv[1][0] == 'b') format = BIN;
    else if(argv[1][0] == 'a') format = BYTE;
    else if(argv[1][0] == 'o') format = OCT;
  }
  if(argc > 2) {
    breakAt = atoi(argv[2]);
  }

  int c;
  for(int i=0; i<bytes; i++) {
    if(i != 0)
    	if(i%breakAt == 0)
      	Serial.println();
    	else
	      Serial.print(" ");
    c = (int)EEPROM.read(i);
    if(format == DEC) { Serial.print((c < 10) ? "  " : (c < 100) ? " " : ""); }
    else if(format == HEX && c < 0x10) Serial.print('0');
    Serial.print(c, format);
  }
  Serial.println();
}

void configure() {
	ConsoleMenuBoolInput actactive("act", "Active", &config.active);
  ConsoleMenuExecuter actload("load", "Load current config", &loadConfig);
  ConsoleMenuExecuter actmem("mem", "Print memory bytes", &printRawMem);
  ConsoleMenuExecuter actprint("print", "Print current config", &printConfig);
  ConsoleMenuExecuter actsave("save", "Save current config", &saveConfig);
  ConsoleMenu menu_sub1("sub1", "sub 1", "Sub menu 1");
  ConsoleMenuIntInput acttest("test", "Test input in sub", &config.sub1.test, INT_MIN, INT_MAX);
  ConsoleMenuIntInput acttestToo("testToo", "Test input in sub", &config.sub1.testToo, INT_MIN, INT_MAX);
  ConsoleMenuItem *menu_sub1_acts[] = { 
    &acttest, &acttestToo };
  menu_sub1.menuItems = menu_sub1_acts;
  menu_sub1.menuItemCount = arlen(menu_sub1_acts);
  ConsoleMenuIntInput acttest1("test1", "Test input 1", &config.test1, -10, 10);
  ConsoleMenuIntInput acttest2("test2", "Test input 2", &config.test2, INT_MIN, INT_MAX);
  ConsoleListMenu actLedConfig("leds", "leds", "Led config");
  actLedConfig.targetList = (void**)&config.ledConfigs;
  actLedConfig.targetSize = sizeof(ledConfig);
  actLedConfig.targetCount = &config.ledConfigCount;
  actLedConfig.printItem = &printLedConfig;
  
  ConsoleListMenuIntInput actLedConfigPin("pin", "The pin used for this LED", offsetof(ledConfig, pin), 0, 19, 0);
  ConsoleListMenuIntInput actLedConfigTimeOn("on", "The time this LED should be on", offsetof(ledConfig, timeOn), 0, INT_MAX, 1000);
  ConsoleListMenuIntInput actLedConfigTimeOff("off", "The time this LED should be off", offsetof(ledConfig, timeOff), 0, INT_MAX, 1000);
  ConsoleMenuItem *menu_ledconfig_acts[] = { &actLedConfigPin, &actLedConfigTimeOn, &actLedConfigTimeOff };
  actLedConfig.itemSettings = menu_ledconfig_acts;
  actLedConfig.itemSettingCount = arlen(menu_ledconfig_acts);
  
  ConsoleMenuItem *menu_config_acts[] = { 
    &actactive, &actload, &actmem, &actprint, &actsave, &menu_sub1, &acttest1, &acttest2, &actLedConfig };
  ConsoleMenu menu_main("", "main", "The main menu");
  menu_main.menuItems = menu_config_acts;
  menu_main.menuItemCount = arlen(menu_config_acts);

  menu_main.execute(0, NULL);
}

void loadDefaultConfig() {
  config.version = CONFIG_STRUCT_VERSION;
  config.active = 1;
  config.test1 = 0;
  config.test2 = 0;
  config.ledConfigCount = 2;
  config.ledConfigs = (ledConfig*)malloc(sizeof(ledConfig) * config.ledConfigCount);
  config.ledConfigs[0].pin = 6;
  config.ledConfigs[0].timeOn = 1337;
  config.ledConfigs[0].timeOff = 4242;
  config.ledConfigs[1].pin = 9;
  config.ledConfigs[1].timeOn = 7331;
  config.ledConfigs[1].timeOff = 2424;
}

void setup() {
	loadConfig(0, NULL);
  if(config.version != CONFIG_STRUCT_VERSION) {
  	loadDefaultConfig();
  }
  
  Serial.begin(9600);
  Serial.print("Welcome. Press any key to configure. ");

  unsigned long lastCountDownAt = 0;
  unsigned long decideBefore = millis() + BOOT_TIMEOUT;
  int avail;
  do {
    avail = Serial.available();
		if(millis() > lastCountDownAt + 1000) {
			lastCountDownAt = millis();
			Serial.print((decideBefore - millis() + 999) / 1000);
			Serial.print(" ");
		}
  } 
  while(avail == 0 && millis() < decideBefore);
  Serial.println();

  if(avail > 0) {
    while(Serial.available()) Serial.read();
    Serial.println("Entering configuration mode.");
    configure();
  }

  Serial.println("Booting...");
  Serial.end();
  
  for(int i=0; i<config.ledConfigCount; i++) {
  	pinMode(config.ledConfigs[i].pin, OUTPUT);
  }
  	pinMode(5, OUTPUT);
}

void loop() {
  digitalWrite(5, HIGH);   // set the LED on
  delay(1000);                  // wait for a second
  digitalWrite(5, LOW);    // set the LED off
  delay(1000);                  // wait for a second
}
