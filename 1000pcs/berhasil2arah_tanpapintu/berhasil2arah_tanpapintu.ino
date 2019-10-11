#include "WiFiEsp.h"
#include <SoftwareSerial.h>
#include <EmonLib.h>
#include <DHT.h>
#include <EEPROM.h>

#ifndef HAVE_HWSERIAL1
SoftwareSerial Serial1(11, 10); // RX, TX
#endif

#define dhttype DHT22   // tipe DHT 22  (AM2302), AM2321
#define dht_pin_in     8
#define door_pin_a     2 //pintu 1 pin ke 2
#define led_b          3 //led biru pin ke 3 
#define led_r          4 //led merah pin ke 5
#define led_g          5 //led hijau pin ke 13
#define rly            9
#define buzzer         7 //buzzer pin ke 8
#define s_r            A0
#define THERMISTORPIN  A1
#define SERIESRESISTOR 10000    
#define ampin          A2


int kali=0;
int kalieeprom = 0;
int attemptconnect=0;
int bis=0;
int nilaiCT = 20; // 24 untuk 10A, 20 untuk 20A
int door_state_a;  // pertama kali keadaan pintu 1(pintu terbuka)
int kondpintu =0;
int pnt ;
int timer_int    = 0;
int qlty         = 50;
int quality;
int jmlhchar;
int apa = 0;
int kiw;
int x=1;
int z;
int br;
int ar,yr=0;
int relays;


double irms = 0;
long rssi_signal;
char ssid[25];        // Isi dengan nama profil Wifi
char pass[20];            // password wifi
char host[] = "10.3.141.1";     // alamat access point yang telah terinstall XAMPP local host
const char* php = " /chiller.php";
char timerbuzzer1[4];
char timerkirim1[3];  //kirim tiap semenit
char crelay[3];
char erelay[3];

float t_in       = 0.00; //suhu pertama kali dibaca
float h_in       = 0.00; //kelembapan pertama kali dibaca
int tegg;
float reading;
float temp;


char namaVariabel[] = "Variabel";
String text = "";
String Respon = "";
String mood;
String s1="0.00";
String ae;
String ipStr;
String perangkat = "CA0002";
String zz;
String str_st;
String variabel;
String nilai = "1";
String nilai1 ;
String sir;
String sor;
String hir;
String rest="1";
String vrr;
String tegangan;

bool responDariServer = false;
bool a ;
bool b ;
bool c ;
bool d ;
bool e ;
bool f ;
bool g;
bool relawal;
 
bool statusKomunikasiWifi = false;
bool statusKomunikasiWifi1 = false;

long waktuMulai;
long kirim; //minta data setiap 5000ms
long kirims;

EnergyMonitor amp; 
DHT dht_in(dht_pin_in, dhttype);
 
WiFiEspClient client;
int status = WL_IDLE_STATUS;

//==============================eeprom============================
const int EEPROM_MIN_ADDR = 0;
const int EEPROM_MAX_ADDR = 511;
boolean eeprom_is_addr_ok(int addr)
{
  return ((addr >= EEPROM_MIN_ADDR) && (addr <= EEPROM_MAX_ADDR));
}
boolean eeprom_write_bytes(int startAddr, const byte* array, int numBytes) 
{
  int i;
  if (!eeprom_is_addr_ok(startAddr) || !eeprom_is_addr_ok(startAddr + numBytes)) 
  {
    return false;
  }
  for (i = 0; i < numBytes; i++) 
  {
    EEPROM.write(startAddr + i, array[i]);
  }
  return true;
}

boolean eeprom_write_string(int addr, const char* string) 
{
  int numBytes; 
  numBytes = strlen(string) + 1;
  return eeprom_write_bytes(addr, (const byte*)string, numBytes);
}

boolean eeprom_read_string(int addr, char* buffer, int bufSize) {
  byte ch;
  int bytesRead;
  if (!eeprom_is_addr_ok(addr)) {
    return false;
  }
  
  if (bufSize == 0) { 
    return false;
  }
  
  if (bufSize == 1) {
    buffer[0] = 0;
    return true;
  }
  bytesRead = 0;
  ch = EEPROM.read(addr + bytesRead);
  buffer[bytesRead] = ch;
  bytesRead++;
  while ( (ch != 0x00) && (bytesRead < bufSize) && ((addr + bytesRead) <= EEPROM_MAX_ADDR) ) {  
    ch = EEPROM.read(addr + bytesRead);
    buffer[bytesRead] = ch;
    bytesRead++;
  }
  if ((ch != 0x00) && (bytesRead >= 1)) 
  {
    buffer[bytesRead - 1] = 0;
  }
  return true;
}

