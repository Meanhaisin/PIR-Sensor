#include "system.h"

void system_init() //初始化端口、RF模块、检测设备是否完成配对（未配对进入STATUS_pair,否则进入STATUS_std)
{
  pinMode(PIR,INPUT);
  pinMode(IRQ,INPUT);
  pinMode(SW,INPUT);
  digitalWrite(SW,HIGH); //使用内置上拉电阻
  pinMode(LED,OUTPUT);

  radio_init();

  //待完善(需先完善EEPROM)
}

void led_blink()
{
  if()
}
