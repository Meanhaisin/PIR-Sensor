#include "key.h"

/* 按键扫描程序所处的状态
  初始状态为：按键按下（KEY_STATE_RELEASE）
*/
uint8_t keyState = KEY_STATE_RELEASE;

uint8_t keyDetect(uint8_t sw)
{
  static unsigned int duriation = 0;  // 用于在等待状态中计数

  switch (keyState)
  {
    case KEY_STATE_RELEASE:
      if (digitalRead(sw) == 0)    // 如果按键按下
      {
        keyState = KEY_STATE_SHORT_PRESSED;  // 转换至下一个状态
      }
      return NOT_PRESSED;    // 返回：按键未按下
      break;

    case KEY_STATE_SHORT_PRESSED:
      if (digitalRead(sw) == 0)
      {
        duriation++;

        if (duriation > LONG_PRESSED_TIME)   // 如果经过多次检测，按键仍然按下
        {
          duriation = 0;
          keyState = KEY_STATE_LONG_PRESSED;  // 转换至下一个状态
          return NOT_PRESSED;
        }
        return NOT_PRESSED;
      }
      else
      {
        duriation = 0;
        keyState = KEY_STATE_RELEASE;
        return SHORT_PRESSED;
      }
      break;

    case KEY_STATE_LONG_PRESSED:
      if (digitalRead(sw) == 1)      // 如果按键松开
      {
        keyState = KEY_STATE_RELEASE;  // 回到按键松开的状态
        return LONG_PRESSED;
      }
      else
      {
        return NOT_PRESSED;
      }
      break;
  }
}
