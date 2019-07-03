#ifndef _system_H
#define _system_H

#include <Arduino.h>
#include <LowPower.h>
#include "radio.h"

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
#define LED_DELAY_SLOW 5000 //闪烁间隔
 
extern volatile uint8_t current_STATUS;
extern volatile bool alarm;
extern uint8_t keyStatus;

bool system_init();
void PIR_isr();
//void led_blink();
void blink_block(uint8_t t, uint8_t count);
uint8_t bat_voltage();
void IDLE_2min();
void Powerdown(unsigned long m); //ms

#endif
