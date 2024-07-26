#include "user.h"
//拓展字符数组的方法
extern uint8_t zhao1[];
extern uint8_t shi1[];
extern uint8_t wen1[];
extern uint8_t du1[];
char wendu[128] = "0";
char shidu[128] = "0";
char guangzhao[30];

//配置部分；
void uart2init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	//1 串口时钟配置
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//2 D组时钟配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	//3引脚功能配置
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	
	//4.GPIO初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//输出类型不要配置
	GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//5.//串口初始化
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART_InitStructure);
	
	//6串口1使能
	USART_Cmd(USART2,ENABLE);
	//7串口中断使能
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	//8中断配置
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);		
}
//中断服务函数
void USART2_IRQHandler(void)
{
	unsigned char  res;
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{	
		res=USART_ReceiveData(USART2);
		switch(res)
		{
			//打开蜂鸣器
			case 1:OLed_Fill(0);Oled_print(16,2,"OPEN BEEP");GPIO_SetBits(GPIOB,GPIO_Pin_10);break;
			//关闭蜂鸣器
			case 2:OLed_Fill(0);Oled_print(16,2,"CLOSE BEEP");GPIO_ResetBits(GPIOB,GPIO_Pin_10);break;
			//打开三个灯
			case 3:OLed_Fill(0);Oled_print(16,2,"OPEN LEDS"); GPIO_ResetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);break;
			//关闭三个灯
			case 4:OLed_Fill(0);Oled_print(16,2,"CLOSE LEDS");GPIO_SetBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);break;
			//显示温度
			case 5:
					OLed_Fill(0);						
					OLed_Fill(0);
					Oled_print(1,2,"temp is");
					Oled_print(65,2,wendu);
					;break;
			//显示湿度
			case 6:
					OLed_Fill(0);						
					OLed_Fill(0);
					Oled_print(1,2,"humi is");
					Oled_print(65,2,shidu);
					;break;
			//显示光照
			case 7:
					OLed_Fill(0);
					Oled_print(1,2,"light is");
					Oled_print(70,2,guangzhao);
					break;
			//输入错误
			//default: OLed_Fill(0);OLed_ShowASCII(8,2,"INPUT ERROR!"); break;
		}
		
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
}













