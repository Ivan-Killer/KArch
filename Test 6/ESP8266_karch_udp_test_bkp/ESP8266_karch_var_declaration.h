char ssid[] = "Electronic Net"; //"elsys-cab37";
char pass[] = "qwerty951-j"; //"elsys-bg.org";

unsigned int UDPPort_listen = 20200;      // local port to listen on
unsigned int UDPPort_server = 20200;      // remote port to send to
char packetBuffer[255]; //buffer to hold incoming packet

IPAddress HAS_ip(192, 168, 0, 255); // IP address of HAS
IPAddress remote_ip(192, 168, 0, 255); // initial IP address UDP reply sender

char Hello[] = "###H;###";    // Hello cmd
char IDcmd[] = "###I;tt;###";    // ID cmd
//char Var_dec[] = "###D;light_intensity@R;state@RW;power@RW;###"; // Var declaration
char Var_dec[] = "###D;tt@RW;###";
//char Var_set[] = "###W;small_lamp.light_intensity=1;###"; // Can't write to HAS (not ready)
//char Read_cmd[] = "###R;small_lamp.state;small_lamp.power;###";
char Read_cmd[] = "###R;tt;###";

char power[15];
char state;
byte dim_val = 0;

int packetSize = 0;
int cmd_delay = 1200;
