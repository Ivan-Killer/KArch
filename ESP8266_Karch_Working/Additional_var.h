long unsigned int lastTime_slowCode = 0;
long unsigned int interval_slowCode = 750 * 1000;
long unsigned int lastTime_fadeTimer = 0;
long unsigned int interval_fadeTimer = 20 * 1000;
char buf_1[4], buf_2[4];
uint32_t dark_threshold = 10000;
byte op_mode = 0; // mode of operation = Manual, Automatic with Server Connection, Autonomous Automatic

int lastState = 0;
int state = 0;
int dimming = 0;
//int power = 0;
//byte dim_val = 0;
//int testing = 0;

int ZCD_pin = 12;   //Pin from ZeroCrossDetector
int AC_pin = 13;    //Pin Small Lamp dimmer trigger
//int AC_pin2 = 10; //Pin to OptoTriac
byte dim = 0;       //Initial brightness level from 0 to 255, change as you like!
//byte dim2 = 0;    //Initial brightness level from 0 to 255, change as you like!

byte ok = 0;
