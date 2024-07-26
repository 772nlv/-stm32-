#ifndef __USER
#define __USER

#include "stm32f4xx.h"
#include "delay.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "iic.h"
#include "FreeRTOS.h"
#include "task.h"
#define LED1 1
#define LED2 2
#define LED3 3


#define us 4
#define ms 5

extern int PWM_LED2_flag;

extern uint8_t SHESHIDU[];
extern uint8_t BAIFENHAO[];
//���ܺ���
void My_Delay(unsigned int DelayCount);//��ʱ����

//ledģ��
void LED_config(void);//led��ʼ��
void LED_TurnOn(unsigned int LEDNUM);//��led����
void LED_TurnOff(unsigned int LEDNUM);//�ر�led
void LED_Shine(unsigned int LEDNUM);//led��˸
void LED_FLow(void);//led��ˮ

	
//beepģ��

//���÷�����
void BEEP_Config(void);
//�򿪷�����
void BEEP_TurnOn(void);
//�رշ�����
void BEEP_TurnOff(void);
//������alarm �޶�����
void BEEP_Alarm_Count(unsigned int count);
//������һֱ����
void BEEP_Alarm(void);
//��������ledͬ��
void BEEP_LED_To(unsigned int count);


//key����ģ��
//1����ʼ������key123
void KEY1_2_3_Config(void);
//key4
void KEY4_Config(void);
//2��ɨ�谴��
void KEY_Scan(void);


//�ⲿ�ж���غ�������
void INTERRUPT_KEY1_Config(void);
//�ж�KEY_2��غ�������
void INTERRUPT_KEY2_Config(void);
//�ж�KEY_3��غ�������
void INTERRUPT_KEY3_Config(void);
//�ж�KEY_4��غ�������
void INTERRUPT_KEY4_Config(void);


//Systick��ʱ��ģ��
void SYSTICK_Init(unsigned int n);
//systick ��ʱ����
void MY_Systick_Delay(unsigned int n);

//��ʱ��ģ��
//���ö�ʱ��4 ʵ�ֶ�ʱһ��
void Timer4_Config(unsigned short prec,unsigned short peri);

//pwmģ��
//����
void TIM12_CH2_PB15_Fan_Config(void);
//2.�򿪷��Ⱥ���
void Fan_TurnOn(void);
//3.�رշ���
void Fan_TurnOff(void);
//4�����Ʒ���
void Fan_Control(unsigned int value);
void Fan_Low_Control(void);
void Fan_MId_Control(void);
void Fan_High_Control(void);
//��ʼ��PWM_ LED2
void PWM_LED3_Config(void);	
void PWM_LED_ON(void);

void pwm2init(void);
void PWM_BEEP_ON(void);

//���ڳ�ʼ��
void USART1_Config(void);

//DHT11ģ��
//1��DHT11���ú���
void DHT11_Config(void);
//���ģʽ
void DHT11_OUTMode(void);
//����ģʽ
void DHT11_INMode(void);
//DHT11��ȡ�ֽ�
unsigned char DHT11_ReadBytes(void);
//DHT11 ������
char DHT11_Readdata(char *humiz,char *humix,char *tempz,char *tempx);


//spiģ��
//SPI��ʼ������
void SPI_Config(void);
//SPI��д����
unsigned char SPI1_Write_Read(unsigned char senddata);

//w25q64ģ��
//1���豸��ʼ������
void W25Q64_Config(void);
//��ȡ�豸ID����
unsigned short W25Q64_ReadID(void);
//д����ʹ�ܺ���
void W25Q64_Write_Enable(void);
unsigned char W25Q64_Check_Busy(void);
void W25Q64_Erase_All_Chip(void);
unsigned int W25Q64_Read_Data(unsigned int wordaddr,unsigned char buff[],unsigned char len);
int W25Q64_Write_Data(unsigned int writeaddr,char *pbuff,unsigned short byteNum);

//ADCģ��
//����ADC��·������������
void ADC1_Light_Config(void);
//��ʼ�ɼ��ĺ���
unsigned short Get_ADC_Channel(unsigned int channel);
//ͨ���� + �ɼ�ʱ��
unsigned short Get_ADC_Average(unsigned int channel,char times);


//ESP8266ģ��
void uart2init(void);

//���ö�ʱ��5 ʵ�ֶ�ʱһ��
void Timer5_Config(unsigned short prec,unsigned short peri);






















#endif