void setup()
{
  digitalWrite(rly,HIGH);
  Serial.begin(9600);
  Serial1.begin(9600);
  eeprom_read_string(18, ssid, 25);
  delay(20);
  eeprom_read_string(44, pass,20);
  delay(20);
  eeprom_read_string(65, timerbuzzer1, 4);
  delay(20);
  eeprom_read_string(70, timerkirim1, 3);
  delay(20);
  eeprom_read_string(74, erelay, 3);
  
  kiw = atoi(timerbuzzer1);
  kirim = atol(timerkirim1);
  kirims = kirim*1000;
  relawal=true;
//  Serial.begin(9600);
//  Serial1.begin(9600);
  WiFi.init(&Serial1);
  dht_in.begin();
  amp.current(ampin, nilaiCT);  
  delay(20);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }
 
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    attemptconnect += 1;
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
    if (attemptconnect == 10)
    {
      digitalWrite(12,HIGH); //hard reset arduino
      attemptconnect = 0;
    }
  }
  attemptconnect = 0;
  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
  digitalWrite(led_g,HIGH);
  pinMode(door_pin_a,INPUT);
  pinMode(led_g, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led_b, OUTPUT);
  pinMode(led_r, OUTPUT);
  pinMode(rly, OUTPUT);
  pinMode(dht_pin_in,OUTPUT);
  a= true;
  b= false;
  c= false;
  d= false;
  e= false;
  f= false;
  relawal=true;
  waktuMulai = millis();
  printWifiStatus();
  
}
 
