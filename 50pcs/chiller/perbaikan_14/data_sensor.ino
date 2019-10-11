void data_sensor()
{
  //===================Suhu ruang=======================
  int suhu_out= A2;
  float suhu1,data_vs,data_left,data_left2,data_right,nilai_hambatan,nilai_a1,nilai_a2;
  char temp[6];
  
  suhu1=analogRead(suhu_out);
  data_left=suhu1/1023;
  data_left2 = 2.2*data_left*1000;
  data_right = 1 - data_left;
  nilai_hambatan = data_left2/data_right;
  nilai_a1 = 1/nilai_hambatan;  
  nilai_a2 = (nilai_a1*1000000/4.96) + 4.96;
  dtostrf(nilai_a2,4,2,temp);
  s1 = String(temp);
  if (nilai_a2 < 10 || nilai_a2 > 70)
  {
    sor ="0";
  }

  else
  {
    sor="1";
  }
  
  //===================dht==============================
  delay(500);
  t_in  = dht_in.readTemperature();
  h_in  = dht_in.readHumidity();
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
    sir =1;
    hir = 1;
  }
  
  //===================ampere===========================
 irms = amp.calcIrms(1480)-0.05;  // Calculate Irms only
  //irms=irms-0.25;
  if(irms < 0.05)
  {
    irms = 0.00;
    ar = "0";
  }
else
{
  ar ="1";
}
  /*RunningStatistics inputStats;                 // create statistics to look at the raw test signal
  inputStats.setWindowSecs(pjgdata);
   
  while( true ) 
  {   
    nilaiADC = analogRead(A1);  // read the analog in value:
    inputStats.input(nilaiADC);  // log to Stats function
    irms = C + grad * inputStats.sigma();
  }*/
  
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

}
