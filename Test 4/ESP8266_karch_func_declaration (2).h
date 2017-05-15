void packet_read() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size "); // debug
    Serial.println(packetSize); // debug
    Serial.print("From "); // debug
    remote_ip = Udp.remoteIP();
    Serial.print(remote_ip); // debug
    Serial.print(", port "); // debug
    Serial.println(Udp.remotePort()); // debug

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    Serial.println("Contents: "); // debug
    Serial.println(packetBuffer); // debug
  }
  // send a reply, to the IP address and port that sent us the packet we received
  /*Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyBuffer);
    Udp.endPacket();*/
}

void wifi_connect() {
  WiFi.begin(ssid); //(ssid,<pass>) -cab36","elsys-bg.org"
  Serial.println(); // debug
  Serial.print("Wait for WiFi"); // debug

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); // debug
  }
  Serial.println(""); // debug
  Serial.println("WiFi connected"); // debug
  Serial.println("IP address: " + WiFi.localIP().toString()); // debug
}

void first() {
  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Hello);
  Udp.endPacket();

  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(IDcmd);
  Udp.endPacket();

  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Var_dec);
  Udp.endPacket();
  
  Serial.println("Sent cmds to server"); // debug
}
/*Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  char ipBuffer[255];
  WiFi.localIP().toString().toCharArray(ipBuffer, 255);
  Udp.write(ipBuffer);
  Udp.endPacket();*/

/*//W ne raboti
  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Var_set);
  Udp.endPacket();*/

void dimmer_send() {
    //dim_val &= 
    dim_val = B10000000;
    Serial.write(dim_val);
}

//next
