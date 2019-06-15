#include "radio.h"

uint64_t send_pipe; //发送管道,从EEPROM读取
uint8_t rfStatus = RF_STATUS_STD;

RF24 RF(CE, CSN);

bool radioInit()
{
  
  RF.begin();
  RF.setDataRate(RF24_250KBPS); //发射速率设定
  RF.setPALevel(RF24_PA_HIGH); //发射功率设定,测试后可适当调小以节能
  RF.setPayloadSize(PAY_LOAD_SIZE_STD); //发射负载大小(Byte)
  if (pairCheck())
  {
    RF.openWritingPipe(send_pipe);
    return 1;
  }
  else
  {
    return 0;
  }
  
}

void radioSend(bool flag)
{
  uint8_t msg = 0;
  
  if (flag)
  {
    msg = bat_voltage() * 2 + 1;
  }
  else
  {
    msg = bat_voltage() * 2;
  }
  
  RF.write(&msg,sizeof(msg));
}

void radioPair()
{

  switch (rfStatus)
  {
    case RF_STATUS_START_PAIR:
      RF.openReadingPipe(PAIR_READINGPIPE, pair_pipe);
      RF.startListening();
      rfStatus = RF_STATUS_PAIRING;
      break;

    case RF_STATUS_PAIRING:
      if (RF.available())
      {
        RF.read(&send_pipe, sizeof(send_pipe));
        writePipe(send_pipe);
        RF.stopListening();
        RF.closeReadingPipe(PAIR_READINGPIPE);
        blink_block(10,3);
        rfStatus = RF_STATUS_STD;
        current_STATUS = STATUS_STD;
      }
      break;
  }

}

bool pairCheck()
{
  
}
