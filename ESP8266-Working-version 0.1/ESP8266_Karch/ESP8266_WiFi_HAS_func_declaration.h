void packet_decode() {
  if ( packetBuffer[3] == 'A' && packetBuffer[5] >= '0' && packetBuffer[5] <= '9' ) {
    Serial.print("-- Packet Decode --"); // debug
    state = packetBuffer[5];
    Serial.print(" Power : "); // debug
    Serial.println(state - '0'); // debug
    /*for (int i3 = 7 ; i3 <= 10 ; i3++)
      {
        power[(i3 - 7)] = packetBuffer[i3];
      }
      Serial.print("Power after : "); // debug
      Serial.println(power); // debug*/
    packetBuffer[3] = NULL;
    power_ctrl();
  };
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
  }

  packet_decode(); // Get values from HAS reply
}
