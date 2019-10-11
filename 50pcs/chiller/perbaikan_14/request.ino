void request()
{
  if(statusKomunikasiWifi)
  {
   while (client.available()) 
   {
     char c = client.read();
     Respon += c; 
    }
    if (!client.connected()) 
    {
      client.stop();
      client.flush();
      statusKomunikasiWifi = false;
      responDariServer = true;
    //digitalWrite(led_g, LOW);
    //digitalWrite(led_r, HIGH);
    }
  }
  /*bis++;
  Serial.println(bis);
  if(bis == 10)
  {
    status = WiFi.begin(ssid, pass);
    bis=0;
    x+=4;
    delay(1000);
    data_sensor();
    statusKomunikasiWifi = keDatabase(mood);
    return true;
  }*/
 statusKomunikasiWifi = keDatabase(mood);
 
} 
 bool keDatabase(String mood)
 {
  mood += perangkat;             mood +="~";
  mood += t_in;                  mood +="~";
  mood += s1;                    mood +="~";
  mood += h_in;                  mood +="~";
  mood += irms;                  mood +="~";
  mood += qlty ;                 mood +="~";
  mood += zz;                    mood +="~";
  mood += str_st;                mood +="~";
  mood += sir;                   
  mood += sor;
  mood += hir;
  mood += ar;
  mood += rest;
                 

  
  String url; 
  url += php;
  url += "?mood=";
  url += mood; 
 if (client.connect(host, port)) 
  {
  client.print("GET");
  client.print(url);
  client.println(" HTTP/1.1");
  client.println("Host: 10.3.141.1");
  client.println("Connection: close");
  client.println();
  Serial.println(mood);
  digitalWrite(led_g, HIGH);
  digitalWrite(led_r, LOW);
  return true;
  }
  return false;
}
