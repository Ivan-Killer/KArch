//variables
static uint8_t LUX_HIGH_REG  = (0x03); // static const uint8_t
static uint8_t LUX_LOW_REG   = (0x04); // static const uint8_t
static uint8_t I2C_ADDRESS_1 = (0x4A); // static const uint8_t
static uint8_t I2C_ADDRESS_2 = (0x4B); // static const uint8_t

uint32_t mLux_value   = 0;
uint32_t mLux_value_1 = 0; // static unsigned long
uint32_t mLux_value_2 = 0; // static unsigned long

unsigned int Lux_Byte[2] = { 0 , 0 }; // Lux_Byte[0] == High Lux Byte AND Lux_Byte[1] == Low Lux Byte

// functions
void read_twoByte(int address, uint8_t regH, uint8_t regL, int debug);
void read_lux(int debug);
void Lux_Level_Check(uint32_t lux_in_1, uint32_t lux_in_2, uint32_t threshold, int pin);
void I2C_probe();
uint32_t calculate_Lux();