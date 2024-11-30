//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
//Ӳ������
#include "LED.h"
#include "Key.h"
#include "bh1750.h"
#include "Usart.h"
#include "fire.h"
#include "dht11.h"

#include "BEEP.h"
#include "OLED.h"
#include "Timer.h"
//C��
#include "stdio.h"
#include "string.h"
//�����豸
#include "esp8266.h"
//����Э���
#include "onenet.h"
char PUB_BUF[256];
char PUB_BUF1[256];
const char *topics[] = {"/k0hyw4o4uBh/STM32/user/lp/sub"};

const char pub_topics[] = "/k0hyw4o4uBh/STM32/user/lp/pub";

u8 flag1;
u8 alarm_is_free = 0;
u8 LED_Status = 0;
u8 alarmFlag = 0;
uint16_t threshold = 100;
u16 time_3;
uint8_t Value;
void Hardware_Init(void);

/*
************************************************************
*	�������ƣ�	Hardware_Init
*
*	�������ܣ�	Ӳ����ʼ��

*	˵����		��ʼ����Ƭ�������Լ�����豸
************************************************************
*/
void Hardware_Init(void)
{
	
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�жϿ�������������
        Delay_Init();									//systick��ʼ��  
        LED_Init();
        key_init();//������ʼ������
        uart1_Init(115200);							//����1����ӡ��Ϣ��
        uart2_Init(115200);					//����2������ESP8266��

        Beep_Init();
        DHT11_INIT();
        BH1750_Init();
       
		BH1750_Data_Send(0x07);//BHReset ��ֵΪ0x07
		BH1750_Data_Send(0x10);//BHModeH1 ��ֵΪ0x10
        /*********************oled��Ļ��ʾ*********************/
        
        OLED_Init();
        OLED_ON();

        UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
       
        
}



int main(void)
                              
{   
        //�����ʼ��
        Hardware_Init();
    /************�ⲿ�жϺ�����洫���������棬���ֱ���***************/
        FIRE_CONFIG();
        u8 key = 0;//������
/************dht11��ȡ��ʪ��***************/    
        u8 Tem,Hum;
    
    
    
/************bh1750��ȡ��ǿ***************/
        float LIGHTstreng = 0;
        uint32_t lightV_H = 0;
//        uint32_t lightV_L = 0;
    
    
    
//*****************esp8266��mqtt*****************/
        unsigned short timeCount = 0;	//���ͼ������       
        unsigned char *dataPtr = NULL;
        ESP8266_Init();					//��ʼ��ESP8266    
        while(OneNet_DevLink())			//����OneNET
        DelayXms(500);    
        DelayXms(250);
        //mqtt����
        OneNet_Subscribe(topics, 1);

	while(1){
        
            if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == 0){
              
                 OLED_ShowString(4,10,"ON  ");
            
            }else{
                
                   OLED_ShowString(4,10,"OFF");
            }
          
/************bh1750��ȡ��ǿ��dht11��ȡ��ʪ��***************/

        if(timeCount % 40 ==0)
        {
        LIGHTstreng = ((float)BH1750_Data_Read()/1.2);			

        lightV_H = (uint32_t)LIGHTstreng;
        UsartPrintf(USART_DEBUG, "��ǰ����ǿ��Ϊ��%d lx\r\n",lightV_H);
//      lightV_L = (uint32_t)(LIGHTstreng*100)%100;

        OLED_ShowNum(3,7,lightV_H,3);//����ֵ����λ
//      OLED_ShowString(4,10,".");	 	 //С����
//      OLED_ShowNum(4,11,lightV_L,2);//����ֵС��λ 
        /***********oled��ʾ��ʪ��******************/  
        Read_DHT_Data(&Tem,&Hum);
        OLED_ShowNum(1,7,Tem,2);
        OLED_ShowNum(2,7,Hum,2);


        Delay_ms(500);
        }
/************bh1750��ȡ��ǿ��dht11��ȡ��ʪ��***************/

        
/***********����1 ����2 �ֱ𿪹ؿ���led�ƺͷ�����  ����3�л�led����ģʽ���Զ�ģʽ���ֶ�ģʽ��******************/
        key = key_scan();//���뷴��whileѭ���У�ÿһ�ζ�ȡ�ĺ���ֵ��ͬ
        if(key == 1 || key == 2 || key == 3)//��Ϊ����1����2��3ʱ��ִ��
        {
        switch (key){
        case 1://����1����LED1
        LED1_Turn();
        
        break;
        case 2://����2����LED2
        BEEP_Turn();
        break;
        case 3://����3�����Զ��ƹ�ģʽ

        if(alarm_is_free==1){
            alarm_is_free = 0;
            BEEP_ON();
            Delay_ms(100);
            BEEP_OFF();
        }else{
            alarm_is_free =1;
            BEEP_ON();
            Delay_ms(100);
            BEEP_OFF();
        }
        
        Delay_ms(50);                                       
        break;                    
        }
        }      
        
        /********�Զ����ƹ����*************/

        if(alarm_is_free){
        if(LIGHTstreng<=threshold){
    
        LED1_ON(); 
        }else{
        LED1_OFF();                                                                                                                                            
        }
        }

        
/***********����1 ����2 �ֱ𿪹ؿ���led�ƺͷ�����  ����3�л�led����ģʽ���Զ�ģʽ���ֶ�ģʽ��******************/
     

/************************���ƶ˷�������*****************************/
        if(++timeCount >= 40)									//���ͼ��1s
        {   
        LED_Status =    GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_0);
        alarmFlag  =    GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12);
        UsartPrintf(USART_DEBUG, "OneNet_Publish\r\n");
        sprintf(PUB_BUF,"{\"Hum\":%d,\"Tem\":%d,\"Light\":%d,\"Led\":%d,\"Beep\":%d}",Hum,Tem,lightV_H,LED_Status,alarmFlag?0:1);
        OneNet_Publish(pub_topics, PUB_BUF);
//            sprintf(PUB_BUF1,"\"params\":{\"Hum\":%f,\"Tem\":%f}",(double)Hum,(double)Tem);
//        OneNet_Publish(pub_topics1, PUB_BUF1);
        timeCount = 0;
        ESP8266_Clear();
        }

        dataPtr = ESP8266_GetIPD(3);
        if(dataPtr != NULL)
        OneNet_RevPro(dataPtr);
        DelayXms(10);

        }
   
}
/************************���ƶ˷�������*****************************/

//void TIM2_IRQHandler(void)
//{
//    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)//���TIM3�����жϷ������
//    {
//        time_3++;
//        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//���TIMx�����жϱ�־ 
//        if (time_3 % 25 == 0)
//		{
//			Check_Key_ON_OFF();
//			time_3 = 0;
//		}
//    }
//}

