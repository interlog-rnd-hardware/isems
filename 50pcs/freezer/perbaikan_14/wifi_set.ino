void wifi_set()
  {

  WiFi.init(&Serial1);

  if (WiFi.status() == WL_NO_SHIELD) 
  {
    Serial.println("esp01 bermasalah");
    asm volatile (" jmp 0");
    //while (true);   
  }
  while (status != WL_CONNECTED) 
  {
    Serial.print("Menyambungkan ");
    Serial.println(ssid); 
    status = WiFi.begin(ssid, pass);
  }
  Serial.println("Tersambung"); 
 // printWifiStatus();
  Serial.println();
  Serial.println("Server");
  if (client.connect(host, port)) 
  {
    Serial.println("Ok");
    digitalWrite(led_g, HIGH);
    digitalWrite(led_r, LOW);
  }

  else
  {
    digitalWrite(led_g, LOW);
    digitalWrite(led_r, HIGH);
  }
  }

  //void printWifiStatus()
//{
  //Serial.print("SSID: ");// print the SSID of the network you're attached to
  //Serial.println(WiFi.SSID());
 
 //IPAddress ip = WiFi.localIP();
  //Serial.print("IP Address: "); // print your WiFi shield's IP address
  //Serial.println(ip);

//  long rssi = WiFi.RSSI();
 // Serial.print("Signal strength (RSSI):");  // print the received signal strength
 // Serial.print(rssi);
 // Serial.println(" dBm");
//}
