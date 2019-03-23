#include "SNIPE_mbed.h"
#include "iostream"
#define DEFAULT_BAUD_RATE 115200

#define DISCO_L475 1
#define UBLOX_EVK_ODIN 2

// SELECT YOUR TARGET BOARD
#define TARGET_BOARD UBLOX_EVK_ODIN

#if TARGET_BOARD == DISCO_L475
    #define SERIAL1_TX PA_0 //PC_1
    #define SERIAL1_RX PA_1 //PC_0

#elif TARGET_BOARD == UBLOX_EVK_ODIN
    #define SERIAL1_TX PD_8 //PC_1
    #define SERIAL1_RX PD_9 //PC_0

#endif

Serial pc(USBTX, USBRX);

string lora_app_key = "11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 00";  //16byte hex key

//using namespace std::

int main(){
    pc.baud(115200);

    SNIPE snipe(SERIAL1_TX, SERIAL1_RX, DEFAULT_BAUD_RATE);
    pc.printf("strating check\r\n");
    if(!snipe.lora_init()){
        cout << "SNIPE LoRa Initialization Fail!\r" << endl;
    }
    pc.printf("SNIPE LoRa StartUP\r\n");

    while(1){
        // cout << (snipe.lora_setFreq(LORA_CH_3)==true?"TRUE":"FALSE") << "\r" << endl;
        // wait_ms(100);
        // cout << snipe.lora_getFreq() << "\r" << endl;
        // wait_ms(100);
        // cout << snipe.lora_getTxp() << "\r" << endl;
        // wait_ms(100);
        // cout << (snipe.lora_setTxp(5)==true?"TRUE":"FALSE") << "\r" << endl; //Tx Power (dBm)
        // wait_ms(100);        
        // cout << snipe.lora_getSf() << "\r" << endl;
        // wait_ms(100);
        // cout << (snipe.lora_setSf(LORA_SF_12)==true?"TRUE":"FALSE") << "\r" << endl;
        // wait_ms(100);        
        // cout << snipe.lora_getRxtout() << "\r" << endl;
        // wait_ms(100);
        // cout << (snipe.lora_setRxtout(1000)==true?"TRUE":"FALSE") << "\r" << endl;
        // wait_ms(100);
        // cout << snipe.lora_getTxtout() << "\r" << endl;
        // wait_ms(100);
        // cout << (snipe.lora_setTxtout(1000)==true?"TRUE":"FALSE") << "\r" << endl;
        // wait_ms(100);
        // cout << (snipe.lora_setAESMode(LORA_AES_OFF)==true?"TRUE":"FALSE") << "\r" << endl;
        // wait_ms(100);        
        cout << (snipe.lora_setAppKey(lora_app_key)==true?"TRUE":"FALSE") << "\r" << endl;
        wait_ms(100);              
        cout << snipe.lora_getAppKey() << "\r" << endl;
        wait_ms(100);
        // cout << snipe.lora_getVersion() << "\r" << endl;
        // wait_ms(100);
    }    
}