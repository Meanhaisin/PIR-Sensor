#include "Arduino.h"
#include "system.h"
#include "key.h"


#define STATUS_init 0
#define STATUS_std 1
#define STATUS_msg 2
#define STATUS_pair 3

uint8_t current_STATUS = STATUS_init;

extern bool alarm;
extern uint8_t keyState;

void DO_STATUS_init();
void DO_STATUS_std();
void DO_STATUS_msg();
void DO_STATUS_pair();
