#ifndef __FIRE_H
#define	__FIRE_H
#include "stm32f10x.h"
 
#define GPIO_FIRE_CLK  RCC_APB2Periph_GPIOB//ʱ��
#define GPIO_FIRE_PORT GPIOB//���洫�����뿪�����������ӵ����ŵļĴ���
#define GPIO_FIRE_PIN  GPIO_Pin_13 //���洫�����뿪�����������ӵ�����
 
void FIRE_CONFIG(void);
uint8_t Sensor_GetValue();

#endif /* __FIRE_H */

