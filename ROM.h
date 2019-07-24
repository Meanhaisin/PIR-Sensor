#ifndef _ROM_H
#define _ROM_H

#include <Arduino.h>
#include <EEPROM.h>
#include "radio.h"

#define PIPE_WIDTH 5
#define PIPE_OFFSITE 0
#define NO_OFFSITE 4
#define PIPE_NUM_MAX 5 
#define SN_WIDTH 4
#define SN_OFFSITE 1020
#define NONE 0xFF

extern byte send_pipe[5];

void writePipe(byte pipe[]); //写入管道
void writeNO(uint8_t no,byte pipe[]); //设置标志位(管道第一位)
void readPipe();
//void delPipe(); //删除管道(只需清除标志位)

#endif
