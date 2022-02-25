# Salomon
Proyecto de monitoreo de generación solar

## Hardware:
* ESP8266 (D1 Mini) conectado a Inversor (PIP) mediante puerto serie (uart)
* Conversor 232 - TTL
* Shield RTC
* Shield DC power
* Fuente 12V a 5V para alimentar al D1 Mini
* PIP tiene RJ45 con TX, RX, GND y 12V
* PIP viene con cable RJ45 - DB9
* Cajita

## Opcionales
* Log en SD

## En server
* Base de datos (influxDB)
* Conector de entrada a la base de datos (si es necesario)
* Sistema de generación de reportes y/o presentaciṕon en vivo (Grafana)

## firmware
* Weemos Di mini (clone)
* Programado en Arduino IDE
* Captive Portal para configurar credenciales de WiFi [github](https://github.com/projetsdiy/ESP8266-Webserver-Tutorials/search?q=wifi-connect-esp8266)
* Librería InverterOfThings para comunicarse con el inversor [github](https://github.com/scottwday/InverterOfThings)
* WebServer para mostrar estado del inversor en vivo en forma local (opcional)
* Guardar datos en db server
* Si no hay conexión con server, loguear localmente (SD, csv, json)
* Subir datos locales el server cuando se restablezca la conexión
* RTC para llevar la hora, sincronizar con NTP [github](https://github.com/radames/NTP_RTC_Sync)


## Referencias:
* [Revisar](https://github.com/tzapu/WiFiManager)

eof