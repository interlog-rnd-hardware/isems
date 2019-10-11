void kondisi_pintu()
{
  door_state_a = digitalRead(door_pin_a);
  //door_state_b = digitalRead(door_pin_b);
  //door_state_c = digitalRead(door_pin_c);
  if(door_state_a == LOW)
  { 
    c=false;
    if(a == true)
    {
      kondpintu = 0;
      str_st = String(kondpintu);
      z=0;
      zz = String(z);
      b=true;
    }
    a=false;
  }
  else if(door_state_a == HIGH)
  {
   if(b == true)
    { 
      int kondpintu = 1;
      str_st = String(kondpintu);
      a=true;   
      b=false; 
      x=0;
      zz = String(x);
      g = true; 
      //request();   
    }
    
    while(door_state_a = HIGH)  
    {
       door_state_a = digitalRead(door_pin_a);
       if (b == false)   //buka
       {
        if (client.connected()) //mastiin matiin koneksi kalo lg ngirim
        {
          client.stop();
          client.flush();
          statusKomunikasiWifi = false;
          responDariServer = true;
        }
        
        int kondpintu = 1;
        str_st = String(kondpintu);
        a=true;   
        b=false; 
        x=1;
        zz = String(x);
        data_sensor();
        delay(100);
        statusKomunikasiWifi = kirimKeDatabase(mood);
        b=true;     
        delay(100);  
       }
       
       x++;
//      menghitung durasi
       delay(1000);
       int oy;
       oy = x-1;
       Serial.println(oy);
 
       if(x == kiw) //kondisi buka 30s
       {        
         if (client.connected()) 
         {
          client.stop();
          client.flush();
          statusKomunikasiWifi = false;
          responDariServer = true;
          }
          g = true;
          data_sensor();
          delay(100);
          zz = String(x);
          statusKomunikasiWifi = kirimKeDatabase(mood); 
          int kondpintu = 0;
          str_st = String(kondpintu);
          c=true;
          x=1; 
          zz = String(x);   
       }
       
          else if(door_state_a == LOW)//tutup
          {
            
          if (client.connected()) 
        {
          client.stop();
          client.flush();
          statusKomunikasiWifi = false;
          responDariServer = true;
        }
            buzzer_tone(0);
            g = true;
            int kondpintu = 0;
            str_st = String(kondpintu);
            c=false;
          zz = String(oy);
          delay(10);
          data_sensor();
          delay(100);
          statusKomunikasiWifi = kirimKeDatabase(mood);
          delay(50);
          x=0;
          zz = String(x); 

          break;
       }

      if(c == true)
        {
          while(door_state_a != LOW)
          {
            digitalWrite(led_g, LOW);
            digitalWrite(led_r, LOW);
            door_state_a = digitalRead(door_pin_a);
//            door_state_b = digitalRead(door_pin_b);
//            door_state_c = digitalRead(door_pin_c);
//            int x = 0;
            x++;
            delay(500);
            Serial.println(x);
            if(x == 30)
            {
           if (client.connected()) 
        {
          client.stop();
          client.flush();
          statusKomunikasiWifi = false;
          responDariServer = true;
        }
              g = true;
              zz = String(x); 
              int kondpintu = 1;
              str_st = String(kondpintu);
              data_sensor();
              delay(100);
              statusKomunikasiWifi = kirimKeDatabase(mood);
              delay(10); 
              x=1; 
              zz = String(x);      
            }
            buzzer_tone(1);
            digitalWrite(led_b, HIGH);
            delay(50);
//            buzzer_tone(0);
            digitalWrite(led_b, LOW);
//            delay(50);
//            buzzer_tone(1);
//            digitalWrite(led_b, HIGH);
//            delay(50);
//            buzzer_tone(0);
//            digitalWrite(led_b, LOW);
            delay(300);
            if(door_state_a == LOW)
            {
              digitalWrite(led_b, LOW);
              digitalWrite(led_g, HIGH);
              digitalWrite(led_r, LOW);
              c=false;
              //request();
              //x=0;
              break; 
            }
          }
        }
    }
  }
}