void loop()
{
  if (digitalRead(rly) == LOW && relawal==true)
  {
    digitalWrite(rly,HIGH);
    relawal=true;
  }
  data_sensor();
  kondisi_pintu();
  if (g == false)
  {
    if ((d == true) && (e==true))
    {
      statusKomunikasiWifi = ambileeprom(perangkat);
      //client.stop();
      e =false;
    }
    if (!client.connected()) 
   {
    client.stop();
    client.flush();
    statusKomunikasiWifi = false;
    responDariServer = true;
    }
  }
    if(kali == 4)  //ambil data relay tiap 15 menit
    {
      if (g == false)
      {
        statusKomunikasiWifi = relay(perangkat);
        //client.stop();
        text = "";
        kali = 0;
        kalieeprom++;
        

        waktuMulai = millis();
      }
       if (!client.connected()) 
      {
        client.stop();
        client.flush();
        statusKomunikasiWifi = false;
        responDariServer = true;
      }
    }

     if(kirims < millis() - waktuMulai)
  {
    if (g == false)
    {
      //data_sensor();
      delay(100);
      statusKomunikasiWifi = kirimKeDatabase(mood);
      kali++;
      waktuMulai = millis();
      //client.stop();
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
 
  // penanganan data yang diretima dari server
  if(responDariServer)
  {
    
    //Serial.println(Respon);
    int posisiData = Respon.indexOf("\r\n\r\n");
    String Data = Respon.substring(posisiData+4);
    Data.trim();
    posisiData = Data.indexOf('=');
    if(posisiData > 1)
    {
      variabel = Data.substring(0,posisiData);
      nilai = Data.substring(posisiData+1);
      int iSSID = nilai.indexOf('='); String sSSID = nilai.substring(0,iSSID);
      int iPassword = nilai.indexOf('=', iSSID + 1); String sPassword = nilai.substring(iSSID + 1, iPassword);
      int iTimerbuzzer  = nilai.indexOf('=', iPassword + 1); String sTimerbuzzer  = nilai.substring(iPassword + 1, iTimerbuzzer);
      int iTimerkirim   = nilai.indexOf('=', iTimerbuzzer + 1); String sTimerkirim   = nilai.substring(iTimerbuzzer + 1, iTimerkirim);          
//      int iRelay = nilai.indexOf('=', iTimerkirim + 1); String sRelay = nilai.substring(iTimerkirim + 1, iRelay);
      //===========Penanganan respon disini
      Serial.print(variabel);
      Serial.print("=");
      Serial.println(nilai);
      jmlhchar = nilai.length();
      if (jmlhchar > 1 )
      {
        f =true;
        
        
        Respon = "";
        if ((sTimerbuzzer != timerbuzzer1) || (sTimerkirim != timerkirim1))
        {
          //from substring db to char variable
          sTimerbuzzer.toCharArray(timerbuzzer1,4);
          sTimerkirim.toCharArray(timerkirim1,3);
          eeprom_write_string(65, timerbuzzer1);
          eeprom_read_string(65, timerbuzzer1, 4);
          eeprom_write_string(70, timerkirim1);
          eeprom_read_string(70, timerkirim1, 3);
          delay(20);
          kirim = atol(timerkirim1);
          kirims = kirim*1000;
          delay(20);
          kiw = atoi(timerbuzzer1); 
          Serial.println(ssid);
          Serial.println(pass);
          Serial.println(timerbuzzer1);
          Serial.println(timerkirim1);
          delay(500);
          //rest="0";
          //asm volatile ("jmp 0");
        }
        if ((sSSID != ssid) || (sPassword != pass) )
        {
          sSSID.toCharArray(ssid,25);
          sPassword.toCharArray(pass,20);
          //read write eeprom
          eeprom_write_string(18, ssid);
          eeprom_read_string(18, ssid, 25);
          eeprom_write_string(44, pass);
          eeprom_read_string(44, pass,20);
          Serial.println(ssid);
          Serial.println(pass);
          Serial.println(timerbuzzer1);
          Serial.println(timerkirim1);
          delay(500);
           //rest="0";
          //asm volatile ("jmp 0");
        }

//        else
//        {
//          rest="1";
//        }
      }
    }
    if (nilai =="1")
    {
      digitalWrite(rly,HIGH); //malah high
      relawal == false;
      apa = 0; 
    }
    else if (nilai == "0")
    {
     digitalWrite(rly,LOW); //malah low
     relawal= false;
    }
      
//    if (kalieeprom == 96)//sehari
    if (kalieeprom == 3)
    {
      apa++;
      if (apa == 1)
      {
        d = true;
        e = true;
      }
      apa = 0;
      kalieeprom = 0;
    }
    responDariServer = false;
   }
   Respon = "";
}

bool relay(String variabel)
{
  // if you get a connection, report back via serial
  if (client.connect(host, 8080)) {
    Serial.println("Tersambung ke Server ambil database");
    // Make a HTTP request
    client.print("GET /relay.php?variabel=");
    client.print(variabel);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(host);
    client.println("Connection: close");
    client.println();
    return true;
  }
  return false;
}
 
bool kirimKeDatabase(String mood)
{
  mood += perangkat;             mood +="~";
  mood += String(t_in);                  mood +="~";
  mood += String(temp);                  mood +="~";
  mood += String(h_in);                  mood +="~";
  mood += String(irms);                  mood +="~";
  mood += String(qlty);                 mood +="~";
  mood += zz;                    mood +="~";
  mood += str_st;                mood +="~";
  //mood += ipStr;               mood +="~";
  mood += String(tegg);              mood +="~";
  mood += sir;                                     
  mood += sor;
  mood += hir;
  mood += ae;
  mood += vrr;
  //mood += rest;
  
  if (client.connect(host, 8080)) 
  {
  String url; 
  url += php;
  url += "?mood=";
  url += mood; 
     
  client.print("GET");
  client.print(url);
  client.println(" HTTP/1.1");
  client.print("Host: ");
  client.println(host);
  client.println("Connection: close");
  client.println();
  Serial.println(mood);
  digitalWrite(led_g,HIGH);
  return true;
  
  }
  return false;
}

bool ambileeprom(String variabel)
{
  // if you get a connection, report back via serial
  if (client.connect(host, 8080)) {
    Serial.println("Tersambung ke Server ambil database");
    // Make a HTTP request
    client.print("GET /eeprom.php?variabel=");
    client.print(variabel);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(host);
    client.println("Connection: close");
    client.println();
    return true;
  }
  return false;
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("gateway:");
  Serial.print(gateway);
  Serial.println(" ");
 
}
 
