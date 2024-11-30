#include "key.h"
#include "stm32f10x.h"
#include "delay.h"
#include "Usart.h"
#include "OLED.h"
void key_init(){//��ʼ������
	
	GPIO_InitTypeDef GPIO_InitStruture;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);//��PB ʱ��
	GPIO_InitStruture.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_InitStruture.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //���ö˿�
    GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruture);//��ʼ��POID

    GPIO_InitTypeDef GPIO_InitStruture1;
	GPIO_InitStruture1.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_InitStruture1.GPIO_Pin = GPIO_Pin_7; //���ö˿�
    GPIO_InitStruture1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruture1);//��ʼ��POID
}

int key_scan()
{
	static u8 flag = 1;//֮ǰû�а�������
	if(flag==1&&(key0==0||key1==0||key2==0))//֮ǰû�а��������ҵ�ǰ��key0����key1����ʱ
	{
		flag = 0;//����key0����key1���£�flag��0����Ϊ�а������£�
		 DelayXms(10);//��ʱ��������
		if(key0==0){
			return 1;
		}else if(key1==0){
			return 2;
		}
        else if(key2==0){
			return 3;
		}
	}else if(key0==1&&key1==1&&key2==1) flag = 1;//û�а�������ʱ��flag��1
	
	return 0;//�ް�������
}

///*********************************************************************************
// * @Function	:  ����Ƿ��а�������
// * @Input		:  GPIOx��x ������ A��B��C��D���� E
// *						:  GPIO_Pin������ȡ�Ķ˿�λ
// * @Output		:  None
// * @Return		:  KEY_OFF(û���°���)��KEY_ON�����°�����
// * @Others		:  None
// * @Date			:  2022-07-23
// **********************************************************************************/
//u8 Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
//{
//	/*����Ƿ��а������� */
//	if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 1)
//	{
//		/*�ȴ������ͷ� */
//		while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == 1)
//			;
//		return 1;
//	}
//	else
//		return 0;
//}
///*********************************************************************************
// * @Function	:  ����������
// * @Input		:  Gmode:0,��֧��������;1,֧��������;
// * @Output		:  None
// * @Return		:  0��û���κΰ�������
// *							 1��KEY1����
// *						   2��KEY2����
// *							 3��KEY3����
// * @Others		:  ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
// * @Date			:  2022-07-23
// **********************************************************************************/
//u8 KEY_Scan(u8 mode)
//{
//	static u8 key_up = 1; // �������ɿ���־
//	if (mode)
//		key_up = 1; // ֧������
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
//	return 0; // �ް�������
//}
// 
///*********************************************************************************
// * @Function	:  STM32���������λ
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
//// ��ⰴ���Ƿ���
//static u16 time_4;
//static u8 key_old = 0;
//u8 Check_Key_ON_OFF()
//{
//	u8 key;
//	key = KEY_Scan(1);
//	// ����һ�εļ�ֵ�Ƚ� �������ȣ������м�ֵ�ı仯����ʼ��ʱ
//	if (key != 0 && time_4 == 0)
//	{
//		key_old = key;
//		time_4 = 1;
//	}
//	if (key != 0 && time_4 >= 1 && time_4 <= 100) // 100ms
//	{
//		time_4++; // ʱ���¼��
//	}
//	if (key == 0 && time_4 > 0 && time_4 < 30) // �̰�
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
//	else if (key == 0 && time_4 >= 30) // ����
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



