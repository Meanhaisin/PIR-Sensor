#ifndef _ROM_H
#define _ROM_H


#include "Arduino.h"
#include "EEPROM.h"

#define PIPE_OFFSITE 0
#define NO_OFFSITE 5
#define SN_OFFSITE 1000

void writePipe(uint64_t pipe); //写入管道,同时设置标志位
uint64_t readPipe();
void delPipe(); //删除管道(只需清除标志位)

#endif
