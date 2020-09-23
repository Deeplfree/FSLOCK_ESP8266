#ifndef __OLED_H
#define __OLED_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "esp_log.h"

#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/gpio.h"

//GPIO_Pin_12
//GPIO_Pin_13
#define GPIO_I2C_SCL_NUM GPIO_NUM_12
#define GPIO_I2C_SDA_NUM GPIO_NUM_13

//GPIO_ResetBits
//GPIO_SetBits

//-----------------OLED端口定义---------------- 

#define OLED_SCLK_Clr() gpio_set_level(GPIO_I2C_SCL_NUM, 0)//SCL
#define OLED_SCLK_Set() gpio_set_level(GPIO_I2C_SCL_NUM, 1)

#define OLED_SDIN_Clr() gpio_set_level(GPIO_I2C_SDA_NUM, 0)//DIN
#define OLED_SDIN_Set() gpio_set_level(GPIO_I2C_SDA_NUM, 1)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

#define u8 unsigned char
#define u16 const unsigned char
#define u32 unsigned int

void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(u8 dat);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y);
void OLED_ClearPoint(u8 x,u8 y);
void OLED_ClearRectangularArea(u8 x1, u8 y1, u8 x2, u8 y2);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
unsigned char * HEX_ToChar(uint8_t *hex, uint16_t len);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);
void OLED_ScrollDisplay(u8 num,u8 space);
void OLED_WR_BP(u8 x,u8 y);
void OLED_ShowPicture(u8 x1,u8 y1,u8 x2,u8 y2,u8 p[]);
void OLED_ShowBilibili();
void OLED_ShowBilibili2();
void OLED_Showok1();
void OLED_Showno1();
void OLED_Showxiaodianshi1();
void OLED_Showblack();
void OLED_Init(void);

#endif  
