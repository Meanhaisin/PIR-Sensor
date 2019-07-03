#include "system.h"

//bool ledchange = 1; //判断是否进入blink
//bool ledflag = 0; //实现blink

bool system_init() //初始化端口、RF模块、检测设备是否完成配对（未配对进入STATUS_pair,否则进入STATUS_std)
{
  pinMode(PIR, INPUT);
  pinMode(IRQ, INPUT);
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH); //使用内置上拉电阻
  pinMode(LED, OUTPUT);
  //blink_block(500, 3);

  if (!radioInit())
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
/*
void led_blink() //配对时非阻塞blink
{
  static uint8_t duriation1;

  if (ledchange == 1) //开始配对
  {
    if(ledflag == 1 && duriation1 < LED_DELAY_SLOW) //led high
    {
      digitalWrite(LED, HIGH);
      duriation1++;
    }
    else if(ledflag == 0 && duriation1 < LED_DELAY_SLOW) //led low
    {
      digitalWrite(LED, LOW);
      duriation1++;
    }
    else  //time change
    {
      duriation1 = 0;
      ledflag = !ledflag;
    }
  }
  else  //防止led常亮，并修正blink
  {
    digitalWrite(LED, LOW);
    duriation1 = 0;
    ledflag = 1;
  }

}
*/
void blink_block(uint8_t t, uint8_t count) //阻塞blink
{
  
  for (uint8_t i = 0; i < count; i++)
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



  
