int ZCD_pin = 12;   //Pin from ZeroCrossDetector
int AC_pin = 13;    //Pin Small Lamp dimmer trigger
//int AC_pin2 = 10; //Pin to OptoTriac
byte dim = 0;       //Initial brightness level from 0 to 255, change as you like!
//byte dim2 = 0;    //Initial brightness level from 0 to 255, change as you like!

void power_ctrl() {
  if (state != lastState) {
    Serial.println("HAS Lights - State Changed - pin 16 500ms high pulse");
    lastState = state;
    digitalWrite(16, HIGH);
    delay(500);
    digitalWrite(16, LOW);
    /*timeElapsed_0 = 0;              // reset the counter to 0 so the counting starts over...
      if (timeElapsed_0 > 100) {
      digitalWrite(16, LOW);
      }*/
  }
  switch(state) {
    case 2: dim = 20; break;
    case 3: dim = 50; break;
    case 4: dim = 80; break;
    case 5: dim = 100; break;
    case 6: dim = 120; break;
    case 7: dim = 150; break;
    case 8: dim = 200; break;
    case 9: dim = 255; break;
    default : dim = 0; break;
  }
}

void light() { // have flicker ?
  if (dim < 1) {
    //Turn TRIAC completely OFF if dim is 0
    digitalWrite(AC_pin, LOW);
  }

  if (dim > 254) { //Turn TRIAC completely ON if dim is 255
    digitalWrite(AC_pin, HIGH);
  }

  if (dim > 0 && dim < 255) {
    //Dimming part, if dim is not 0 and not 255
    delayMicroseconds(34 * (255 - dim));
    digitalWrite(AC_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(AC_pin, LOW);
  }
}

void light_fadeIn() {
  for (int i = 5; i <= 255; i++) {
    dim = i;
    //dim2 = 255 - i;
    delay(20);
  }
}

void light_init() {
  pinMode(AC_pin, OUTPUT);
  //pinMode(AC_pin2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(ZCD_pin), light, FALLING);
  //inside(===during) ISR(=light) - delay(), millis() won't work , micros() might work up to 1~2ms , only delayMicroseconds() work
  //When ESP8266 Pin ZCD_pin is FALLING from HIGH to LOW, run light procedure!
  dim = 0;
}

void stop_serial_debug_info() {
  Serial.setDebugOutput(1); //set some var ?
  Serial.setDebugOutput(0); //disable serial debug info
  delay(10); //doesn't disable debug info
}
