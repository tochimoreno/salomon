// Sistema de monitoreo de Luxis.

// WiFi
#include <ESP8266WiFi.h>

// NTP
#include <NTPClient.h>
#include <WiFiUdp.h>

// RTC
#include <RTClib.h>

const char *ssid     = "ZOOROPA";
const char *password = "m1lanesa";
#define NTP_SERVER "time1.google.com"
#define GMT_TIME_ZONE -3

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, GMT_TIME_ZONE * 3600 , 60000);

RTC_DS1307 rtc;
char daysOfTheWeek[7][4] = {"DOM", "LUN", "MAR", "MIE", "JUE", "VIE", "SAB"};


//---- Sincronizo el RTC con el NTP ----//
void syncTime() {
  
  Serial.println( "Sync" );
  timeClient.begin();
  timeClient.update();

  long actualTime = timeClient.getEpochTime();
  Serial.println(timeClient.getFormattedDate());
  Serial.println(timeClient.getFormattedTime());
//  rtc.adjust(DateTime(actualTime));

}



void setup() {

// Inicio Serial
  Serial.begin(115200);
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

// Inicio WiFi
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
//    Serial.print ( "." );
  }
  Serial.println( "Conectado a WiFi " );

// Inicio NTP
  Serial.println( "Iniciando NTP" );
  timeClient.begin();

//// Inicio RTC
  Serial.println( "Iniciando RTC" );
//  if (! rtc.begin()) {
//    Serial.println("Couldn't find RTC");
//    Serial.flush();
//    while (1) delay(10);
//  }

  syncTime();
}

void loop() {


}
