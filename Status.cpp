#include "Status.h"

uint8_t current_STATUS = STATUS_STD;
bool alarm = 0;

void DO_STATUS_std()
{
  if(digitalRead(PIR) == HIGH)
  {
    alarm = 1;
    
    current_STATUS = STATUS_MSG;
  }
  else
  {
    if(!alarm)
    {
      alarm = 0;

      current_STATUS = STATUS_MSG;
    }
  }

  if(keyDetect(SW) == LONG_PRESSED)
  {
     current_STATUS = STATUS_PAIR;
  }
  
}

void DO_STATUS_msg()
{
  //待完善(需先完善radio)
}

void DO_STATUS_pair()
{
  led_blink();
  radioPair();
  
}
