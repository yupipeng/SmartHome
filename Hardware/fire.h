#ifndef __FIRE_H
#define	__FIRE_H
#include "stm32f10x.h"
 
#define GPIO_FIRE_CLK  RCC_APB2Periph_GPIOB//时钟
#define GPIO_FIRE_PORT GPIOB//火焰传感器与开发板数据连接的引脚的寄存器
#define GPIO_FIRE_PIN  GPIO_Pin_13 //火焰传感器与开发板数据连接的引脚
 
void FIRE_CONFIG(void);
uint8_t Sensor_GetValue();

#endif /* __FIRE_H */

