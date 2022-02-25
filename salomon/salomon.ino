/*  ------------------------------
 *  Sistema de monitoreo de Luxis.
 *  ------------------------------
 *  Monitoreo remoto de inversores PIP
 */


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


#define NTP_SERVER "time1.google.com"
#define GMT_TIME_ZONE -3


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, GMT_TIME_ZONE * 3600 , 60000);

RTC_DS1307 rtc;
char daysOfTheWeek[7][4] = {"DOM", "LUN", "MAR", "MIE", "JUE", "VIE", "SAB"};

WiFiManager wifiManager;

ESP8266WebServer server(80);

const int led = 2;

//---- Sincronizo el RTC con el NTP ----//
long syncTime() {
  
  Serial.println( "Sync" );
  timeClient.begin();
  timeClient.update();

  long t = timeClient.getEpochTime();
  Serial.println(t);
  Serial.println(timeClient.getFormattedTime());
//  rtc.adjust(DateTime(t));
  return (t);
}



void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led,LOW); 

  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP  

  digitalWrite(led,HIGH); 
  Serial.begin(115200);
//  Serial.setDebugOutput(true);  
  delay(3000);
  Serial.println("\nEn Marcha!");
  digitalWrite(led,LOW); 



  Serial.println("WiFiMan");
// Inicio WifiManager
  bool res;
  res = wifiManager.autoConnect("Salomon", "ReySalomon");

  if(!res) {
    Serial.println("Failed to connect");
    ESP.restart();
    while (1) delay(50);
  }     

  digitalWrite(led,HIGH); 
  Serial.println("Conectado a WiFi");


  Serial.println("Sincronizando Time");
  syncTime();

  
//  Serial.println("Iniciando nDNS como salomon.local");
//  if (MDNS.begin("salomon")) {              // Start the mDNS responder for esp8266.local
//    Serial.println("mDNS responder started");
//  } else {
//    Serial.println("Error setting up MDNS responder!");
//  }


  digitalWrite(led,LOW); 
  Serial.println("Iniciando HTTP server");
  server.on("/", handleRoot);               // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/led", handleLed);
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
  digitalWrite(led,HIGH); 

}

void loop() {
  server.handleClient();                    // Listen for HTTP requests from clients
}


void handleRoot() {
  long t = syncTime();
  char buf[10];
  String page;

  sprintf(buf, "%lu", t); 
  page = "<h1>Salomon</h1><h2>Solar Monitor</h2><br><p>{t}</p><br><form action=\"/led\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>";
  page.replace("{t}", buf);

  server.send(200, "text/html", page);
  
 }


void handleLed() {                          // If a POST request is made to URI /LED
  digitalWrite(led,!digitalRead(led));      // Change the state of the LED
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}
