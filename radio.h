#ifndef _radio_H
#define _radio_H

#include "Arduino.h"
#include "SPI.h"
#include "nRF24L01.h"
#include "RF24.h"

#define CE 9
#define CSN 10

#define LOAD_SIZE 16 //发射负载大小

const byte pair_pipe[6] = "pairP"; //配对默认管道
const byte pipe[5][6];

void radio_init();
bool radio_pair(); //配对函数

#endif
