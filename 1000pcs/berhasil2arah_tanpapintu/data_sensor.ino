void data_sensor()
{

  //===================Suhu ruang=======================
  reading = analogRead(THERMISTORPIN);
  reading = (1023 / reading)  - 1;     // (1023/ADC - 1) 
  reading = SERIESRESISTOR / reading;  // 10K / (1023/ADC - 1)

  temp = reading / 8900;
  temp = log(temp);
  temp /= 3950;
  temp += 1.0 / (25 + 273.15);
  temp = 1.0 / temp;
  temp -= 273.15;
  temp += 13;

  
  //===================dht==============================
  delay(500);
  t_in  = dht_in.readTemperature();
  h_in  = dht_in.readHumidity();
 
  //===================ampere===========================
 irms = amp.calcIrms(1480)-0.17;  // Calculate Irms only
//  irms=irms-0.25;

  


  IPAddress ip1 = WiFi.localIP();
  ipStr = String(ip1[0])+"."+String(ip1[1])+"."+String(ip1[2])+"."+String(ip1[3]);
  //======kirim sinyal ESP8266
  rssi_signal =WiFi.RSSI();
  quality = rssi_signal + 100;
  qlty = 2*quality;
  if(rssi_signal >= -50)
  {
    qlty = 100;
  }
  else if(rssi_signal <= -100)
  {
    qlty = 0;
  }
 delay(10);
 br=analogRead(s_r);// baca nilai A1 melewati kapasitor
 ar=(br* 0.317176);
 tegg = (ar*0.7289)+12.52515;

     if ( temp < 10 || temp > 70)
  {
    sor ="0";
  }

  else
  {
    sor="1";
  }
   if (isnan(h_in) || isnan(t_in)) 
  {
    //Serial.println("dht error");
    t_in = 0.00;
    h_in = 0.00;
    sir = "0";
          hir = "0";
  }
    else 
  {
    sir ="1";
    hir = "1";
  }
    if(irms < 0.00)
  {
    irms = 0.00;
   ae = "0";
  }
    else 
  {
    ae ="1";
  }
     if(tegg < 100 || tegg > 250 )
  {
    vrr = "0";
  }
  else
  {
    vrr = "1"; 
  }
  
}
