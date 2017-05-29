// OK - WiFi connect, print status - HAS hello, init, var-dec, var-set - UDP listen - LUX read, check
// pin 12 -> ZCD input
// pin 13 -> AC Dimmer trigger output
// pin 14 -> Low Lux Detection
// pin 16 -> Big Lamp power control
// Needs HAS variables ...
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <Wire.h>
//#include <elapsedMillis.h>
//elapsedMillis timeElapsed_0;
//elapsedMillis timeElapsed_1;
//int lastTime = 0;
//int success = 0;
WiFiUDP Udp;
#include "ESP8266_WiFi_HAS_var_declaration.h"
#include "i2c_MAX44009_var_dec.h"
#include "ESP8266_Other.h"
#include "ESP8266_WiFi_HAS_func_declaration.h"
#include "ESP8266_WiFi_HAS_func_tested.h"
#include "i2c_MAX44009_func_dec.h"

void setup() {
  pinMode(14, OUTPUT);      // Lux low detection
  pinMode(16, OUTPUT);      // Big Lamp power control
  digitalWrite(14, LOW);
  digitalWrite(16, LOW);
  Serial.begin(115200);     // start debug serial
  //stop_serial_debug_info(); // doesn't stop serial debug - does nothing ???
  //light_init(); // Enable dimming - Dimming has some flicker
  Wire.begin();
  yield();
  MAX44009_probe();         // not implemented yet
  wifi_connect();           // connect to wifi with debug info
  yield();
  Udp.begin(UDPPort_listen);// Start listening on UDP
  Module_to_HAS_init();     // initialize connection with HAS and declare variables
  yield();
}

void loop() {
  //dim = 0; // Effectively turns off the lamp
  //light_fadeIn(); // doesn't turn on lamp only controlls brigthness
  //packet_read();
  //read_lux(0); // Debug = 0 -> No output OR Debug = 1 -> Lux output OR Debug = 2 -> Debug output OR Debug = 3 -> Lux output + Debug output
  //Lux_Level_Check(mLux_value_1, mLux_value_2, 10000, 14); // check if Lux level is below threshold(10000) level and if yes turn on pin(14) else turn off pin(14)
}
