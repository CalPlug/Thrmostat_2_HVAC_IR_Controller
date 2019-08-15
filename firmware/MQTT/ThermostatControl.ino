/**********************************
* CalPlug Portable AC Integration
* ThermostatControl
* 
* Jigar Hira & Navid Bazmoon 
* Fall 2018
***********************************/

#include "driver/rmt.h" /* ESP32 RMT driver library */

#include "Constants.h"	/* Constants */
#include "Data.h"		/* Data processing */
#include "NESTSignal.h" /* NEST signal handling */
#include "Publish.h"
#include "EPROM.h"
#include "AP.h"

int ISR = 0;  /* Trigger for ISR */

/* Delay variables */
long previousTime = 0;      /* clock tick at previous execution */
unsigned long currentTime;  /* current clock tick */
  

rmt_config_t config;  /* ESP32 RMT configuration */
rmt_item32_t items[LENGTH + 2]  /* RMT send array */;

long long data;  /* data to be sent */

int zero[2] = {ZERO_0, ZERO_1}; /* one and zero burst pairs */   
int one[2] = {ONE_0, ONE_1};

int startMessage[2] = {START_0, START_1};  /* Start message - Does not change between codes */
int endMessage[2] = {END_0, END_1};  /* End message - Does not change between codes */

void setup() {

char epromData[150];
 MQTTsetup ();
 EPROMsetup();
 APsetup(); 
load_data (epromData);  
 if (strstr (epromData, "Default") != NULL){
   
 }
 
  Serial.begin(115200); /* Begin serial monitor */

  /* Input signals from NEST */
  pinMode(AC, INPUT);
  pinMode(HEAT, INPUT);
  pinMode(FAN, INPUT);
  pinMode(HUMIDIFIER, INPUT);

  /* Interrupts */
  attachInterrupt(digitalPinToInterrupt(AC), TriggerISR, CHANGE); /* Sets pin, Interrupt Service Routine (ISR), Trigger */
  attachInterrupt(digitalPinToInterrupt(HEAT), TriggerISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(FAN), TriggerISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(HUMIDIFIER), TriggerISR, CHANGE);

  /* ESP32 RMT Configuration Settings */
  config.rmt_mode = RMT_MODE_TX;
  config.channel = RMT_CHANNEL_0;
  config.gpio_num = IR_LED;                                 /* pin on the ESP32 that is being controlled */
  config.mem_block_num = 1;
  config.tx_config.loop_en = 0;
  config.tx_config.carrier_en = 1;                          /* enables carrier signal (modulation) */
  config.tx_config.idle_output_en = 1;
  config.tx_config.idle_level = RMT_IDLE_LEVEL_LOW;         /* default signal is low */
  config.tx_config.carrier_level = RMT_CARRIER_LEVEL_HIGH;  /* data is modulated on the high signals */
  config.tx_config.carrier_duty_percent = 50;               /* carrier duty cyle */
  config.tx_config.carrier_freq_hz = FREQUENCY;             /* frequency of the carrier signal */
  config.clk_div = 80;                                      /* resultion -> ESP32 clock speed is 80MHz so division of 8 gives us 1MHz resolution or 1us per tick */

  rmt_config(&config);  /* Apply RMT configuration settings */
  rmt_driver_install(config.channel, 0, 0); /* install  the ESP32 RMT driver */
  
}

void loop() {

  long long dataForMQTT;  /* Data to send to the MQTT Server */

  if (ISR)
  {
    
    delay(10); /* This is to ensure the digitalRead from the pin is the correct value after the interrupt */
    
    dataForMQTT = SendIR(); /* Generates the IR code and sends the signal */

     publishToMQTT(dataForMQTT);


    ISR = 0;  /* reset ISR variable */     
  }

  currentTime = millis(); /* get the current clock */
  if ((currentTime - previousTime) > POLLRATE)  /* Checks if time interval has passed */
  {
    previousTime = currentTime; /* reset the previous execution time */

    SendIR(); /* Generates the IR code and sends the signal */
    
  }
}


/* Polls the inputs and generates IR command code. Then sends the command via RMT library */
long long SendIR()
{
  /* reads the current input values and generates an IR code to send */
  data = GenerateIRCode(digitalRead(AC), digitalRead(HEAT), digitalRead(FAN), digitalRead(HUMIDIFIER));

  /* Converts the IR binary code to the RMT format and stores the data in (rmt_item32_t) items */
  BinaryToRMT(items, data, LENGTH, startMessage, endMessage, zero, one);

  /* Sends the IR code */
  rmt_write_items(config.channel, items, LENGTH + 2, IRREPEAT);

  Serial.println((int) data, BIN);

  /* Logs to serial monitor */
  Serial.println("Message Sent");

  return data;
}


/* Lightweight ISR to trigger interrupt function */
void TriggerISR()
{
  ISR = 1;  /* ISR global variable */
  
}

/* EOF */
