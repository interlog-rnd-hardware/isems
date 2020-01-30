void init_awal()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  
//  kiw = atoi(timerbuzzer1);
//  kirim = atol(timerkirim1);
//  kirims = kirim*1000;
  WiFi.init(&Serial1);
    
  delay(20);
  if (WiFi.status() == WL_NO_SHIELD) 
  {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }
 
//  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
}
}
