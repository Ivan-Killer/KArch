int dimming = 0;

void zero_crosss_int()  // function to be fired at the zero crossing to dim the light
{
  int dimtime = (75 * dimming);  // For 60Hz =>65
  delayMicroseconds(dimtime);    // Off cycle
  digitalWrite(9, HIGH);   // triac firing
  delayMicroseconds(10);         // triac On propagation delay (for 60Hz use 8.33)
  digitalWrite(9, LOW);    // triac Off
}

void setup() {
  pinMode(9, OUTPUT);// Set AC Load pin as output
  attachInterrupt(0, zero_crosss_int, RISING);  // Choose the zero cross interrupt # from the table above
}

void loop()  {
  for (int i = 5; i <= 128; i++) {
    dimming = i;
    delay(10);
  }
}
