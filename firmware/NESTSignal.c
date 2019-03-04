/**********************************
* CalPlug Portable AC Integration
* ESP32 IR Blaster
* 
* Jigar Hira
* Fall 2018
***********************************/


#include "NESTSignal.h"
#include "Constants.h"


/* Get signals from the NEST and output corresponding data for IR transmission */
long long GenerateIRCode(int Y, int W, int G, int X)
{
	int bytes[NUM_OF_BYTES];	/* 5 bytes of data */
	
	bytes[0] = BYTE_4;	/* this byte is always 0b00000000 */
	bytes[1] = BYTE_3;
	bytes[4] = ADDRESS;	/* address byte is always the same */
	
	if (!Y == 1)	/* AC is on */
	{
		bytes[2] = MODE_AC;	/* AC mode */
		bytes[3] = TEMP_64;	/* 64 degrees F */
				
	}
	else if (!W == 1)	/* HEAT is on */
	{
		bytes[2] = MODE_HEAT;	/* HEAT mode */
		bytes[3] = TEMP_81;	/* 81 degrees F */
    
	}
	else if (!G == 1)	/* FAN is on */
	{
		bytes[2] = MODE_FAN;	/* FAN mode */
		bytes[3] = TEMP_64_MEDFAN;	/* 64 degrees F (MED FAN) */

	}
	else if (!X == 1)	/* HUMIDIFIER is on */
	{
		bytes[2] = MODE_HUMIDIFIER;	/* HUMIDIFIER mode */
		bytes[3] = TEMP_64;	/* 64 degrees F */
    
	}
	else	/* OFF */
	{
		bytes[2] = MODE_OFF;	/* OFF */
		bytes[3] = TEMP_64;	/* 64 degrees F */
    
	}

  return CombineBytes(bytes); 
}


/* Combines bytes together by concatenating them one after another */
long long CombineBytes(int bytes[])
{
	long long data = 0;	/* Data */
	long long byte = 0;	/* each byte of data */

	int i;
	for (i = 0; i < NUM_OF_BYTES; i++)
	{
		
		byte = bytes[i];
		byte = byte << (8 * ((NUM_OF_BYTES - 1) - i));	/*shift the bits over the appropriate amount */
		data += byte;			                              /* add the byte to the data */
	
	}
	
	return data;
}



/* EOF */
