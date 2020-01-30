void komunikasidata()
{
  responDariServer = false;
  
//  if(kali == 2)  //ngirim data sensor tiap 1 menit
//  {
//    if (g == false)
//    {
//      statusKomunikasiWifi = ambileeprom(perangkat);
//      waktuMulai = millis();
//      responDariServer = true;
//    }
//    kali = 0;
//  }

  if(kirims < millis() - waktuMulai) //ambil data relay tiap 30s
  {
    
    if (g == false)
    {
      data_sensor();
      statusKomunikasiWifi = kirimKeDatabase(mood);
      waktuMulai = millis();
      kali++;
    }
    g = false;
    
  }
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
      statusKomunikasiWifi = false;
      responDariServer = true;
    }
  }
  // penanganan data yang diterima dari server
  if(responDariServer)
  {
    int posisiData = Respon.indexOf("\r\n\r\n");
    String Data = Respon.substring(posisiData+4);
    Data.trim();
    posisiData = Data.indexOf('=');
    Serial.println(Data);
    SetSockStatus();
    jmlhchar = Data.length(); 
      if (jmlhchar > 17)
      {
        int iVariabel = Data.indexOf('='); String sVariabel = Data.substring(0,iVariabel);
        int iSSID = Data.indexOf('=', iVariabel + 1); String sSSID = Data.substring(iVariabel +1 ,iSSID);
        int iPassword = Data.indexOf('=', iSSID + 1); String sPassword = Data.substring(iSSID + 1, iPassword);
        int iTimerbuzzer  = Data.indexOf('=', iPassword + 1); String sTimerbuzzer  = Data.substring(iPassword + 1, iTimerbuzzer);
        int iTimerkirim   = Data.indexOf('=', iTimerbuzzer + 1); String sTimerkirim   = Data.substring(iTimerbuzzer + 1, iTimerkirim);          
    }
   }
  Respon = "";
}
