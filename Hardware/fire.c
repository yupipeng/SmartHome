#include "fire.h"
#include "stm32f10x.h"
#include "BEEP.h"
//#include "Ralay.h"
//extern u8 Tem;

void FIRE_CONFIG(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
 
		RCC_APB2PeriphClockCmd(GPIO_FIRE_CLK, ENABLE); 
 
		GPIO_InitStructure.GPIO_Pin = GPIO_FIRE_PIN;
	
		/*设置GPIO模式为浮空输入*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
 
		/*调用库函数，初始化GPIO*/
		GPIO_Init(GPIO_FIRE_PORT, &GPIO_InitStructure);			 	

        GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);

        EXTI_InitTypeDef EXTI_InitStructure;
        EXTI_InitStructure.EXTI_Line = EXTI_Line13;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
        EXTI_Init(&EXTI_InitStructure);

        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

        NVIC_InitTypeDef NVIC_InitStructure;
        NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        NVIC_Init(&NVIC_InitStructure);
}

uint8_t Sensor_GetValue(void)
{
	uint8_t Num = GPIO_ReadInputDataBit(GPIO_FIRE_PORT, GPIO_FIRE_PIN);
	return Num;
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line13) == SET)
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0)
		{
			BEEP_ON();
		}
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
//    	if (EXTI_GetITStatus(EXTI_Line10) == SET)
//	{
//		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
//		if (Tem < 20 || Tem >30)
//		{
//			relay_on();
//		}
//		EXTI_ClearITPendingBit(EXTI_Line10);
//	}
}
