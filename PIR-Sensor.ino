#include "Status.h"

void setup()
{
  system_init();
}

void loop()
{
  
  switch (current_STATUS)
  {
    case STATUS_std:
      DO_STATUS_std();
      break;

    case STATUS_msg:
      DO_STATUS_msg();
      break;

    case STATUS_pair:
      DO_STATUS_pair();
      break;
  }
  
}
