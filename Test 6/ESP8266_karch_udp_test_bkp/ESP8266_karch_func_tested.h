void wifi_connect() {
  WiFi.begin(ssid,pass);
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

void Module_to_HAS_init() {
  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Hello);
  Udp.endPacket();
  //delay(1000); //(cmd_delay);
  yield();

  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Var_dec); // was IDcmd
  Udp.endPacket();
  //delay(1000); //(cmd_delay);
  yield();

  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Read_cmd); // was Var_dec
  Udp.endPacket();
  //delay(1000); //(cmd_delay);
  yield();

  Serial.println("Successfully sent commands to server"); // debug
}
