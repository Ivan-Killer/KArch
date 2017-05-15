#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
WiFiUDP Udp;
#include "ESP8266_karch_var_declaration.h"
#include "ESP8266_karch_func_declaration.h"

void serialEvent() {
  first();
}

void setup() {
  Serial.begin(115200); // start (debug) serial
  wifi_connect(); // connect to wifi with debug info

  Udp.begin(UDPPort_listen); // initialize UDP
  first(); // initialize connection with HAS and declare variables
  Serial.println("Sent cmds to server"); // debug
}

void loop() {
  packet_read();
}/*
  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Read_cmd); // request variables to read
  Udp.endPacket();
  packet_read(); // read received UDP packets
  //packetBuffer
  //###A;1;0.00;###
  char local_state = packetBuffer[5] - 48; // -48(='0') bacause packetBuffer is in ASCII
  char local_power_char[5] = "0";
  for (int i1 = 7 ; i1 <= 10 ; i1++) {
    local_power_char[(i1 - 7)] = packetBuffer[i1];
  }
  Serial.println("Read - state: "); // debug
  Serial.println(local_state); // debug
  Serial.println("Read - power: "); // debug
  Serial.println(local_power_char); // debug

  //dimmer_send(); // send byte[state(1bit) + power(7bit)] to Arduino Dimmer

  delay(5000);
  }*/
