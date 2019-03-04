/**********************************
* CalPlug Portable AC Integration
* ESP32 IR Blaster
* 
* Jigar Hira
* Fall 2018
***********************************/

#ifndef _CONSTANTS_
#define _CONSTANTS_


#define LENGTH 40        /* Bit length of the data */
#define POLLRATE 60000   /* NEST signal pollrate and period of IR signals in milliseconds */


/* Pin Definitions */
#define IR_LED        GPIO_NUM_21
#define AC            GPIO_NUM_27
#define HEAT          GPIO_NUM_26
#define FAN           GPIO_NUM_25
#define HUMIDIFIER    GPIO_NUM_33


/* IR CODE SETTINGS */
#define FREQUENCY 38000  /* Frequency in hz of carrier signal*/
#define IRREPEAT 1       /* How many times the IR signal will be repeated (1 means no repetition) */

#define ZERO_0  579       /* timings for binary zero burst pair */
#define ZERO_1  579
#define ONE_0   579       /* timings for binary one burst pair */
#define ONE_1   1632

#define START_0  9079     /* timings for start message burst pair */
#define START_1  4474
#define END_0   579       /* timings for end message burst pair */
#define END_1   32767

/* IR CODES */
#define NUM_OF_BYTES 5  /* number of bytes that make up the IR signal */

#define ADDRESS         0b01001011  /* 1st byte of message */
#define BYTE_3          0b00001110  /* 4th byte of message */
#define BYTE_4          0b00000000  /* 5th byte of message */

/* 2nd byte of the message */
#define MODE_AC         0b01000001
#define MODE_HEAT       0b01000111
#define MODE_FAN        0b01000101
#define MODE_HUMIDIFIER 0b01000011
#define MODE_OFF        0b01000000

/* 3rd byte of the message */
#define TEMP_64         0b00001010  /* 64F which is the lowest setting for the AC */
#define TEMP_64_MEDFAN  0b10001010  /* 64F with the MED fan setting*/
#define TEMP_81         0b00011011  /* 81F which is the highest setting for the heater */


#endif

/* EOF */
