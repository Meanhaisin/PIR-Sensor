#include "Status.h"

uint8_t current_STATUS = STATUS_STD;
bool alarm = 0;

void DO_STATUS_std()
{
  if(digitalRead(PIR) == HIGH && alarm == 0)
  {
    alarm = 1;
    
    current_STATUS = STATUS_MSG;
  }
  else
  {
    if(alarm)
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

  radioSend(alarm);
  current_STATUS = STATUS_STD;
    
}

void DO_STATUS_pair()
{
  
  radioPair();

  if(keyDetect(SW) == SHORT_PRESSED)
  {
     current_STATUS = STATUS_STD;
  }
  
}
