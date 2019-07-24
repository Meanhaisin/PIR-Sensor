#include "ROM.h"

void writePipe(byte pipe[])
{
  for (uint8_t i = PIPE_OFFSITE; i < SN_WIDTH; i++)
  {
    EEPROM.update(i, pipe[i + 1]);
  }
}

void writeNO(uint8_t no,byte pipe[])
{
  EEPROM.update(NO_OFFSITE + no, pipe[0]);
}

void readPipe()
{
  for (uint8_t i = PIPE_OFFSITE; i < SN_WIDTH; i++)
  {
    send_pipe[i + 1] = EEPROM.read(i);
  }
  send_pipe[0] = EEPROM.read(NO_OFFSITE);
}
/*
void delPipe()
{
  EEPROM.update(NO_OFFSITE,NONE);
}
*/
