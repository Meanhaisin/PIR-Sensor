#include "Status.h"
//extern int timerset;
void setup()
{
  Serial.begin(115200);
  system_init();
}

void loop()
{
  /*
  if (sw_status == SHORT_PRESSED)
  {
    Serial.println("SHORT_PRESSED");
  }
  if (sw_status == LONG_PRESSED)
  {
    Serial.println("LONG_PRESSED");
  }
  */
  //Serial.println(alarm);

  switch (current_STATUS)
  {
    case STATUS_STD:
      DO_STATUS_std();
      break;

    case STATUS_MSG:
      DO_STATUS_msg();
      break;

    case STATUS_PAIR:
      DO_STATUS_pair();
      break;
  }
  
  sw_press();
}
