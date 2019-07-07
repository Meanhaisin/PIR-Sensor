#include "radio.h"

byte send_pipe[5]; //发送管道,从EEPROM读取
uint8_t rfStatus = RF_STATUS_START_PAIR;

RF24 RF(CE, CSN);

bool radioInit() //初始化
{
  RF.begin();
  RF.setDataRate(RF24_250KBPS); //发射速率设定
  RF.setPALevel(RF24_PA_HIGH); //发射功率设定,测试后可适当调小以节能
  RF.setPayloadSize(PAY_LOAD_SIZE_STD); //发射负载大小(Byte)
  readPipe();
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
  uint8_t i = 0;
  if (flag)
  {
    msg = bat_voltage() * 2 + 1;
  }
  else
  {
    msg = bat_voltage() * 2;
  }
  while (!RF.write(&msg, sizeof(msg)) & (i < 3))
  {
    i ++;
  }
}

void radioPair()
{
  switch (rfStatus)
  {
    case RF_STATUS_START_PAIR:
      RF.setPayloadSize(PAY_LOAD_SIZE_PAIR);
      RF.openReadingPipe(PAIR_READINGPIPE, pair_pipe);
      RF.startListening();
      
      rfStatus = RF_STATUS_PAIRING;
      
      Timer1.initialize(INTERVAL);
      Timer1.attachInterrupt(led_blink2);
      
      if (sw_status == SHORT_PRESSED)
      {
        Timer1.stop();
        digitalWrite(LED, LOW);

        RF.stopListening();
        RF.closeReadingPipe(PAIR_READINGPIPE);
        RF.setPayloadSize(PAY_LOAD_SIZE_STD);
        RF.openWritingPipe(send_pipe);

        rfStatus = RF_STATUS_START_PAIR;
        current_STATUS = STATUS_STD;
      }
      break;

    case RF_STATUS_PAIRING:
      if (RF.available())
      {
        RF.read(&send_pipe, sizeof(send_pipe));
        writePipe(send_pipe);
        writeNO(0, send_pipe);
        delay(500);
        
        RF.stopListening();
        RF.closeReadingPipe(PAIR_READINGPIPE);
        RF.setPayloadSize(PAY_LOAD_SIZE_STD);
        RF.openWritingPipe(send_pipe);
        
        rfStatus = RF_STATUS_START_PAIR;
        current_STATUS = STATUS_STD;
        
        Timer1.stop();
        digitalWrite(LED, LOW);
        
        blink_block(100, 3);
      }

      if (sw_status == SHORT_PRESSED)
      {
        Timer1.stop();
        digitalWrite(LED, LOW);

        RF.stopListening();
        RF.closeReadingPipe(PAIR_READINGPIPE);
        RF.setPayloadSize(PAY_LOAD_SIZE_STD);
        RF.openWritingPipe(send_pipe);

        rfStatus = RF_STATUS_START_PAIR;
        current_STATUS = STATUS_STD;
      }
  }
}

bool pairCheck()
{
  if (EEPROM.read(NO_OFFSITE) == NONE)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
