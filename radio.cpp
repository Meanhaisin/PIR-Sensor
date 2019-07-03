#include "radio.h"

//extern bool ledchange;
byte send_pipe[5]; //发送管道,从EEPROM读取
uint8_t rfStatus = RF_STATUS_START_PAIR;
//int timerset = 0;
bool led_flagblink = 1;

RF24 RF(CE, CSN);

bool radioInit() //初始化
{
  bool ispair = 0;
  
  RF.begin();
  RF.setDataRate(RF24_250KBPS); //发射速率设定
  RF.setPALevel(RF24_PA_HIGH); //发射功率设定,测试后可适当调小以节能
  RF.setPayloadSize(PAY_LOAD_SIZE_STD); //发射负载大小(Byte)
  readPipe();
  delay(4);
  ispair = pairCheck();
  //blink_block(500, 3);
  if (ispair)
  {
    RF.openWritingPipe(send_pipe);
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

  if (flag)
  {
    msg = bat_voltage() * 2 + 1;
  }
  else
  {
    msg = bat_voltage() * 2;
  }

  RF.write(&msg, sizeof(msg));
}

void led_blink2()
{
  digitalWrite(LED,led_flagblink);
  //PORTD = ~(PORTD ^ B11101111);
  led_flagblink = !led_flagblink;
  //blink_block(500, 3);
  //timerset++;
}

void radioPair()
{
  //led_blink();
  //blink_block(500, 3);
  switch (rfStatus)
  {
    case RF_STATUS_START_PAIR:
      //blink_block(500, 3);
      RF.openReadingPipe(PAIR_READINGPIPE, pair_pipe);
      RF.startListening();
      rfStatus = RF_STATUS_PAIRING;
      //ledchange = 1;
      Timer1.initialize(INTERVAL);
      Timer1.attachInterrupt(led_blink2);
      //blink_block(500, 3);
      break;

    case RF_STATUS_PAIRING:
      if (RF.available())
      {
        RF.read(&send_pipe, sizeof(send_pipe));
        writePipe(send_pipe);
        writeNO(0, send_pipe);
        RF.stopListening();
        RF.closeReadingPipe(PAIR_READINGPIPE);
        blink_block(10,3);
        //rfStatus = RF_STATUS_STD;
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
      if (keyDetect(SW) == SHORT_PRESSED)
      {
        MsTimer2::stop();
        digitalWrite(LED, LOW);
        RF.stopListening();
        RF.closeReadingPipe(PAIR_READINGPIPE);
        rfStatus = RF_STATUS_START_PAIR;
        current_STATUS = STATUS_STD;
      }
  }
}

bool pairCheck()
{
  int check = 0;
  

  check = EEPROM.read(4);
  if (check == 0)
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
