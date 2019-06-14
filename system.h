#include "Arduino.h"
#include "SPI.h"
#include "nRF24L01.h"
#include "RF24.h"
//#include "EEPROM.h"

#define PIR 2
#define IRQ 3
#define SW 4
#define LED 5

#define CE 9
#define CSN 10

#define LOAD_SIZE 16

const byte pair_pipe[6] = "pairP";

void system_init();
