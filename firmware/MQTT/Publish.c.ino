/**********************************
* CalPlug Portable AC Integration
* ESP32 Publish to MQTT via WebSocket
* 
* Navid Bazmoon
* Fall 2018
***********************************/


#include "Publish.h"
#include <WiFi.h>
#include <WebSocketClient.h>
#include <PubSubClient.h>

//MQTT Credentials 
const char* userName = "Naviiid";
const char* passwordPub =  "12345678";
const char* mqttServer = "m10.cloudmqtt.com";
const int mqttPort = 17934;
const char* mqttUser = "dkpljrty";
const char* mqttpasswordPub = "ZJDsxMVKRjoR";


//Websocket Credentials 
char path[] = "/echo";
char host[] = "demos.kaazing.com";

WebSocketClient webSocketClient;

WiFiClient ESP32Client;
WiFiClient clientW;
PubSubClient client(ESP32Client);


 
void MQTTsetup() {
   
  WiFi.begin(userName, passwordPub);
 
  while (WiFi.status() != WL_CONNECTED) {
    
    delay(500);
    Serial.println("Connecting to WiFi Network......");
    
  }
 
  Serial.println("Nice! Connected to the WiFi network.");
 
  client.setServer(mqttServer, mqttPort);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT Server.......");
 
    if (client.connect("ESP32Client", mqttUser, mqttpasswordPub )) {
 
      Serial.println("Your are now connected to mqtt.");
 
    } else {
 
      Serial.print("Sorry! The connection failed !");
      Serial.print(client.state());
      delay(2000);
    }

    
  }

  if (clientW.connect(host, 80)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
  }

  publishToMQTT( 1);
  
  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(clientW)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
  }
  
 }


 void publishToMQTT(long long dataSet) //make sure to do anclient connected check before calling!
 {
    // To write multiple fields for MQTT Posting
   char payload[255];
   
  snprintf(payload, sizeof(payload), "%lld", dataSet);
for (int i=0; i<10; i++) {  client.publish("esp/test", "This is a test !");
                            }
}

/*
void loop() {

  String data;

  client.loop(); 
   
  if (client.connected()) {
 
    webSocketClient.sendData("Information Sent: Information is sent and will be echoed back");
 
    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }
 
  } else {
    Serial.println("Client disconnected.");
  }
 
  delay(3000);
 
}
*/
