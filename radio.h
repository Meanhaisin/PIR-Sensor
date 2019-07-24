#ifndef _radio_H
#define _radio_H

#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TimerOne.h>
#include "system.h"
#include "ROM.h"
#include "Status.h"

#define CE 9
#define CSN 10

#define RF_STATUS_START_PAIR 0
#define RF_STATUS_PAIRING 1

#define PAY_LOAD_SIZE_STD 1 //标准发射负载大小
#define PAY_LOAD_SIZE_PAIR 5 //配对发射负载大小
#define PAIR_READINGPIPE 0 //配对管道

#define INTERVAL 500000

extern volatile uint8_t current_STATUS;

extern void writePipe(const byte pipe[]); //写入管道
extern void writeNO(uint8_t no ,const byte pipe[]); //设置标志位(管道第一位)
extern void readPipe();

const byte pair_pipe[5] = {'P', 'p', 'a','i' ,'r'}; //配对默认管道

bool radioInit();
void radioSend(bool flag); //发送
void radioPair(); //配对函数
bool pairCheck(); //配对检查(检查标志位)

#endif
