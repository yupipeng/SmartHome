#include "bh1750.h" 
#include "Delay.h"
void BH1750_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_4;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	GPIO_Init(GPIOA, &GPIO_InitStructure);	  //��ʼ��GPIOD3,6
 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_4);	

	BH1750_Data_Send(BHPowOn);
}

//����IIC��ʼ�ź�
void BH_IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	Delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void BH_IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	Delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	Delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 BH_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;Delay_us(1);	   
	IIC_SCL=1;Delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			BH_IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void BH_IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	Delay_us(2);
	IIC_SCL=1;
	Delay_us(2);
	IIC_SCL=0;
}
//������ACKӦ��		    
void BH_IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	Delay_us(2);
	IIC_SCL=1;
	Delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void BH_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		Delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		Delay_us(2); 
		IIC_SCL=0;	
		Delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 BH_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        Delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		Delay_us(1); 
    }					 
    if (!ack)
        BH_IIC_NAck();//����nACK
    else
        BH_IIC_Ack(); //����ACK   
    return receive;
}

/*************************************************************************************/
void BH1750_Data_Send(u8 command)
{
    do{
    BH_IIC_Start();                      //iic��ʼ�ź�
    BH_IIC_Send_Byte(BHAddWrite);       //����������ַ
    }while(BH_IIC_Wait_Ack());           //�ȴ��ӻ�Ӧ��
    BH_IIC_Send_Byte(command);          //����ָ��
    BH_IIC_Wait_Ack();                   //�ȴ��ӻ�Ӧ��
    BH_IIC_Stop();                       //iicֹͣ�ź�
}

u16 BH1750_Data_Read(void)
{
	u16 buf;
	BH_IIC_Start();                       //iic��ʼ�ź�
	BH_IIC_Send_Byte(BHAddRead);         //����������ַ+����־λ
	BH_IIC_Wait_Ack();                     //�ȴ��ӻ�Ӧ��
	buf=BH_IIC_Read_Byte(1);              //��ȡ����
	buf=buf<<8;                        //��ȡ������߰�λ����
	buf+=0x00ff&BH_IIC_Read_Byte(0);      //��ȡ������ڰ�λ����
	BH_IIC_Stop();                        //����ֹͣ�ź� 
	return buf; 
}
