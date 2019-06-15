#ifndef _system_H
#define _system_H

#include "Arduino.h"
#include "radio.h"
#include "EEPROM.h" //待实现

#define PIR 2
#define IRQ 3
#define SW 4
#define LED 5
#define BAT A0

/*
 * LED的三种状态以及闪烁间隔
 */
#define LED_STATUS_BRIGHT 0
#define LED_STATUS_DARK 1
#define LED_CHANGE_DELAY_FAST 40  //闪烁间隔
#define LED_CHANGE_DELAY_SLOW 100
 
extern uint8_t current_STATUS;
extern bool alarm;
extern uint8_t keyStatus;

bool system_init();
void led_blink();
void blink_block(uint8_t t, uint8_t count);
uint8_t bat_voltage();

#endif
