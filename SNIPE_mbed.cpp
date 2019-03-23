/*
 * A library for controlling SNIPE LoRa radio.
 *
 * @Author Rooney.Jang
 * @Date 08/28/2018
 *
 */

#include "mbed.h"
#include <iostream>
#include "SNIPE_mbed.h"

// extern "C" {
// #include "string.h"
// #include "stdlib.h" // for what??
// }

/*
   @param serial Needs to be an already opened Stream ({Software/Hardware}Serial) to write to and read from.
 */

SNIPE::SNIPE(PinName TX_PIN, PinName RX_PIN)
{ 
	_serial = new UARTSerial(TX_PIN, RX_PIN, 115200);
	_parser = new ATCmdParser(_serial);
	_timeOut = 2000;
	_parser->set_delimiter( "\r\n" );
	_parser->set_timeout(int(_timeOut + 500));
}; // default baud rate - 115200 /9600
SNIPE::SNIPE(PinName TX_PIN, PinName RX_PIN, int baud) 
{ 
	_serial = new UARTSerial(TX_PIN, RX_PIN, baud); 
	_parser = new ATCmdParser(_serial);
	_timeOut = 2000;
  _parser->set_delimiter( "\r\n" );
	_parser->set_timeout(int(_timeOut + 500));
};
SNIPE::~SNIPE()
{
	delete _parser;
	delete _serial;
}
bool SNIPE::lora_init()
{
	//int cnt = 10;	//retry count
	_parser->send("AT");
	if(!(_parser->recv("OK"))){
		return false;
    }
	else{
		return true;
	}
}

void SNIPE::lora_reset()
{
	_parser->send("ATZ");
}


string SNIPE::lora_getFreq()
{
	string ret;
	int channel;
	char buffer[SHORTWORD];
	_parser->send("AT+FREQ=?");
	if(_parser->recv("%d", &channel) && _parser->recv("OK")) {
		ret = "\nchannel is ";
		itoa(channel, buffer, 10);
		ret += buffer;
		return ret;
	}
	return ret;
}

