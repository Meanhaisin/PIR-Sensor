#ifndef _Status_H
#define _Status_H

#include <Arduino.h>
#include "system.h" //设备外设，难分类的丢这
#include "radio.h" //无线相关代码
#include "key.h"  //按键代码

#define STATUS_STD 0
#define STATUS_MSG 1
#define STATUS_PAIR 2

extern uint8_t keyState; //按键状态
extern uint8_t rfStatus; //无线状态

extern void radioSend(bool flag); //发送
extern void radioPair(); 
extern void PowerSave(unsigned long m, uint8_t p); //ms,%

void DO_STATUS_std();
void DO_STATUS_msg();
void DO_STATUS_pair();

#endif
