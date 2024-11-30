//单片机头文件
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
//硬件驱动
#include "LED.h"
#include "Key.h"
#include "bh1750.h"
#include "Usart.h"
#include "fire.h"
#include "dht11.h"

#include "BEEP.h"
#include "OLED.h"
#include "Timer.h"
//C库
#include "stdio.h"
#include "string.h"
//网络设备
#include "esp8266.h"
//网络协议层
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
*	函数名称：	Hardware_Init
*
*	函数功能：	硬件初始化

*	说明：		初始化单片机功能以及外接设备
************************************************************
*/
void Hardware_Init(void)
{
	
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//中断控制器分组设置
        Delay_Init();									//systick初始化  
        LED_Init();
        key_init();//按键初始化函数
        uart1_Init(115200);							//串口1，打印信息用
        uart2_Init(115200);					//串口2，驱动ESP8266用

        Beep_Init();
        DHT11_INIT();
        BH1750_Init();
       
		BH1750_Data_Send(0x07);//BHReset 的值为0x07
		BH1750_Data_Send(0x10);//BHModeH1 的值为0x10
        /*********************oled屏幕显示*********************/
        
        OLED_Init();
        OLED_ON();

        UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");
       
        
}



int main(void)
                              
{   
        //外设初始化
        Hardware_Init();
    /************外部中断红外火焰传感器检测火焰，火灾报警***************/
        FIRE_CONFIG();
        u8 key = 0;//按键数
/************dht11获取温湿度***************/    
        u8 Tem,Hum;
    
    
    
/************bh1750获取光强***************/
        float LIGHTstreng = 0;
        uint32_t lightV_H = 0;
//        uint32_t lightV_L = 0;
    
    
    
//*****************esp8266，mqtt*****************/
        unsigned short timeCount = 0;	//发送间隔变量       
        unsigned char *dataPtr = NULL;
        ESP8266_Init();					//初始化ESP8266    
        while(OneNet_DevLink())			//接入OneNET
        DelayXms(500);    
        DelayXms(250);
        //mqtt订阅
        OneNet_Subscribe(topics, 1);

	while(1){
        
            if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == 0){
              
                 OLED_ShowString(4,10,"ON  ");
            
            }else{
                
                   OLED_ShowString(4,10,"OFF");
            }
          
/************bh1750获取光强、dht11获取温湿度***************/

        if(timeCount % 40 ==0)
        {
        LIGHTstreng = ((float)BH1750_Data_Read()/1.2);			

        lightV_H = (uint32_t)LIGHTstreng;
        UsartPrintf(USART_DEBUG, "当前光照强度为：%d lx\r\n",lightV_H);
//      lightV_L = (uint32_t)(LIGHTstreng*100)%100;

        OLED_ShowNum(3,7,lightV_H,3);//光照值整数位
//      OLED_ShowString(4,10,".");	 	 //小数点
//      OLED_ShowNum(4,11,lightV_L,2);//光照值小数位 
        /***********oled显示温湿度******************/  
        Read_DHT_Data(&Tem,&Hum);
        OLED_ShowNum(1,7,Tem,2);
        OLED_ShowNum(2,7,Hum,2);


        Delay_ms(500);
        }
/************bh1750获取光强、dht11获取温湿度***************/

        
/***********按键1 按键2 分别开关控制led灯和蜂鸣器  按键3切换led控制模式（自动模式和手动模式）******************/
        key = key_scan();//必须反在while循环中，每一次读取的函数值不同
        if(key == 1 || key == 2 || key == 3)//当为按键1或者2或3时，执行
        {
        switch (key){
        case 1://按键1控制LED1
        LED1_Turn();
        
        break;
        case 2://按键2控制LED2
        BEEP_Turn();
        break;
        case 3://按键3进入自动灯光模式

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
        
        /********自动化灯光控制*************/

        if(alarm_is_free){
        if(LIGHTstreng<=threshold){
    
        LED1_ON(); 
        }else{
        LED1_OFF();                                                                                                                                            
        }
        }

        
/***********按键1 按键2 分别开关控制led灯和蜂鸣器  按键3切换led控制模式（自动模式和手动模式）******************/
     

/************************向云端发送数据*****************************/
        if(++timeCount >= 40)									//发送间隔1s
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
/************************向云端发送数据*****************************/

//void TIM2_IRQHandler(void)
//{
//    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)//检查TIM3更新中断发生与否
//    {
//        time_3++;
//        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//清除TIMx更新中断标志 
//        if (time_3 % 25 == 0)
//		{
//			Check_Key_ON_OFF();
//			time_3 = 0;
//		}
//    }
//}

