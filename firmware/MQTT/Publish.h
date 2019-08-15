/**********************************
* CalPlug Portable AC Integration
* ESP32 Publish to MQTT via WebSocket
* 
* Navid Bazmoon
* Fall 2018
***********************************/

#ifndef _PUBLISH_
#define _PUBLISH_

#ifdef __cplusplus
extern "C" {
#endif


void publishToMQTT(long long dataSet);
void MQTTsetup();


#ifdef __cplusplus
}
#endif

#endif

/* EOF */
