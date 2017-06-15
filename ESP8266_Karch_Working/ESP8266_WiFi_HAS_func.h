void packet_decode() {
  if ( packetBuffer[3] == 'E' ) { // ###E;Error;###
    Serial.println("Server: Error message - has been received");
    /*char *pch;
      int empty = 0;
      pch = strtok (packetBuffer, ";.");
      empty = atoi(pch);
      pch = strtok (NULL, ";.");*/
    Serial.println((String)"Server: Error");// = " + pch);
    yield();
  }
  else if ( packetBuffer[3] == 'A' ) { // ###R;on;dim;### -> ###A;1;255;###
    if ( strcmp(packetBuffer, valid) == 0 ) {
      Serial.println("Server: Parameter Valid Reply has been received");
    }
    else {
      Serial.println("-- Dimming config --"); // debug
      char *pch;
      int empty = 0;
      pch = strtok (packetBuffer, ";.");
      empty = atoi(pch);
      pch = strtok (NULL, ";."); state = atoi(pch);
      pch = strtok (NULL, ";."); dimming = atoi(pch);
      Serial.println((String)"Config: Power state Big lamp   : " + state); // debug
      //Serial.println(state); // debug
      Serial.println((String)"Config: Power level Small lamp : " + dimming); // debug
      //Serial.println(dim); // debug
      power_ctrl();
      yield();
    }
  }
  else if ( packetBuffer[3] == 'H' ) { // ###H;95.42.35.63;###
    Serial.println("-- HAS IP config --"); // debug
    char *pch;
    int empty = 0;
    pch = strtok (packetBuffer, ";.");
    empty = atoi(pch);
    pch = strtok (NULL, ";."); HAS_ip[0] = atoi(pch);
    pch = strtok (NULL, ";."); HAS_ip[1] = atoi(pch);
    pch = strtok (NULL, ";."); HAS_ip[2] = atoi(pch);
    pch = strtok (NULL, ";."); HAS_ip[3] = atoi(pch);
    HAS_ip_configured = 1;
    Serial.print("Config: HAS IP configured : ");
    Serial.println(HAS_ip);
    yield();
  }
  else if ( packetBuffer[3] == 'S' ) { // ###S;5;###
    char *pch;
    int empty = 0;
    pch = strtok (packetBuffer, ";.");
    empty = atoi(pch);
    pch = strtok (NULL, ";.");
    Serial.println((String)"Server: Successful writen " + pch + " bytes");
    yield();
  }
  packetBuffer[3] = NULL;
}
