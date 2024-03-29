#ifndef _system_H
#define _system_H

#include <Arduino.h>
#include "radio.h"

#define PIR 2
#define IRQ 3
#define SW 4
#define LED 5
#define BAT A0

#define POWERDOWN_T 300000 //进入低功耗模式时间（ms）

extern volatile uint8_t current_STATUS;
extern volatile bool alarm;
extern uint8_t keyStatus;
extern uint8_t sw_status;

extern bool radioInit();
extern uint8_t keyDetect(uint8_t sw);

void system_init();
void PIR_isr();
//void led_blink();
void led_blink2();
void blink_block(uint8_t t, uint8_t count);
void sw_press();
uint8_t bat_voltage();
uint8_t BatPercent();
void PowerSave(unsigned long m, uint8_t p); //ms,%

#endif
