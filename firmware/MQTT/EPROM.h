/**********************************
* CalPlug Portable AC Integration
* ESP32 EEPROM Initializer
* 
* Navid Bazmoon
* Fall 2018
***********************************/

#ifndef _EPROM_
#define _EPROM_

#ifdef __cplusplus
extern "C" {
#endif

void EPROMsetup();
void load_data(char* data);

#ifdef __cplusplus
}
#endif

#endif

/* EOF */
