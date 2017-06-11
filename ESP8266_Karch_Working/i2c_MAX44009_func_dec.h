void read_twoByte(int address, uint8_t regH, uint8_t regL, int debug) {
  //Read High Lux Byte
  Wire.beginTransmission(address);
  Wire.write(regH);
  Wire.endTransmission(false);
  Wire.requestFrom((int)address, 1, 0);
  if ( Wire.available() )
  {
    Lux_Byte[0] = Wire.read();
  }
  //Read Low Lux Byte
  Wire.beginTransmission(address);
  Wire.write(regL);
  Wire.endTransmission(false);
  Wire.requestFrom((int)address, 1, 0);
  if ( Wire.available() )
  {
    Lux_Byte[1] = Wire.read();
  }
  Wire.endTransmission(true);

  if (debug == 1) {
    Serial.println((String)" Read from I2C Address " + address + " = HIGH : " + Lux_Byte[0] + " LOW : " + Lux_Byte[1] + " ! ");
  }
}

uint32_t calculate_Lux() {
  Lux_Byte[1] &= 0x0F;
  if ((Lux_Byte[0] >> 4) == 0b1111) {
    Serial.println("Overload"); // if Exponent = 0b1111 ==> Overload
  }
  mLux_value = 45L * round(pow(2, (Lux_Byte[0] >> 4))) * (((Lux_Byte[0] << 4) & 0xF0) | Lux_Byte[1]);
  return mLux_value;
}

//Automatic Sensor Poll and Lux calculation + Optional debug
void read_lux(int debug) { // Debug = 0 -> No output OR Debug = 1 -> Lux output OR Debug = 2 -> Debug output OR Debug = 3 -> Lux output + Debug output
  read_twoByte(I2C_ADDRESS_1 , LUX_HIGH_REG , LUX_LOW_REG , ((debug > 1) ? 1 : 0));
  mLux_value_1 = calculate_Lux();

  read_twoByte(I2C_ADDRESS_2 , LUX_HIGH_REG , LUX_LOW_REG , ((debug > 1) ? 1 : 0));
  mLux_value_2 = calculate_Lux();

  if (debug == 1 || debug > 2) {
    Serial.print(mLux_value_1);
    Serial.println(" from 0x4A !!! ");
    Serial.print(mLux_value_2);
    Serial.println(" from 0x4B !!! ");
  }
}

void Lux_Level_Check(uint32_t lux_in_1, uint32_t lux_in_2, uint32_t threshold, int pin) {
  if ((lux_in_1 < threshold) || (lux_in_2 < threshold)) {
    digitalWrite(pin, HIGH);
    //Serial.println("Automatic Lights - Lights On - pin 14 high");
    state = 1;
  }
  else {
    digitalWrite(pin, LOW);
    //Serial.println("Automatic Lights - Lights Off - pin 14 low");
    state = 0;
  }
}

void I2C_probe() {
  Serial.println("Status: I2C bus scanning... ");
  byte error, i2c_probe_address;
  int nDevices;

  nDevices = 0;
  for (i2c_probe_address = 1; i2c_probe_address < 127; i2c_probe_address++ )
  {
    Wire.beginTransmission(i2c_probe_address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("Status: I2C device found at address 0x");
      if (i2c_probe_address < 16)
        Serial.print("0");
      Serial.print(i2c_probe_address, HEX);
      if (i2c_probe_address == 74 || i2c_probe_address == 75) {
        Serial.println(" - Light intensity sensor MAX44009 !");
      }
      else
        Serial.println(" !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Status: Unknown error at address 0x");
      if (i2c_probe_address < 16)
        Serial.print("0");
      Serial.println(i2c_probe_address, HEX);
      if (i2c_probe_address == 74 || i2c_probe_address == 75) {
        Serial.println(" - Light intensity sensor MAX44009 !");
      }
      else
        Serial.println(" !");
    }
  }
  if (nDevices == 0)
    Serial.println("Status: No I2C devices found\n");
  else
    Serial.println((String)"Status: Done - I2C bus scanning found " + nDevices + " devices :)");

  yield();
  delay(700);           // wait N seconds for next scan
}
