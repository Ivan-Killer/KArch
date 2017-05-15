void packet_read() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    //Serial.print("Received packet of size "); // debug
    //Serial.println(packetSize); // debug
    //Serial.print("From "); // debug
    remote_ip = Udp.remoteIP();
    //Serial.print(remote_ip); // debug
    //Serial.print(", port "); // debug
    //Serial.println(Udp.remotePort()); // debug

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }
    //Serial.println("Contents: "); // debug
    //Serial.println(packetBuffer); // debug
  }

  //"###A;1;0.32;1;0###" ###192.168.97.4;A;1;0.32;1;0###
  if (packetBuffer[3] == 'A') {
    //Serial.println("raboti be"); /*code here*/
  /// { /// from here
  state = packetBuffer[5];
  //Serial.println("State: "); // debug
  //Serial.println(state); // debug
  big = packetBuffer[12];
  //Serial.println("Big: "); // debug
  //Serial.println(big); // debug
  heat = packetBuffer[14];
  //Serial.println("Heat: "); // debug
  //Serial.println(heat); // debug

  for (int i3 = 7 ; i3 <= 10 ; i3++)
  {
    power[(i3 - 7)] = packetBuffer[i3];
  }
  //Serial.println("Power: "); // debug
  //Serial.println(power); // debug
  } /// to here
  // send a reply, to the IP address and port that sent us the packet we received
  /*Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyBuffer);
    Udp.endPacket();*/
}

void dimmer_send() {
  if(state == '0') strcpy(power, "0.00"); // else power remains as received
  if(heat == '1') power[0] += 3; // heat = 1;
  if(big == '1') power[0] += 5; // big = 1;
  //digitalWrite(5, big);
  Serial.println("PWR: ");
  Serial.print(power);
}

void first() {
  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Hello);
  Udp.endPacket();
  delay(1000);

  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(IDcmd);
  Udp.endPacket();
  delay(1000);

  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Var_dec);
  Udp.endPacket();
  delay(1000);

  //Serial.println("Sent cmds to server"); // debug
}

void wifi_connect() {
  WiFi.begin(ssid, pass); //(ssid,<pass>) -cab36","elsys-bg.org"
  //Serial.println(); // debug
  //Serial.print("Wait for WiFi"); // debug

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print("."); // debug
  }
  //Serial.println(""); // debug
  //Serial.println("WiFi connected"); // debug
  //Serial.println("IP address: " + WiFi.localIP().toString()); // debug
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

//next
