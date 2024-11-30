#ifndef __BH1750_H
#define __BH1750_H
#include "sys.h"
#include "delay.h"
//IO��������
 
#define SDA_IN()  {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=8<<20;} 
#define SDA_OUT() {GPIOA->CRL&=0XFF0FFFFF;GPIOA->CRL|=3<<20;}



#define IIC_SCL    PAout(4) //SCL
#define IIC_SDA    PAout(5) //SDA	 
#define READ_SDA   PAin(5)  //����SDA 
#define ADDR 0x23//0100011
#define uchar unsigned char 

#define BHAddWrite     0x46      //�ӻ���ַ+���д����λ
#define BHAddRead      0x47      //�ӻ���ַ+��������λ
#define BHPowDown      0x00      //�ر�ģ��
#define BHPowOn        0x01      //��ģ��ȴ�����ָ��
#define BHReset        0x07      //�������ݼĴ���ֵ��PowerOnģʽ����Ч
#define BHModeH1       0x10      //�߷ֱ��� ��λ1lx ����ʱ��120ms
#define BHModeH2       0x11      //�߷ֱ���ģʽ2 ��λ0.5lx ����ʱ��120ms
#define BHModeL        0x13      //�ͷֱ��� ��λ4lx ����ʱ��16ms
#define BHSigModeH     0x20      //һ�θ߷ֱ��� ���� ������ģ��ת�� PowerDownģʽ
#define BHSigModeH2    0x21      //ͬ������
#define BHSigModeL     0x23      // ������

void Single_Write_BH1750(uchar REG_Address);
void BH1750_Init(void);
void BH1750_Data_Send(u8 command);
u16 BH1750_Data_Read(void);

//IIC���в�������
void BH_IIC_Init(void);                //��ʼ��IIC��IO��				 
void BH_IIC_Start(void);				//����IIC��ʼ�ź�
void BH_IIC_Stop(void);	  			//����IICֹͣ�ź�
void BH_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 BH_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 BH_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void BH_IIC_Ack(void);					//IIC����ACK�ź�
void BH_IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	

#endif
