char ssid[] = "Electronic Net";
char pass[] = "qwerty951-j";

unsigned int UDPPort_listen = 20200;      // local port to listen on
unsigned int UDPPort_server = 20200;      // remote port to send to
char packetBuffer[255]; //buffer to hold incoming packet

IPAddress HAS_ip(95, 42, 35, 63); // IP address of HAS
IPAddress remote_ip(95, 42, 35, 63); // initial IP address UDP reply sender //95.42.35.63

char Hello[] = "###H;###"; // Hello cmd
char IDcmd[] = "###I;big_lamp;###"; // ID cmd
char Var_dec[] = "###D;on@RW;dim@RW;###"; // Var declaration
char Var_set[] = "###W;on=1;###"; // Write initial values to variables
char Read_cmd[] = "###R;on;###"; // Read variables values

//char power[15];
char lastState = 0;
char state = 0;
//byte dim_val = 0;

int packetSize = 0;
int cmd_delay = 1000;
