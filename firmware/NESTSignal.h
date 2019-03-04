/**********************************
* CalPlug Portable AC Integration
* ESP32 IR Blaster
* 
* Jigar Hira
* Fall 2018
***********************************/


#ifndef _NESTSIGNAL_
#define _NESTSIGNAL_

#ifdef __cplusplus
extern "C" {
#endif


/* Get signals from the NEST and output corresponding data for IR transmission */
long long GenerateIRCode(int Y, int W, int G, int X);


/* Combines bytes together by concatenating them one after another */
long long CombineBytes(int bytes[]);


#ifdef __cplusplus
}
#endif

#endif

/* EOF */
