#include "Status.h"

void DO_STATUS_init()
{
  system_init();

  
}

void DO_STATUS_std()
{
  if(digitalRead(PIR) == HIGH)
  {
    alarm = 1;
    
    current_STATUS = STATUS_msg;
  }
  else
  {
    if(!alarm)
    {
      alarm = 0;

      current_STATUS = STATUS_msg;
    }
  }
}

void DO_STATUS_msg()
{
  
}

void DO_STATUS_pair()
{

}
