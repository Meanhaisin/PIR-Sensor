#include "Arduino.h"
#include "SPI.h"
#include "nRF24L01.h"
#include "RF24.h"

#define CE 9
#define CSN 10

#define LOAD_SIZE 16

const byte pair_pipe[6] = "pairP";

void radio_init();
void radio_pair();
