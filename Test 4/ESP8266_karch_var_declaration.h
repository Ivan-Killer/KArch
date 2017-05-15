char ssid[] = "elsys";
char pass[] = "";

unsigned int UDPPort_listen = 20300;      // local port to listen on
unsigned int UDPPort_server = 20250;      // RxD port of Home Automation Server(HAS)
char packetBuffer[255]; //buffer to hold incoming packet
//char replyBuffer[] = "acknowledged";       // a string to send back

IPAddress HAS_ip(192, 168, 97, 50); // IP address of HAS
IPAddress remote_ip(255, 255, 255, 255); // initial IP address UDP reply sender

char Hello[] = "###H;###";    // Hello cmd
char IDcmd[] = "###I;small_lamp;###";    // ID cmd
char Var_dec[] = "###D;light_intensity@R;state@RW;power@RW;###"; // Var declaration
//char Var_set[] = "###W;small_lamp.light_intensity=1;###"; // Can't write to HAS (not ready)
char Read_cmd[] = "###R;small_lamp.state;small_lamp.power;###";
//char Read_cmd[] = "###R;small_lamp.state;small_lamp.power;big_lamp.on;pechka.on;###"; // check ?
char power[15] = "0.50";
char state = '1';
char big = '0';
char heat = '0';
