// OK - WiFi connect, print status - HAS hello, init, var-dec, var-set - UDP listen - LUX read, check, write
// pin 12 -> ZCD input
// pin 13 -> AC Dimmer trigger output
// pin 14 -> Low Lux Detection
// pin 16 -> Big Lamp power control
// Needs HAS variables ...
// Define Read_request with coresponding packet_decode.if_statement
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
//#include <MAX44009.h>
// gives compile errors
// part of which are because of variables/constants used in the sketch outside of the library
//MAX44009 LUX;
WiFiUDP Udp;
#include "Additional_var.h"
#include "ESP8266_WiFi_HAS_var.h"
#include "i2c_MAX44009_var_dec.h"
#include "ESP8266_Other.h"
#include "ESP8266_WiFi_HAS_func.h"
#include "ESP8266_WiFi_HAS_func_tested.h"
#include "i2c_MAX44009_func_dec.h"

void setup() {
  pinMode(14, OUTPUT);      // Lux low detection
  pinMode(16, OUTPUT);      // Big Lamp power control
  digitalWrite(14, LOW);
  digitalWrite(16, LOW);

  Serial.begin(9600);      // start debug serial
  wifi_connect();           // connect to wifi with debug info
  light_init(); // Enable dimming - Dimming has some flicker
  yield();
  Wire.begin(); // Wire.begin([SDA], [SCL]); // esp8266 I2C is software so should work
  I2C_probe();
  Module_to_HAS_init();     // initialize connection with HAS and declare variables
  ok = 1; // allow execution of the slow code
  op_mode = 0; // 1-auto 0-server
}

void loop() {
  switch(op_mode) {
    case 0: server_mode(); break;
    case 1: autonomous_mode(); break;
    case 2: manual_mode(); break;
    default: break;
  }
}