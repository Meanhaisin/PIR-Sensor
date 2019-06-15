#ifndef _ROM_H
#define _ROM_H

<<<<<<< HEAD
#include "EEPROM.h"

=======
#include "Arduino.h"
#include "EEPROM.h"

void writePipe(uint64_t pipe); //写入管道,同时设置标志位
uint64_t readPipe();
void delPipe(); //删除管道(只需清除标志位)
>>>>>>> c5a563c502a42b052dd8f4e119cf34f1314aa7eb

#endif
