#ifndef _EPD_DRIVE_GPIO_H_
#define _EPD_DRIVE_GPIO_H_
#include <SPI.h>

/********************------------------------------------------------------------

  Hardware interface

  ------------------------------------------------------------------------------*/
//GPIO config

#define CS 15
#define EPD_CS_0	digitalWrite(CS,LOW)
#define EPD_CS_1	digitalWrite(CS,HIGH)
#define isEPD_CS  digitalRead(CS)

#define RST 2
#define EPD_RST_0	digitalWrite(RST,LOW)
#define EPD_RST_1	digitalWrite(RST,HIGH)
#define isEPD_RST digitalRead(RST)

#define DC 0
#define EPD_DC_0	digitalWrite (DC,LOW)
#define EPD_DC_1	digitalWrite (DC,HIGH)

#define BUSY 4
#define isEPD_BUSY digitalRead(BUSY)
#define EPD_BUSY_LEVEL 0

#define CLK 14
#define EPD_CLK_0  digitalWrite (CLK,LOW)
#define EPD_CLK_1  digitalWrite (CLK,HIGH)

#define DIN 13
#define EPD_DIN_0  digitalWrite (DIN,LOW)
#define EPD_DIN_1  digitalWrite (DIN,HIGH)

extern void SPI_Write(unsigned char value);
extern void driver_delay_xms(unsigned long xms);


#endif
