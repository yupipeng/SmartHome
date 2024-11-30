#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void Beep_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
}


void BEEP_ON(void){
     GPIO_ResetBits(GPIOB, GPIO_Pin_12);

}
void BEEP_OFF(void){
    GPIO_SetBits(GPIOB, GPIO_Pin_12);

}
void BEEP_Turn(void){
    if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == 0)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
	}
}

void worn(void){

        BEEP_ON();
        DelayXms(100);
        BEEP_OFF();
        DelayXms(100);
        BEEP_ON();
        DelayXms(100);
        BEEP_OFF();
        DelayXms(100);
        BEEP_ON();
        DelayXms(100);
        BEEP_OFF();
        DelayXms(100);
}