bool SNIPE::lora_setFreq(int freq)
{
	char buffer[SHORTWORD];
	itoa(freq, buffer, 10); // need to do trim every this functions
	string temp_ret = "AT+FREQ=";
	temp_ret += buffer;
	const char* ret = temp_ret.c_str();
	_parser->send(ret);
	if (_parser->recv("OK"))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

string SNIPE::lora_getTxp()
{
	string ret;
	char buffer[SHORTWORD];
	int channel;
	_parser->send("AT+TXP=?");
	if(_parser->recv("%d", &channel) && _parser->recv("OK")) {
		ret = "\nTXP is ";
		itoa(channel, buffer, 10);
		ret += buffer;
		return ret;
	}
	return ret;
}

bool SNIPE::lora_setTxp(int txp)
{
	char buffer[SHORTWORD];
	itoa(txp, buffer, 10);
	string temp_ret = "AT+FREQ=";
	temp_ret += buffer;
	const char* ret = temp_ret.c_str();
	_parser->send(ret);
	if (_parser->recv("OK"))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

string SNIPE::lora_getSf()
{	
	string ret;
	char buffer[SHORTWORD];
	int channel;
	_parser->send("AT+SF=?");
	if(_parser->recv("%d", &channel) && _parser->recv("OK")) {
		ret = "\nSF is ";
		itoa(channel, buffer, 10);
		ret += buffer;
		return ret;
	}
	return ret;
}

bool SNIPE::lora_setSf(int sf)
{
	char buffer[SHORTWORD];
	itoa(sf, buffer, 10);
	string temp_ret = "AT+FREQ=";
	temp_ret += buffer;
	const char* ret = temp_ret.c_str();
	_parser->send(ret);
	if (_parser->recv("OK"))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

string SNIPE::lora_getRxtout()
{
	string ret;
	char buffer[SHORTWORD];
	int channel;
	_parser->send("AT+RXTOUT=?");
	if(_parser->recv("%d", &channel) && _parser->recv("OK")) {
		ret = "\nRXTOUT is ";
		itoa(channel, buffer, 10);
		ret += buffer;
		return ret;
	}
	return ret;
}

bool SNIPE::lora_setRxtout(int rxtout)
{
	/* Serial timeout calibration */
	if(_timeOut < rxtout){
		_timeOut = rxtout;
		_parser->set_timeout(int(_timeOut+500) );
	}
	char buffer[SHORTWORD];
	itoa(rxtout, buffer, 10);
	string temp_ret = "AT+FREQ=";
	temp_ret += buffer;
	const char* ret = temp_ret.c_str();
	_parser->send(ret);
	if (_parser->recv("OK"))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

string SNIPE::lora_getTxtout()
{
	string ret;
	char buffer[SHORTWORD];
	int channel;
	_parser->send("AT+TXTOUT=?");
	if(_parser->recv("%d", &channel) && _parser->recv("OK")) {
		ret = "\nTXTOUT is ";
		itoa(channel, buffer, 10);
		ret += buffer;
		return ret;
	}
	return ret;
}

bool SNIPE::lora_setTxtout(int txtout)
{
	/* Serial timeout calibration */
	if(_timeOut < txtout){
		_timeOut = txtout;
		_parser->set_timeout( int(_timeOut+500) );
	}
	char buffer[SHORTWORD];
	itoa(txtout, buffer, 10);
	string temp_ret = "AT+FREQ=";
	temp_ret += buffer;
	const char* ret = temp_ret.c_str();
	_parser->send(ret);
	if (_parser->recv("OK"))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool SNIPE::lora_setAESMode(int mode)
{
	string ver;
	switch (mode)
	{
		case 0:
			ver = "AT+USEAES=0"; //Set AES Disable mode.
			break;
		case 1:
			ver = "AT+USEAES=1"; //Set AES Enable mode.
			break;
		default:
			return false;
	}
	const char* ret = ver.c_str();
	_parser->send(ret);
	if (_parser->recv("OK"))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

string SNIPE::lora_getAppKey()
{
	//string ret = sendRawCommand(F("AT+APPKEY=?"));
	string ret;
	char buffer[SHORTWORD];
	char appkey[MAXWORD];
	int value;
	_parser->send("AT+APPKEY=?");
	if(_parser->recv("%50s", appkey)) { // && _parser->recv("OK")
		ret = "\nappkey is ";
		ret += appkey;
		return ret;
	}
	return ret;
}

bool SNIPE::lora_setAppKey(string appKEY)
{
	//string command = "";
	if (appKEY.length() != 47 )
	{
		//printf("The parameter appKEY is set incorrectly!");
		return false;
	}

	//command = "AT+APPKEY=" + appKEY;
	//printf("%s", command);
	//string ret = sendRawCommand(command);
	string temp_ret = "AT+APPKEY=" + appKEY;
	const char* ret = temp_ret.c_str();
	_parser->send(ret);
	if (_parser->recv("OK"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

string SNIPE::lora_getRssi()
{
	string ret;
	char buffer[SHORTWORD];
	int channel;
	_parser->send("AT+RSSI=?");
	if(_parser->recv("%d", &channel) && _parser->recv("OK")) {
		ret = "\nRSSI is ";
		itoa(channel, buffer, 10);
		ret += buffer;
		return ret;
	}

	return ret;
}

string SNIPE::lora_getSnr()
{
	string ret;
	char buffer[SHORTWORD];
	int channel;
	_parser->send("AT+SNR=?");
	if(_parser->recv("%d", &channel) && _parser->recv("OK")) {
		ret = "\nSNR is ";
		itoa(channel, buffer, 10);
		ret += buffer;
		return ret;
	}

	return ret;
}

string SNIPE::lora_getVersion()
{
	string ret;
	char buffer[SHORTWORD];
	int channel;
	_parser->send("AT+VER=?");
	if(_parser->recv("%d", &channel) && _parser->recv("OK")) {
		ret = "\nVER is ";
		itoa(channel, buffer, 10);
		ret += buffer;
		return ret;
	}
	return ret;
}

bool SNIPE::lora_setConf()
{
	string temp_ret = "AT+LORASET";
	const char* ret = temp_ret.c_str();
	_parser->send(ret);
	if (_parser->recv("OK"))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

bool SNIPE::lora_send(string Text)
{
	if (Text.length() > 120 )
	{
		printf("The number of characters exceeded 120!");
		return false;
	}
	string temp_ret = "AT+SEND=" + Text;
	const char* ret = temp_ret.c_str();
	_parser->send(ret);
	if (_parser->recv("OK"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SNIPE::lora_sendBinary(string Hex)
{
	if (Hex.length() > 240 )
	{
		printf("The number of hex characters exceeded 240!");
		return false;
	}
	
	string temp_ret = "AT+SENDB=" + Hex;
	const char* ret = temp_ret.c_str();
	_parser->send(ret);
	if (_parser->recv("OK"))
	{
		return true;
	}
	else
	{
		return false;
	}
}

string SNIPE::lora_recv()
{
	string ret;
	char buffer[SHORTWORD];
	char recv_string[MAXWORD];
	_parser->send("AT+RECV=?");
	if(_parser->recv("%50s", recv_string) && _parser->recv("OK")) {
		ret = "\nrecv : ";
		ret += recv_string;
		return ret;
	}
	return ret;
}

string SNIPE::lora_recvBinary()
{
	string ret;
	char buffer[SHORTWORD];
	int channel;
	_parser->send("AT+RECV=?");
	if(_parser->recv("%d", &channel) && _parser->recv("OK")) {
		ret = "\nRECV is ";
		itoa(channel, buffer, 10);
		ret += buffer;
		return ret;
	}
	return ret;

	return ret;
}

string SNIPE::read()
{
	string ret;
	char buffer[SHORTWORD];
	if(_parser->recv("%50s", buffer)) {
		ret = "\nRECEIVED : ";
		ret += buffer;
		return ret;
	}
	return ret;
}