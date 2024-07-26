#include "user.h"
//温度、湿度数组

//配置定时器4 实现定时一秒
void Timer4_Config(unsigned short prec,unsigned short peri)
{
	//配置时钟 APB1 :42hz 特殊之处：定时器 84hz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	//配置时间单元,初始化定时器
	TIM_TimeBaseInitTypeDef timer4struct;
	timer4struct.TIM_ClockDivision = TIM_CKD_DIV1;
	//预分频系数 - 总线时钟 做除法  给定时器分频
	//一个周期 时间 = 1/ 总线时钟 * 预分频系数 s
	timer4struct.TIM_Prescaler = prec;
	
	//时间节拍 每执行一个时间节拍 产生一个中断 
	//peri 是一个时间节拍执行的周期数
	timer4struct.TIM_Period = peri;
	TIM_TimeBaseInit(TIM4,&timer4struct);
	

	//配置中断条件
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	//中断使能
	TIM_Cmd(TIM4,ENABLE);
	
	//配置NVIC 中断控制器配置
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = TIM4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//中断函数
void TIM4_IRQHandler()
{
	char temp[2] = {0};
	char humi[2] = {0};
	//计时时间到，读取温湿度
	int DHT11_Flag =  DHT11_Readdata(humi,humi+1,temp,temp+1);
	//光照
	unsigned short Lightvalue = Get_ADC_Average(0,5);	
	//电位计算
	unsigned short potential = Get_ADC_Average(10,5);
	float potential_1 = ((float)potential/(float)4096)*(float)3.3;
	if(DHT11_Flag == 0)
	{
		char valuearr[128] = "";
		sprintf(valuearr,"%d.%d  %d.%d %d %f\n",temp[0],temp[1],humi[0],humi[1],Lightvalue,potential_1);
		printf("%s",valuearr);
		if(temp[0] >= 31)
		{
			Fan_Control(100);
			BEEP_Alarm_Count(3);
		}
	//OLED显示
	//温度
	char tempvalue_1[128] = {0};
	sprintf(tempvalue_1,"%d.%d",temp[0],temp[1]);
	Oled_print(50,0,tempvalue_1);
	OLed_ShowChina(90,0,SHESHIDU);
	//湿度
	char humivalue_1[128] = {0};
	sprintf(humivalue_1,"%d.%d",humi[0],humi[1]);
	Oled_print(50,2,humivalue_1);
	Oled_print(90,2,"%");
	//光照
	char lihgtvalue_1[128] = {0};

	sprintf(lihgtvalue_1,"%d",Lightvalue);
	Oled_print(50,4,lihgtvalue_1);

	//电位
	char potenvalue_1[128] = {0};
	sprintf(potenvalue_1,"%fV",potential_1);
	Oled_print(50,6,potenvalue_1);
	}
	else
	{
		printf("DHT11 异常\r\n");
	}	
	//清除标志位
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}



























