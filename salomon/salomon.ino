
// Sistema de monitoreo de Luxis.

// WiFi
#include <ESP8266WiFi.h>

// NTP
#include <NTPClient.h>
#include <WiFiUdp.h>

// RTC
#include <RTClib.h>

const char *ssid     = "<SSID>";
const char *password = "<PASSWORD>";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time1.google.com", 3600, 60000);

RTC_DS1307 rtc;
char daysOfTheWeek[7][4] = {"DOM", "LUN", "MAR", "MIE", "JUE", "VIE", "SAB"};


void setup() {
  Serial.begin(115200);
#ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

// Inicio NTP
  timeClient.begin();

// Inicio RTC
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }


// Busca Hora
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());

  timeClient.
  rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop() {


}
