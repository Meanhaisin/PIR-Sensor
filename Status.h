#ifndef _Status_H
#define _Status_H

#include "Arduino.h"
#include "system.h" //设备外设，难分类的丢这
#include "radio.h" //无线相关代码
#include "key.h"  //按键代码

extern uint8_t keyState; //按键状态
extern bool readKey(int sw);
extern uint8_t keyDective(int sw); //按键读取函数
extern void led_blink(); //led控制函数


#define STATUS_std 0
#define STATUS_msg 1
#define STATUS_pair 2

extern uint8_t current_STATUS; //设备状态
extern bool alarm; //报警知识

void DO_STATUS_std();
void DO_STATUS_msg();
void DO_STATUS_pair();

#endif
