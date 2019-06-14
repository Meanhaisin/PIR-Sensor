#include "radio.h"

RF24 RF(CE,CSN);

void radio_init()
{
  RF.begin();
  RF.setDataRate(RF24_250KBPS); //发射速率设定
  RF.setPALevel(RF24_PA_HIGH); //发射功率设定,测试后可适当调小以节能
  RF.setPayloadSize(LOAD_SIZE); //发射负载大小

  //待完善
}

bool radio_pair()
{
  //待完善,记得在配对完后发数据测试一下,不通过则失败
  
}
