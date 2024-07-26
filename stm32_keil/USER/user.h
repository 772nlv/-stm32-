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
//功能函数
void My_Delay(unsigned int DelayCount);//延时函数

//led模块
void LED_config(void);//led初始化
void LED_TurnOn(unsigned int LEDNUM);//打开led函数
void LED_TurnOff(unsigned int LEDNUM);//关闭led
void LED_Shine(unsigned int LEDNUM);//led闪烁
void LED_FLow(void);//led流水

	
//beep模块

//配置蜂鸣器
void BEEP_Config(void);
//打开蜂鸣器
void BEEP_TurnOn(void);
//关闭蜂鸣器
void BEEP_TurnOff(void);
//蜂鸣器alarm 限定次数
void BEEP_Alarm_Count(unsigned int count);
//蜂鸣器一直警报
void BEEP_Alarm(void);
//蜂鸣器和led同步
void BEEP_LED_To(unsigned int count);


//key按键模块
//1、初始化按键key123
void KEY1_2_3_Config(void);
//key4
void KEY4_Config(void);
//2、扫描按键
void KEY_Scan(void);


//外部中断相关函数声明
void INTERRUPT_KEY1_Config(void);
//中断KEY_2相关函数声明
void INTERRUPT_KEY2_Config(void);
//中断KEY_3相关函数声明
void INTERRUPT_KEY3_Config(void);
//中断KEY_4相关函数声明
void INTERRUPT_KEY4_Config(void);


//Systick定时器模块
void SYSTICK_Init(unsigned int n);
//systick 延时函数
void MY_Systick_Delay(unsigned int n);

//定时器模块
//配置定时器4 实现定时一秒
void Timer4_Config(unsigned short prec,unsigned short peri);

//pwm模块
//配置
void TIM12_CH2_PB15_Fan_Config(void);
//2.打开风扇函数
void Fan_TurnOn(void);
//3.关闭风扇
void Fan_TurnOff(void);
//4、控制风扇
void Fan_Control(unsigned int value);
void Fan_Low_Control(void);
void Fan_MId_Control(void);
void Fan_High_Control(void);
//初始化PWM_ LED2
void PWM_LED3_Config(void);	
void PWM_LED_ON(void);

void pwm2init(void);
void PWM_BEEP_ON(void);

//串口初始化
void USART1_Config(void);

//DHT11模块
//1、DHT11配置函数
void DHT11_Config(void);
//输出模式
void DHT11_OUTMode(void);
//输入模式
void DHT11_INMode(void);
//DHT11读取字节
unsigned char DHT11_ReadBytes(void);
//DHT11 读数据
char DHT11_Readdata(char *humiz,char *humix,char *tempz,char *tempx);


//spi模块
//SPI初始化函数
void SPI_Config(void);
//SPI读写函数
unsigned char SPI1_Write_Read(unsigned char senddata);

//w25q64模块
//1、设备初始化函数
void W25Q64_Config(void);
//读取设备ID函数
unsigned short W25Q64_ReadID(void);
//写数据使能函数
void W25Q64_Write_Enable(void);
unsigned char W25Q64_Check_Busy(void);
void W25Q64_Erase_All_Chip(void);
unsigned int W25Q64_Read_Data(unsigned int wordaddr,unsigned char buff[],unsigned char len);
int W25Q64_Write_Data(unsigned int writeaddr,char *pbuff,unsigned short byteNum);

//ADC模块
//配置ADC电路——光敏电阻
void ADC1_Light_Config(void);
//开始采集的函数
unsigned short Get_ADC_Channel(unsigned int channel);
//通道数 + 采集时间
unsigned short Get_ADC_Average(unsigned int channel,char times);


//ESP8266模块
void uart2init(void);

//配置定时器5 实现定时一秒
void Timer5_Config(unsigned short prec,unsigned short peri);






















#endif



