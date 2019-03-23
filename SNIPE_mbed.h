/*
 * A library for controlling SNIPE LoRa radio.
 *
 * @Author Rooney.Jang
 * @Date 08/28/2018
 *
 */

#ifndef SNIPE_h
#define SNIPE_h

#define LORA_AES_OFF   0
#define LORA_AES_ON    1

#define LORA_CH_1 1     //921.9 Mhz
#define LORA_CH_2 2     //922.1 Mhz
#define LORA_CH_3 3     //922.3 Mhz
#define LORA_CH_4 4     //922.5 Mhz
#define LORA_CH_5 5     //922.7 Mhz
#define LORA_CH_6 6     //922.9 Mhz
#define LORA_CH_7 7     //923.1 Mhz
#define LORA_CH_8 8     //923.3 Mhz

#define LORA_SF_7   7
#define LORA_SF_8   8
#define LORA_SF_9   9
#define LORA_SF_10  10
#define LORA_SF_11  11
#define LORA_SF_12  12
#define SHORTWORD 10
#define MAXWORD 51
#include <string>
#include <stdlib.h>
#include "mbed.h"
#include "platform\ATCmdParser.h"
#include "drivers\UARTSerial.h"

class SNIPE
{
  private:
  UARTSerial *_serial;
  ATCmdParser *_parser; //should be point??
  int		_timeOut;

  public:
 /*
  * A simplified constructor taking only a Stream ({Software/Hardware}Serial) object.
  * The serial port should already be initialised when initialising this library.
  */
  SNIPE(PinName TX_PIN, PinName RX_PIN); // default baud rate - 115200 /9600
  SNIPE(PinName TX_PIN, PinName RX_PIN, int baud);
  ~SNIPE();
  
  /*
  * Initialization the module.
  */
  bool lora_init(void);  

 /*
  * Reset the module.
  */
  void lora_reset(void);
 
 /*
  * Get the frequency of the module.
  */
  string lora_getFreq(void);

 /*
  * Set the frequency of the module.
  */
  bool lora_setFreq(int freq);

 /*
  * Get the Tx Power of the module.
  */
  string lora_getTxp(void);

 /*
  * Set the Tx Power of the module.
  */
  bool lora_setTxp(int txp);

 /*
  * Get the Spreading Factor of the module.
  */
  string lora_getSf(void);

 /*
  * Set the Spreading Factor of the module.
  */
  bool lora_setSf(int sf);

 /*
  * Get the Rx Timeout of the module.
  */
  string lora_getRxtout(void);

 /*
  * Set the Rx Timeout of the module.
  */
  bool lora_setRxtout(int rxtout);

 /*
  * Get the Tx Timeout of the module.
  */
  string lora_getTxtout(void);

 /*
  * Set the Tx Timeout of the module.
  */
  bool lora_setTxtout(int txtout);

 /*
  * Set the module AES mode, the module defaults to AES mode.
  * mode  = 0: Set the module to AES Disable mode.
  * mode  = 1: Set the module to AES Enable mode.
  */
  bool lora_setAESMode(int mode);

 /*
  * Get the module AES Key.
  */
  string lora_getAppKey(void);

 /*
  * Set the module AES Key.
  * appKEY : Application key as a HEX string. Example "a5 84 99 8d 0d bd b1 54 51 a3 40 8f 92 9d 38 f5" 
  */
  bool lora_setAppKey(string appKEY);

 /*
  * Get the module RSSI.
  */
  string lora_getRssi(void);

 /*
  * Get the module SNR.
  */
  string lora_getSnr(void);

 /*
  * Gets the firmware version number of the module.
  * Only applies to the firmware that the module programmed for the SNIPE AT command.
  */
  string lora_getVersion(void);

 /*
  * Apply the Configuration value to the module.
  * Configuration value : Frequency, TX Power, Spreading Factor, RX Timeout, TX Timeout
  */
  bool lora_setConf(void);

 /*
  * Send Text Data to the module
  */
  bool lora_send(string Text);

 /*
  * Send Binary Data to the module
  */
  bool lora_sendBinary(string Hex);

 /*
  * Returns the data received by the module.
  * 
  */
  string lora_recv(void);

 /*
  * Returns the binary data received by the module.
  * 
  */
  string lora_recvBinary(void);
 
 /*
  * Send a raw command to the SNIPE module.
  * Returns the raw string as received back from the SNIPE.
  * If the SNIPE replies with multiple line, only the first line will be returned.
  */
  string sendRawCommand(string command);

  string read();  
};
#endif
