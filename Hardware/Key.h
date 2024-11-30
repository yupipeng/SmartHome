#ifndef _KEY_H
#define _KEY_H

#include "sys.h"

//从PD8和PD9读取数据
#define key0 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#define key1 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)
#define key2 GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)
void key_init();
int key_scan();
//u8 Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
//u8 KEY_Scan(u8 mode);
//void Sys_Restart(void);
//u8 Check_Key_ON_OFF();
#endif
