int AC_pin = 9;//Pin to s-l
int AC_pin2 = 10;//Pin to h
byte dim = 0; //Initial brightness level from 0 to 255, change as you like!0

float dimF = 0;
int brightness = 0;
int heat = 0;
int big = 0;

void setup() {
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  pinMode(AC_pin, OUTPUT);
  pinMode(AC_pin2, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  attachInterrupt(0, light, FALLING);//When arduino Pin 2 is FALLING from HIGH to LOW, run light procedure!
}

void light() {
  if (brightness < 1) {
    digitalWrite(AC_pin, LOW); //Turn TRIAC completely OFF if dim is 0
  }

  if (brightness > 254) {
    digitalWrite(AC_pin, HIGH); //Turn TRIAC completely ON if dim is 255
  }

  if (brightness > 0 && brightness < 255) { //Dimming part, if dim is not 0 and not 255
    delayMicroseconds(34 * (255 - brightness));
    digitalWrite(AC_pin, HIGH);
    delayMicroseconds(500);
    digitalWrite(AC_pin, LOW);
  }

  if (heat) {
    digitalWrite(AC_pin2, HIGH); //Turn TRIAC completely ON if heat is > 0
    //Serial.println("Heater is ON");
  }
  else {
    digitalWrite(AC_pin2, LOW); //Turn TRIAC completely OFF if heat is 0
    //Serial.println("Heater is OFF");
  }
}

void loop() {
  if (Serial.available()) {
    for (int i2 = 0 ; Serial.available() > 0 ; i2++)
    {
      dim = (Serial.read() - '0');
      //Serial.print(dim);
      //Serial.print(" --- t-t --- ");
      //Serial.println(i2);
      delay(50);
      switch (i2) {
        case 0: dimF = dim; break;
        case 2: dimF += ( ((float)dim) / 10.0 ); break;
        case 3: dimF += ( ((float)dim) / 100.0 ); break;
      }
    }

    if (dimF > 1.00) {
      switch ((int)dimF) {
        case 3: {
            dimF -= 3.00;
            heat = 1;
            big = 0;
          } break;
        case 4: {
            dimF -= 3.00;
            heat = 1;
            big = 0;
          } break;
        case 5: {
            dimF -= 5.00;
            heat = 0;
            big = 1;
          } break;
        case 6: {
            dimF -= 5.00;
            heat = 0;
            big = 1;
          } break;
        case 8: {
            dimF -= 8.00;
            heat = 1;
            big = 1;
          } break;
        case 9: {
            dimF -= 8.00;
            heat = 1;
            big = 1;
          } break;
      }
    }
    else {
      heat = 0;
      big = 0;
    }

    brightness = (int)(dimF * 255);
    digitalWrite(5, big);
    //Serial.print("--- total --- ");
    //Serial.print(brightness);
    //Serial.println(" --- test ---");
  }
}
