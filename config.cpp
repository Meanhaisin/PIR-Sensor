#include "config.h"

void system_init()
{
  pinMode(PIR,INPUT);
  pinMode(IRQ,INPUT);
  pinMode(SW,INPUT);
  digitalWrite(SW,HIGH); //enable pullup
  pinMode(LED,OUTPUT);

  RF.begin();
  RF.setDataRate(RF24_250KBPS);
  RF.setPALevel(RF24_PA_HIGH);
  RF.setPayloadSize(LOAD_SIZE);``
  
}
