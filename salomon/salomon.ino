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

// Web Server
#include <WiFiClient.h>
//#include <ESP8266WiFiMulti.h> 
//#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   // Include the WebServer library

//const char *ssid     = "ZOOROPA";
//const char *password = "m1lanesas";

#define NTP_SERVER "time1.google.com"
#define GMT_TIME_ZONE -3


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, GMT_TIME_ZONE * 3600 , 60000);

RTC_DS1307 rtc;
char daysOfTheWeek[7][4] = {"DOM", "LUN", "MAR", "MIE", "JUE", "VIE", "SAB"};

WiFiManager wifiManager;

ESP8266WebServer server(80);

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


  Serial.println("Sincronizando Time");
  syncTime();

  
//  Serial.println("Iniciando nDNS como salomon.local");
//  if (MDNS.begin("salomon")) {              // Start the mDNS responder for esp8266.local
//    Serial.println("mDNS responder started");
//  } else {
//    Serial.println("Error setting up MDNS responder!");
//  }


  Serial.println("Iniciando HTTP server");
  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.onNotFound(handleNotFound);        // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
  server.begin();                           // Actually start the server
  Serial.println("HTTP server started");

//// Inicio RTC
//  Serial.println( "Iniciando RTC" );
//  if (! rtc.begin()) {
//    Serial.println("Couldn't find RTC");
//    Serial.flush();
//    while (1) delay(10);
//  }

}

void loop() {
  server.handleClient();                    // Listen for HTTP requests from clients
}


void handleRoot() {
  server.send(200, "text/plain", "Salomon, Monitoreo Solar. Luxis");   // Send HTTP status 200 (Ok) and send some text to the browser/client
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
