#ifndef __SERIAL_H
#define __SERIAL_H

#include <stdio.h>


#define USART_DEBUG		USART1		//调试打印所使用的串口组

void uart1_Init(u32 bound);
void uart2_Init(u32 bound);
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str, unsigned short len);
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);
void USART1_IRQHandler(void);

#endif

