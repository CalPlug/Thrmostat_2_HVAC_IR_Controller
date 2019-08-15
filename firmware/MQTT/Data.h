/**********************************
* CalPlug Portable AC Integration
* ESP32 IR Blaster
* 
* Jigar Hira
* Fall 2018
***********************************/

#ifndef _SENDIR_
#define _SENDIR_

#ifdef __cplusplus
extern "C" {
#endif


/* Converts binary data to microsecond time format for the ESP32 RMT library */
/* binary: data */
/* binarySize: data length in bits */
/* *startMessage: burst pair at the start of the message */
/* *endMessage: burst pair at the end of the message */
/* *zero: 0 burst pair (two element int array) */
/* *one: 1 burst pair (two element int array) */
/* Generates code in rmt format */
void BinaryToRMT(rmt_item32_t items[], long long binary, int binarySize, int *startMessage, int *endMessage, int *zero, int *one);


#ifdef __cplusplus
}
#endif

#endif

/* EOF */
