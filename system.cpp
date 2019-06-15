#include "system.h"

bool system_init() //初始化端口、RF模块、检测设备是否完成配对（未配对进入STATUS_pair,否则进入STATUS_std)
{
  pinMode(PIR, INPUT);
  pinMode(IRQ, INPUT);
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH); //使用内置上拉电阻
  pinMode(LED, OUTPUT);

  if (!radioInit())
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

void led_blink()
{
<<<<<<< HEAD
  if (ledchange == 1) //开始配对
  {
    static uint8_t duriation;
    if(ledflag == 1 && duriation < 5000) //led high
    {
      digitalWrite(LED, HIGH);
      duriation++;
    }
    else if(ledflag == 0 && duriation < 5000) //led low
    {
      digitalWrite(LED, LOW);
      duriation++;
    }
    else  //time change
    {
      duriation = 0;
      ledflag = !ledflag;
    }
  }
=======
  if()
>>>>>>> c1566da90f1f54b94afbc36ae085fa3389f8bdb7
}

void blink_block(uint8_t t, uint8_t count)
{
  
  for (uint8_t i = 0; i < t; i++)
  {
    digitalWrite(LED, HIGH);
    delay(t);
    digitalWrite(LED, LOW);
    delay(t);
  }

}

uint8_t bat_voltage()
{

   return analogRead(BAT) / 8;
   
}
