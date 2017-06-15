char ssid[] = "elsys-cab36";
char pass[] = "elsys-bg.org";

unsigned int UDPPort_listen = 20200;      // local port to listen on
unsigned int UDPPort_server = 20200;      // remote port to send to
char packetBuffer[255]; //buffer to hold incoming packet

IPAddress HAS_ip(192, 168, 36, 255); // IP address of HAS
IPAddress broadcast_ip(255, 255, 255, 255); // initial IP address UDP reply sender //95.42.35.63
IPAddress SubnetMask(255, 255, 255, 0);
IPAddress Local_IP(0, 0, 0, 0);
IPAddress remote_ip(0, 0, 0, 0);
IPAddress staticIP(192, 168, 36, 188);
IPAddress gateway(192, 168, 36, 1);
IPAddress subnet(255, 255, 255, 0);

char Hello[] = "###H;###"; // Hello cmd
char IDcmd[] = "###I;big_lamp;###"; // ID cmd
char Var_dec[] = "###D;on@RW;dim@RW;lux_1@R;lux_2@R;###"; // Var declaration
char Var_set[] = "###W;on=0;dim=0;lux_1=0;lux_2=0;###"; // Write initial values to variables
char Read_cmd[] = "###R;on;dim;###"; // Read variables values
char valid[255] = "###A;Valid;###";

int HAS_ip_configured = 0;
int HAS_init_successful = 0;

int packetSize = 0;
unsigned long cmd_delay = 1000;
int udp_state = 0;
long rssi = 0;
