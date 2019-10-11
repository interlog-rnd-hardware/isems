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
      int kondpintu = 0;
      str_st = String(kondpintu);
      int z=0;
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
      zz = String(z); 
      //request();   
    }
    
    while(door_state_a == HIGH)
    {
       door_state_a = digitalRead(door_pin_a);
       if (b== false)
       {
      int kondpintu = 1;
      str_st = String(kondpintu);
      a=true;   
      b=false; 
      x=1;
      zz = String(x);
       data_sensor();
       delay(100);
       request();
       b=true;
       }
       x++;
//menghitung durasi
       delay(1000);
       int oy;
       oy = x-1;
       Serial.println(oy);
      if(x == kiw)
       {        
          data_sensor();
          delay(100);
          zz = String(x);
          request(); 
          int kondpintu = 0;
          str_st = String(kondpintu);
          c=true;
          x=1; 
          zz = String(x);        
       }
       else if(door_state_a == LOW)
       {
          int kondpintu = 0;
          str_st = String(kondpintu);
          c=false;
          zz = String(oy);
          delay(10);
          data_sensor();
          delay(100);
          request();
          delay(10);
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
            //door_state_b = digitalRead(door_pin_b);
            //door_state_c = digitalRead(door_pin_c);
            //int x = 0;
            x++;
            delay(500);
            Serial.println(x);
            if(x == 30)
           {
           zz = String(x); 
           int kondpintu = 1;
           str_st = String(kondpintu);
           data_sensor();
           delay(100);
           request();
           delay(10); 
           x=1; 
           zz = String(x);         
           }
            buzzer_tone(1);
            digitalWrite(led_b, HIGH);
            delay(50);
            buzzer_tone(0);
            digitalWrite(led_b, LOW);
            delay(50);
            buzzer_tone(1);
            digitalWrite(led_b, HIGH);
            delay(50);
            buzzer_tone(0);
            digitalWrite(led_b, LOW);
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
