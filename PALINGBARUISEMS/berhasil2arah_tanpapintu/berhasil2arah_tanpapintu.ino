#include "WiFiEsp.h"
#include <SoftwareSerial.h>

#ifndef HAVE_HWSERIAL1
SoftwareSerial Serial1(11, 10); // RX, TX
#endif

//yg skrg
#define buzzer         2 
#define led_b          3 
#define led_g          4 
#define led_r          5 
#define door_pin_a     6 
#define dhttype        DHT22
#define dht_pin_in     9

#define THERMISTORPIN   A0  
#define THERMISTORPIN2  A2
#define ampin           A3
#define s_r             A4
#define SERIESRESISTOR  10000  

int kali=0;
int kalieeprom = 0;
int attemptconnect=0;
int bis=0;
int nilaiCT = 28; // 24 untuk 10A, 20 untuk 20A
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
int tegg;
int tegangann;
double irms = 0;
long rssi_signal;

//without eeprom
char ssid[]="ISEMSCHILLER1";        // Isi dengan nama profil Wifi
char pass[]="1nterlog4kupadamu";            // password wifi
char host[] = "10.3.141.1";     // alamat access point yang telah terinstall XAMPP local host
const char* php = " /chiller.php";
char timerbuzzer1[]="30";
char timerkirim1[]="5";  //kirim tiap semenit

float t_in       = 0.00; //suhu pertama kali dibaca
float h_in       = 0.00; //kelembapan pertama kali dibaca
float reading,reading2;
float temp,temp2;
float T;

char namaVariabel[] = "Variabel";
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
WiFiEspClient client;
int status = WL_IDLE_STATUS;

void setup()
{
  init_awal();
  waktuMulai = millis();
//  printWifiStatus();
}
 
void loop()
{
  komunikasidata();
}
 
bool kirimKeDatabase(String mood)
{
//  mood += perangkat;             mood +="~";
//  mood += String(t_in);          mood +="~";
//  mood += String(temp);          mood +="~";
//  mood += String(temp2);         mood +="~";
//  mood += String(h_in);          mood +="~";
//  mood += String(irms);          mood +="~";
//  mood += String(qlty);          mood +="~";
//  mood += zz;                    mood +="~";
//  mood += str_st;                mood +="~";
//  mood += String(tegangann);     mood +="~";
//  mood += sir;                                     
//  mood += sor;
//  mood += hir;
//  mood += ae;
//  mood += vrr;
  
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
 
