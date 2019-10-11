
#include <WiFiEsp.h>
#include <SoftwareSerial.h>
//#include <Filters.h>
#include <EmonLib.h>
#include <DHT.h>


#ifndef HAVE_HWSERIAL1
SoftwareSerial Serial1(11, 10); // RX, TX
#endif

#define s_r            A0
#define SERIESRESISTOR 10000  
#define dhttype DHT22   // tipe DHT 22  (AM2302), AM2321
//#define dht_pin_in A3
//#define dht_pin_in A3
#define door_pin_a  4 //pintu 1 pin ke 2
#define led_r       5 //led merah pin ke 5
#define led_g      13 //led hijau pin ke 13
#define led_b       6 //led hijau pin ke 6
#define buzzer      8 //buzzer pin ke 8
#define THERMISTORPIN  A3  

String s1="0.00";
String merk;
String data_2;
String data_value;
String str_id;
String str_host;
String str_ssid;
String str_pass;
String str_value; 
String str_timer;
String str_door ;  
String str_t_door;
String test;
String str_st;
String data;
String perangkat = "CA0008";
String mood;
String yy;
String zz;
String Respon = "";
String sir;
String sor;
String hir = "0";
String ar;
String rest;
String tegangan;


bool a ;
bool b ;
bool c ;
bool statusKomunikasiWifi = false;
bool responDariServer = false;


double irms = 0;
long rssi_signal;

float ampin      = A1; //sensor arus pin A1
float t_in       = 0.00; //suhu pertama kali dibaca
float h_in       = 0.00; //kelembapan pertama kali dibaca
float reading;
float tempe;
float T;


int nilaiCT        = 24; // 24 untuk 10A, 20 untuk 20A
int door_state_a   = 0;  // pertama kali keadaan pintu 1(pintu terbuka)
int m;                 // integer m = variabel memasukkan ssid password menggunakan awalan "?"
int n;
int o;
int p;
int kondpintu ;
int pnt ;
int timer_int    = 0;
int qlty         = 50;
int quality;
int w = 0;
int x = 1;
int y = 0;
int z = 0;
int kiw = 30;
int pinghost;
int bis=0;
int suhu_out= A2;




char ssid[] = "ISEMSCHILLER";           
char pass[] = "1nterlog4kupadamu";           
char host[] = "10.3.141.1";        
const char* php = " /html/chiller.php";
const int port   = 8080;

unsigned long wktawal = 0;
unsigned long countbuzzer = 60000;


int status = WL_IDLE_STATUS;     // the Wifi radio's status
WiFiEspClient client;

EnergyMonitor amp; 
//DHT dht_in(dht_pin_in, dhttype);

void setup() 
{
 Serial.begin(9600);
 Serial1.begin(9600);
 amp.current(ampin, nilaiCT);
 pinMode(door_pin_a, INPUT);
 pinMode(led_g, OUTPUT);
 pinMode(buzzer, OUTPUT);
 pinMode(led_b, OUTPUT);
 pinMode(led_r, OUTPUT);
 a=true;
 b=false;
 c=false;
 //dht_in.begin();
 wifi_set();
}

void loop() 
{
unsigned long wktnow = millis();
unsigned long tk = wktnow -wktawal;
data_sensor();
kondisi_pintu();
//Serial.println(tk);
if( tk  > countbuzzer)
 {
  bis++;
  if (bis == 120)
  {
    rest="0";
  }
  else
  {
    rest="1";
  }
  Serial.print(bis);
  data_sensor();
  delay(300);
  request();
  delay(100);
  wktawal = millis();
  if (bis == 120)
  {
    delay(500);
    asm volatile (" jmp 0");
  }
  }
 }                                                                                                   
