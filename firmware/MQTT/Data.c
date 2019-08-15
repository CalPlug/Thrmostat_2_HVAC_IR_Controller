/**********************************
* CalPlug Portable AC Integration
* ESP32 IR Blaster
* 
* Jigar Hira
* Fall 2018
***********************************/

#include <math.h>
#include <assert.h>
#include "driver/rmt.h"
#include "Arduino.h"

#include "Data.h"

/* Converts binary data to microsecond time format for the ESP32 RMT library */
/* binary: data */
/* binarySize: data length in bits */
/* *startMessage: burst pair at the start of the message */
/* *endMessage: burst pair at the end of the message */
/* *zero: 0 burst pair (two element int array) */
/* *one: 1 burst pair (two element int array) */
/* Generates code in rmt format */
void BinaryToRMT(rmt_item32_t items[], long long binary, int binarySize, int *startMessage, int *endMessage, int *zero, int *one)
{
	int bitData;				/* single bit of data */

  /* Initial burst to indicate start */  
  items[0].duration0 = startMessage[0];
  items[0].level0 = 1;
  items[0].duration1 = startMessage[1];
  items[0].level1 = 0;

	
	int i;
	for (i = 0; i < binarySize; i++)	/* iterate through all the bits */
	{
		/* creates a mask, ands it with the data, and shifts back to get the bit data*/
		bitData = (binary & (1 << i)) >> i;
		
		if (bitData == 0)
		{
			items[i + 1].duration0 = zero[0];		/* adds burst pair to send array */
      items[i + 1].level0 = 1;
      items[i + 1].duration1 = zero[1];
      items[i + 1].level1 = 0;
			
		}
		else
		{
			items[i + 1].duration0 = one[0];    /* adds burst pair to send array */
      items[i + 1].level0 = 1;
      items[i + 1].duration1 = one[1];
      items[i + 1].level1 = 0;
		}
				
	}

  /* End burst to indicate end of message */  
  items[binarySize + 1].duration0 = endMessage[0];
  items[binarySize + 1].level0 = 1;
  items[binarySize + 1].duration1 = endMessage[1];
  items[binarySize + 1].level1 = 0;

}

/* EOF */
