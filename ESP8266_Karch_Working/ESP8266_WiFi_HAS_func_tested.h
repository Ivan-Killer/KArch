void broadcast_calc() {
  broadcast_ip[0] = Local_IP[0] | (~SubnetMask[0]);
  broadcast_ip[1] = Local_IP[1] | (~SubnetMask[1]);
  broadcast_ip[2] = Local_IP[2] | (~SubnetMask[2]);
  broadcast_ip[3] = Local_IP[3] | (~SubnetMask[3]);
}

void printWifiStatus() {
  // print SSID
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print RSSI
  Serial.print("RSSI: ");
  Serial.print(rssi);
  Serial.println(" dBm");

  // print ESP8266 MAC Address
  Serial.print("Device MAC Address: ");
  Serial.println(WiFi.macAddress());

  // print Host IP
  Serial.print("Host Unicast IP Address: ");
  Serial.println(Local_IP);

  // print Subnet Mask
  Serial.print("Subnet Mask: ");
  Serial.println(SubnetMask);

  // print Broadcast IP
  Serial.print("Broadcast IP Address: ");
  Serial.println(broadcast_ip);
}

void wifi_connect() {
  WiFi.mode(WIFI_STA); // set WiFi to Client mode
  WiFi.hostname("Automatic-Light-Control-Module-1");
  WiFi.config(staticIP, gateway, subnet);  // (DNS not required) otherwise + dns1 + dns2
  WiFi.begin(ssid, pass);
  Serial.println(); // debug
  Serial.print("Status: Waiting for WiFi connection"); // debug

  while (WiFi.isConnected() == 0) {//WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // debug
  }
  Serial.println(""); // debug
  Serial.println("Status: WiFi Connected"); // debug
  rssi = WiFi.RSSI();
  Local_IP = WiFi.localIP();
  SubnetMask = WiFi.subnetMask();
  broadcast_calc();
  HAS_ip = broadcast_ip;
  printWifiStatus();
  udp_state = Udp.begin(UDPPort_listen);// Start listening on UDP
  if(udp_state == 1) Serial.println((String)"Status: Successfully opened UDP Socket on local port " + UDPPort_listen);
  else if(udp_state == 0) Serial.println((String)"Status: Cannot open UDP Socket on local port " + UDPPort_listen + " - there are no sockets available to use !");
}

void packet_read() {
  // if there's data available, read a packet
  packetSize = Udp.parsePacket();
  if (packetSize) {
    remote_ip = Udp.remoteIP();
    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    // show debug info
    Serial.println((String)"Received packet of size " + packetSize + " from " + remote_ip[0] + '.' + remote_ip[1] + '.' + remote_ip[2] + '.' + remote_ip[3] + " , port " + Udp.remotePort() + " with Contents: " + packetBuffer); // debug
    packet_decode(); // Extract values from HAS reply
  }

  //packet_decode(); // Extract values from HAS reply
}

void Module_to_HAS_init() {
  Serial.println("Status: Home Automation Server initialization ... ");
  send_udp(HAS_ip, UDPPort_server, Hello);
  while (HAS_init_successful == 0) {
    packet_read(); yield();
    if (HAS_ip_configured == 1) {
      Serial.println("Status: Sending commands to server ... ");
      send_udp(HAS_ip, UDPPort_server, IDcmd);
      send_udp(HAS_ip, UDPPort_server, Var_dec);
      send_udp(HAS_ip, UDPPort_server, Var_set);
      HAS_init_successful = 1;
      Serial.println("Status: Successfully sent commands to server");
    }
  }
}
