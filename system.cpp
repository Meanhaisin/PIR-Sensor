#include "system.h"

uint8_t sw_status = NOT_PRESSED;

void system_init() //初始化端口、RF模块、检测设备是否完成配对（未配对进入STATUS_pair,否则进入STATUS_std)
{
  pinMode(PIR, INPUT);
  pinMode(IRQ, INPUT);
  pinMode(SW, INPUT);
  digitalWrite(SW, HIGH); //使用内置上拉电阻
  pinMode(LED, OUTPUT);

  attachInterrupt(PIR - 2, PIR_isr, CHANGE);

  blink_block(1000,3);

  if (radioInit())
  {
    current_STATUS = STATUS_STD;
  }
  else
  {
    current_STATUS = STATUS_PAIR;
    rfStatus = RF_STATUS_START_PAIR;
  }
}

void PIR_isr()
{
  if (digitalRead(PIR) == HIGH && alarm == 0)
  {
    alarm = 1;

    current_STATUS = STATUS_MSG;
  }
  else if (digitalRead(PIR) == LOW && alarm == 1)
  {
    alarm = 0;

    current_STATUS = STATUS_MSG;
  }
}

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

void led_blink2()
{
  static bool led_flagblink = 1;
  digitalWrite(LED, led_flagblink);
  //PORTD = ~(PORTD ^ B11101111);
  led_flagblink = !led_flagblink;
}

void sw_press()
{
  sw_status = keyDetect(SW);
}

uint8_t bat_voltage()
{
  return analogRead(BAT) / 8;
}

uint8_t BatPercent()
{
  return map(analogRead(BAT), 327, 615, 0, 100); //1V6-3V
}

void IDLE_2min()
{
  for (uint8_t i = 0; i < 15; i++)
  {
    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
  }
}

void Powerdown(unsigned long m,uint8_t p)
{
  if (millis() > m or BatPercent() < p)
  {
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
  }
}
