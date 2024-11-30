#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>


#define USART_DEBUG		USART1		//���Դ�ӡ��ʹ�õĴ�����

void uart1_Init(u32 bound);
void uart2_Init(u32 bound);
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);
void USART1_IRQHandler(void);

#endif

