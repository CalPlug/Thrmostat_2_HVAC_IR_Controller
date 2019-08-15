/**********************************
* CalPlug Portable AC Integration
* ESP32 Auto AP Script 
* 
* Navid Bazmoon
* Fall 2018
***********************************/
/**********************************
* CalPlug Portable AC Integration
* ESP32 Auto AP Script 
* 
* Navid Bazmoon 
* Fall 2018
***********************************/

#include <WiFi.h>
#include <WebServer.h>
#include <AutoConnect.h>

WebServer Server;

ESP32WebServer Server;

AutoConnect      Portal(Server);

void AProotPage() 

{
  char content[] = "This is a test for ESP32 Access Point";
  Server.send(200, "text/plain", content);
}

void APsetup() 

{
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Server.on("/", rootPage);
  if (Portal.begin()) {
    Serial.println("HTTP server:" + WiFi.localIP().toString());
  }
}

void APloop()

 {
  Portal.handleClient();
}
