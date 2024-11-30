#ifndef __OLED_H
#define __OLED_H

void OLED_Init(void);
void OLED_Clear(void);

void OLED_ON(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_WR_Byte(unsigned dat,unsigned cmd);

//void OLED_ShowBMP(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);//显示一幅图片
//坐标设置

void OLED_Set_Pos(unsigned char x, unsigned char y);

//显示汉字
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void yuzhi(void);
void OLED_Fire(void);
#endif
