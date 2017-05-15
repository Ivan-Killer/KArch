void packet_decode() {
  if (packetBuffer[3] == 'R') {
    Serial.println("-- R check --"); // debug
    //"###R;1;0.32;###"
    state = packetBuffer[5];
    Serial.println("Power before : "); // debug
    Serial.println(power); // debug
    for (int i3 = 7 ; i3 <= 10 ; i3++)
    {
      power[(i3 - 7)] = packetBuffer[i3];
    }
    Serial.println("Power after : "); // debug
    Serial.println(power); // debug
  };
}

void packet_read() {
  // if there's data available, read a packet
  packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet from "); // debug
    //Serial.println(packetSize); // debug
    Serial.print("From "); // debug
    //remote_ip = Udp.remoteIP();
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

  packet_decode(); // Get values from HAS reply
  packetBuffer = NULL;
}
