// Sistema de monitoreo de Luxis.

// WiFi
#include <ESP8266WiFi.h>

// NTP
#include <NTPClient.h>
#include <WiFiUdp.h>

// RTC
#include <RTClib.h>

// WiFi Manager
#include <WiFiManager.h> 

//const char *ssid     = "ZOOROPA";
//const char *password = "m1lanesas";

#define NTP_SERVER "time1.google.com"
#define GMT_TIME_ZONE -3


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, GMT_TIME_ZONE * 3600 , 60000);

RTC_DS1307 rtc;
char daysOfTheWeek[7][4] = {"DOM", "LUN", "MAR", "MIE", "JUE", "VIE", "SAB"};

WiFiManager wifiManager;



//---- Sincronizo el RTC con el NTP ----//
void syncTime() {
  
  Serial.println( "Sync" );
  timeClient.begin();
  timeClient.update();

  long t = timeClient.getEpochTime();
  Serial.println(t);
  Serial.println(timeClient.getFormattedTime());
//  rtc.adjust(DateTime(t));
}



void setup() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  

  Serial.begin(115200);
//  Serial.setDebugOutput(true);  
  delay(3000);
  Serial.println("\nEn Marcha!");

  Serial.println("WiFiMan");
// Inicio WifiManager
  bool res;
  res = wifiManager.autoConnect("Salomon", "ReySalomon");

  if(!res) {
    Serial.println("Failed to connect");
    ESP.restart();
    while (1) delay(50);
  }     

  Serial.println("Conectado a WiFi");

// Inicio NTP
  Serial.println( "Iniciando NTP" );
  timeClient.begin();

//// Inicio RTC
//  Serial.println( "Iniciando RTC" );
//  if (! rtc.begin()) {
//    Serial.println("Couldn't find RTC");
//    Serial.flush();
//    while (1) delay(10);
//  }

  syncTime();
}

void loop() {
  Serial.println( "  No hago nada" );
  delay(1000);
}
