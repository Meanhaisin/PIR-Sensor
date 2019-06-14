#include "system.h"
#include "radio.h"

void system_init()
{
  pinMode(PIR,INPUT);
  pinMode(IRQ,INPUT);
  pinMode(SW,INPUT);
  digitalWrite(SW,HIGH); //enable pullup
  pinMode(LED,OUTPUT);

  radio_init();
}
