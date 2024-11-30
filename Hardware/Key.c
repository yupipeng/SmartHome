#include "key.h"
#include "stm32f10x.h"
#include "delay.h"
#include "Usart.h"
#include "OLED.h"
void key_init(){//初始化按键
	
	GPIO_InitTypeDef GPIO_InitStruture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);//打开PB 时钟
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_InitStruture.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //设置端口
    GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruture);//初始化POID

    GPIO_InitTypeDef GPIO_InitStruture1;
	GPIO_InitStruture1.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_InitStruture1.GPIO_Pin = GPIO_Pin_7; //设置端口
    GPIO_InitStruture1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruture1);//初始化POID
}

int key_scan()
{
	static u8 flag = 1;//之前没有按键按下
	if(flag==1&&(key0==0||key1==0||key2==0))//之前没有按键按下且当前有key0或者key1按下时
	{
		flag = 0;//按键key0或者key1按下，flag置0（即为有按键按下）
		 DelayXms(10);//延时按键消抖
		if(key0==0){
			return 1;
		}else if(key1==0){
			return 2;
		}
        else if(key2==0){
			return 3;
		}
	}else if(key0==1&&key1==1&&key2==1) flag = 1;//没有按键按下时，flag置1
	
	return 0;//无按键按下
}

///*********************************************************************************
// * @Function	:  检测是否有按键按下
// * @Input		:  GPIOx：x 可以是 A，B，C，D或者 E
// *						:  GPIO_Pin：待读取的端口位
// * @Output		:  None
// * @Return		:  KEY_OFF(没按下按键)、KEY_ON（按下按键）
// * @Others		:  None
// * @Date			:  2022-07-23
// **********************************************************************************/
//u8 Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
//{
//	/*检测是否有按键按下 */
//	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 1)
//	{
//		/*等待按键释放 */
//		while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 1)
//			;
//		return 1;
//	}
//	else
//		return 0;
//}
///*********************************************************************************
// * @Function	:  按键处理函数
// * @Input		:  Gmode:0,不支持连续按;1,支持连续按;
// * @Output		:  None
// * @Return		:  0，没有任何按键按下
// *							 1，KEY1按下
// *						   2，KEY2按下
// *							 3，KEY3按下
// * @Others		:  注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!
// * @Date			:  2022-07-23
// **********************************************************************************/
//u8 KEY_Scan(u8 mode)
//{
//	static u8 key_up = 1; // 按键按松开标志
//	if (mode)
//		key_up = 1; // 支持连按
//	if (key_up && (key0 == 1 || key1 == 1 || key2 == 1 ))
//	{

//		key_up = 0;
//		if (key0 == 1)
//			return 1;
//		else if (key1 == 1)
//			return 2;
//		else if (key2 == 1)
//			return 3;
//	
//	}
//	else if (key0 == 0 && key1 == 0 && key2 == 0 )
//		key_up = 1;
//	return 0; // 无按键按下
//}
// 
///*********************************************************************************
// * @Function	:  STM32程序软件复位
// * @Input		:  None
// *						:  None
// * @Output		:  None
// * @Return		:  None
// * @Others		:  None
// * @Date			:  2022-08-23
// **********************************************************************************/
//void Sys_Restart(void)
//{
//	__set_FAULTMASK(1);
//	NVIC_SystemReset();
//}
//// 检测按键是否按下
//static u16 time_4;
//static u8 key_old = 0;
//u8 Check_Key_ON_OFF()
//{
//	u8 key;
//	key = KEY_Scan(1);
//	// 与上一次的键值比较 如果不相等，表明有键值的变化，开始计时
//	if (key != 0 && time_4 == 0)
//	{
//		key_old = key;
//		time_4 = 1;
//	}
//	if (key != 0 && time_4 >= 1 && time_4 <= 100) // 100ms
//	{
//		time_4++; // 时间记录器
//	}
//	if (key == 0 && time_4 > 0 && time_4 < 30) // 短按
//	{
//		switch (key_old)
//		{  
//		case 1:
//			
//			break;
//		case 2:  
//			
//			break;
//		case 3:
//            
//			break;

//		}
//		time_4 = 0;
//	}
//	else if (key == 0 && time_4 >= 30) // 长按
//	{
//		switch (key_old)
//		{
//		case 1:
////			printf("Key1_Long\n");
//			break;
//		case 2:
////			printf("Key2_Long\n");
//			break;
//		case 3:
//            yuzhi();
//			break;

//		}
//		time_4 = 0;
//	}
// 
//	return 1;

//}
///*********************************************END OF FILE**********************/



