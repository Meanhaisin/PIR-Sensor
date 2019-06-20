#include "ROM.h"

void writePipe(byte pipe[])
{
  for (uint8_t i = PIPE_OFFSITE; i < SN_WIDTH; i++)
  {
    EEPROM.update(i, pipe[SN_WIDTH - i]);
  }
}

void writeNO(uint8_t no,byte pipe[])
{
  EEPROM.update(PIPE_WIDTH + no, pipe[0]);
}

void readPipe()
{
  for (uint8_t i = PIPE_OFFSITE; i < PIPE_WIDTH; i++)
  {
    send_pipe[PIPE_WIDTH - i] = EEPROM.read(i);
  }
}

void delPipe()
{
  EEPROM.update(NO_OFFSITE,0);
}
