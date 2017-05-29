void printWifiStatus() {
  // print SSID
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print IP
  IPAddress ipip = WiFi.localIP();
  Serial.print("IP: ");
  Serial.println(ipip);

  // print RSSI
  long rssi = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void wifi_connect() {
  WiFi.begin(ssid, pass);
  Serial.println(); // debug
  Serial.print("Wait for WiFi"); // debug

  while (WiFi.status() != WL_CONNECTED) {
    /*if (timeElapsed_1 > 500) {
      Serial.print("."); // debug
      timeElapsed_1 = 0;              // reset the counter to 0 so the counting starts over...
      }*/
    delay(500);
    Serial.print("."); // debug
  }
  Serial.println(""); // debug
  Serial.println("WiFi connected"); // debug
  Serial.println("IP address: " + WiFi.localIP().toString()); // debug
  printWifiStatus();
}

void Module_to_HAS_init() {
  Serial.println("Sending commands to server ... ");
  //Serial.println((String)"Module to HAS init : " + success + " elapsed time : " + (millis() - lastTime));
  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Hello);
  Udp.endPacket();
  yield();
  //lastTime = millis();
  delay(cmd_delay);
  //success += 1;

  //if (millis() - lastTime > 1000) {
  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(IDcmd);
  Udp.endPacket();
  yield();
  delay(cmd_delay);
  //success += 1;
  //}

  //if (millis() - lastTime > 2000) {
  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Var_dec);
  Udp.endPacket();
  yield();
  delay(cmd_delay);
  //success += 1;
  //}

  //if (millis() - lastTime > 3000) {
  Udp.beginPacket(HAS_ip, UDPPort_server);//send to server
  Udp.write(Var_set);
  Udp.endPacket();
  yield();
  delay(cmd_delay);
  //success += 1;
  //}

  Serial.println("Successfully sent commands to server");
  /*
    if (success == 4) Serial.println("Successfully sent commands to server"); // debug
    else if (success < 4) {
    Serial.println("Sending commands to server ... "); // debug
    Module_to_HAS_init();
    }
  */
}
