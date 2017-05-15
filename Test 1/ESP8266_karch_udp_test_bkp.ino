#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
WiFiUDP Udp;
#include "ESP8266_karch_var_declaration.h"
#include "ESP8266_karch_func_declaration.h"
#include "ESP8266_karch_func_tested.h"
char nul = 0;

void setup() {
  Serial.begin(115200); // start (debug) serial
  wifi_connect(); // connect to wifi with debug info

  Udp.begin(UDPPort_listen); // initialize UDP
  Module_to_HAS_init(); // initialize connection with HAS and declare variables
}

void loop() {
  packet_read();
}
