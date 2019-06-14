#include "radio.h"

RF24 RF(CE,CSN);

void radio_init()
{
  RF.begin();
  RF.setDataRate(RF24_250KBPS);
  RF.setPALevel(RF24_PA_HIGH);
  RF.setPayloadSize(LOAD_SIZE);
}

void radio_pair()
{
  RF.setPayloadSize(5);
  
}
