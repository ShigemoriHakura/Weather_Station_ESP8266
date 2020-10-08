#include "EPD_drive_gpio.h"
#include <SPI.h>

/*********************************************

*********************************************/
void SPI_Write(unsigned char value)
{
  SPI.transfer(value);

  EPD_CLK_0;
  //delayMicroseconds(1);
  for (byte i = 0; i < 8; i++)
  {
    //高位在前发送方式    根据升级器件特性定
    if ((value & 0x80) == 0x80) EPD_DIN_1;
    else EPD_DIN_0;
    //delayMicroseconds(1);      //等待数据稳定  根据实际时钟调整
    EPD_CLK_1;//上升沿发送数据
    //delayMicroseconds(1);//CLK高电平保持一段时间 这个可以不需要 根据具体的spi时钟来确定
    EPD_CLK_0;; //把时钟拉低实现为下一次上升沿发送数据做准备
    value = value << 1; //发送数据的位向前移动一位
  }

}

/*********************************************

*********************************************/
void driver_delay_xms(unsigned long xms)
{
  delay(xms);
}
