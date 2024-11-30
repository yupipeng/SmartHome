#include "stm32f10x.h"   

void relay_init(void)//对继电器初始化，即对PB0口初始化
{
    
        GPIO_InitTypeDef     GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource10);

        EXTI_InitTypeDef EXTI_InitStructure;
        EXTI_InitStructure.EXTI_Line = EXTI_Line10;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
        EXTI_Init(&EXTI_InitStructure);

        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

        NVIC_InitTypeDef NVIC_InitStructure;
        NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        NVIC_Init(&NVIC_InitStructure);
//  GPIO_InitTypeDef     GPIO_InitStructure;
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
//	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}      



void relay_on(void)//PA10置1
{
  GPIO_SetBits(GPIOA,GPIO_Pin_10);
}
 
void relay_off(void)//PA10置0
{ 
  GPIO_ResetBits(GPIOA,GPIO_Pin_10);
}

void relay_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_10) == 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_10);
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_10);
	}
}
