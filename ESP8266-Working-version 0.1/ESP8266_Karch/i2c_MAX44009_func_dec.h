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
void read_lux(int debug) {
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

void Lux_Level_Check(uint32_t lux_in_1, uint32_t lux_in_2, int threshold, int pin) {
  if ((lux_in_1 < threshold) || (lux_in_2 < threshold)) {
    digitalWrite(pin, HIGH);
    Serial.println("Automatic Lights - Lights On - pin 13 high");
  }
  else {
    digitalWrite(pin, LOW);
    Serial.println("Automatic Lights - Lights Off - pin 13 low");
  }
}

void MAX44009_probe() {
  Serial.println("Probe MAX44009: "); // need I2C sensor probe = " I2C scanner " copied to function ?
}

