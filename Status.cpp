#include "Status.h"

volatile uint8_t current_STATUS = STATUS_STD;
volatile bool alarm = 0;

void DO_STATUS_std()
{
  if(keyDetect(SW) == LONG_PRESSED)
  {
     current_STATUS = STATUS_PAIR;
  }
  
  //IDLE_2min();
  Powerdown(7200000);
}

void DO_STATUS_msg()
{
  radioSend(alarm);
  current_STATUS = STATUS_STD;
}

void DO_STATUS_pair()
{
  radioPair(); 
}
