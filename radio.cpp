#include "radio.h"

//extern bool ledchange;
byte send_pipe[5]; //发送管道,从EEPROM读取
uint8_t rfStatus = RF_STATUS_STD;

RF24 RF(CE, CSN);

bool radioInit() //初始化
{
  RF.begin();
  RF.setDataRate(RF24_250KBPS); //发射速率设定
  RF.setPALevel(RF24_PA_HIGH); //发射功率设定,测试后可适当调小以节能
  RF.setPayloadSize(PAY_LOAD_SIZE_STD); //发射负载大小(Byte)
  readPipe();
  delay(4);
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

void led_blink2()
{
  static boolean output = HIGH;
  digitalWrite(LED, output);
  output = !output;
}

void radioPair()
{
  //led_blink();
  MsTimer2::set(1000, led_blink2);

  switch (rfStatus)
  {
    case RF_STATUS_START_PAIR:
      RF.openReadingPipe(PAIR_READINGPIPE, pair_pipe);
      RF.startListening();
      rfStatus = RF_STATUS_PAIRING;
      //ledchange = 1;
      MsTimer2::start();
      break;

    case RF_STATUS_PAIRING:
      if (RF.available())
      {
        RF.read(&send_pipe, sizeof(send_pipe));
        writePipe(send_pipe);
        writeNO(0,send_pipe);
        RF.stopListening();
        RF.closeReadingPipe(PAIR_READINGPIPE);
        blink_block(10,3);
        rfStatus = RF_STATUS_STD;
        current_STATUS = STATUS_STD;
      }
      else
      {
        //ledchange = 0;
        MsTimer2::stop();
        digitalWrite(LED, LOW);
      }
      break;
  }

}

bool pairCheck()
{
  
  int check = 0;
  
  check = EEPROM.read(5);
  if (check == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
  
}
