void send_lux(IPAddress ip_address, unsigned int udp_port) {
  Udp.beginPacket(ip_address, udp_port);
  Udp.write("###W;lux_1=");
  sprintf(buf_1, "%d", mLux_value_1);
  Udp.write(buf_1);
  Udp.write(";lux_2=");
  sprintf(buf_2, "%d", mLux_value_2);
  Udp.write(buf_2);
  Udp.write(";###");
  Udp.endPacket();
  yield();
}

void send_udp(IPAddress ip_address, unsigned int udp_port, char *cmd) {
  Udp.beginPacket(ip_address, udp_port);
  Udp.write(cmd);
  Udp.endPacket();
  yield();
  delay(cmd_delay);
}

void power_ctrl() {
  if (state != lastState) { // change
    lastState = state;
    if (state == 1) {
      Serial.println("Power control - Automatic Lights - Lights On - pin 14 high");
    }
    if (state == 0) {
      Serial.println("Power control - Automatic Lights - Lights Off - pin 14 low");
    }
    Serial.println("HAS Lights - State Changed - pin 16 500ms pulse");
    //digitalWrite(16, HIGH);
    delay(200);
    //digitalWrite(16, LOW);
  }
}

void light() {  // have flicker ?
  if (dim < 1) { //Turn TRIAC completely OFF if dim is 0
    digitalWrite(AC_pin, LOW);
  }

  else if (dim > 254) {  //Turn TRIAC completely ON if dim is 255
    digitalWrite(AC_pin, HIGH);
  }

  else if (dim > 0 && dim < 255) { //Dimming part, if dim is not 0 and not 255
    delayMicroseconds(34 * (255 - dim));
    digitalWrite(AC_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(AC_pin, LOW);
  }
}

void light_fade() {
  for (int i = 5; i <= 255; i++) {
    if (micros() - lastTime_fadeTimer > interval_fadeTimer) {
      lastTime_fadeTimer = micros();
      dim = i; // fade in
      //dim2 = 255 - i; // fade out
    }
  }
}

void light_init() {
  dim = 0;
  pinMode(AC_pin, OUTPUT);
  //pinMode(AC_pin2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ZCD_pin), light, FALLING);
  //inside(=during) ISR(=light) -> delay(), millis() won't work , micros() might work up to 1~2ms , only delayMicroseconds() work
  //When ESP8266 Pin ZCD_pin is FALLING from HIGH to LOW, run light procedure!
}

void stop_serial_debug_info() {
  //uart_set_debug(UART_NO); // still doesn't work
  //Serial.setDebugOutput(1); //set some var ?
  //Serial.setDebugOutput(0); //disable serial debug info but doesn't works disabling debug info
  delay(10);
}
