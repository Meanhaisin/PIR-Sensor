#include "radio.h"

//extern bool ledchange;
byte send_pipe[5]; //发送管道,从EEPROM读取
uint8_t rfStatus = RF_STATUS_START_PAIR;
//int timerset = 0;

RF24 RF(CE, CSN);

bool radioInit() //初始化
{
  RF.begin();
  RF.setDataRate(RF24_250KBPS); //发射速率设定
  RF.setPALevel(RF24_PA_HIGH); //发射功率设定,测试后可适当调小以节能
  RF.setPayloadSize(PAY_LOAD_SIZE_STD); //发射负载大小(Byte)
  readPipe();
  /*
    for (int i = 0; i < 5; i++)
    {
    Serial.write(send_pipe[i]);
    }
  */
  //blink_block(500, 3);
  if (pairCheck())
  {
    RF.openWritingPipe(send_pipe);
    RF.openReadingPipe(0, send_pipe);
    RF.startListening();
    //blink_block(500, 3);
    return 1;
  }
  else
  {
    //blink_block(500, 3);
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
  Serial.println("Sending.................................................................................................................");
  while (!RF.write(&msg, sizeof(msg)) & (i < 5))
  {
    i ++;
    Serial.println("failed!!!!!!!!!!!!!!!!!!!!");
  }
}

void radioPair()
{
  //led_blink();
  //blink_block(500, 3);
  switch (rfStatus)
  {
    case RF_STATUS_START_PAIR:
      //blink_block(500, 3);
      RF.setPayloadSize(PAY_LOAD_SIZE_PAIR);
      RF.openReadingPipe(PAIR_READINGPIPE, pair_pipe);
      RF.startListening();
      rfStatus = RF_STATUS_PAIRING;
      //ledchange = 1;
      Timer1.initialize(INTERVAL);
      Timer1.attachInterrupt(led_blink2);
      //blink_block(500, 3);
      if (sw_status == SHORT_PRESSED)
      {
        //Serial.println(1);
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
        /*
          for (int i = 0; i < 5; i++)
          {
          Serial.write(send_pipe[i]);
          }
        */
        Timer1.stop();
        digitalWrite(LED, LOW);
        blink_block(100, 3);
      }

      if (sw_status == SHORT_PRESSED)
      {
        //Serial.println(1);
        Timer1.stop();
        digitalWrite(LED, LOW);

        RF.stopListening();
        RF.closeReadingPipe(PAIR_READINGPIPE);
        RF.setPayloadSize(PAY_LOAD_SIZE_STD);
        RF.openWritingPipe(send_pipe);

        rfStatus = RF_STATUS_START_PAIR;
        current_STATUS = STATUS_STD;
      }
      /*
        case RF_STATUS_STD:
        current_STATUS = STATUS_STD;
        //ledchange = 0;
        //Timer1.stop();
        digitalWrite(LED, LOW);
        blink_block(10, 3);
        }
      */
  }
}

bool pairCheck()
{
  if (EEPROM.read(NO_OFFSITE) == NONE)
  {
    return 0;
    //blink_block(500, 3);
  }
  else
  {
    return 1;
    //blink_block(500, 3);
  }
}
