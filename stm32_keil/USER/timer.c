#include "user.h"
//�¶ȡ�ʪ������

//���ö�ʱ��4 ʵ�ֶ�ʱһ��
void Timer4_Config(unsigned short prec,unsigned short peri)
{
	//����ʱ�� APB1 :42hz ����֮������ʱ�� 84hz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	//����ʱ�䵥Ԫ,��ʼ����ʱ��
	TIM_TimeBaseInitTypeDef timer4struct;
	timer4struct.TIM_ClockDivision = TIM_CKD_DIV1;
	//Ԥ��Ƶϵ�� - ����ʱ�� ������  ����ʱ����Ƶ
	//һ������ ʱ�� = 1/ ����ʱ�� * Ԥ��Ƶϵ�� s
	timer4struct.TIM_Prescaler = prec;
	
	//ʱ����� ÿִ��һ��ʱ����� ����һ���ж� 
	//peri ��һ��ʱ�����ִ�е�������
	timer4struct.TIM_Period = peri;
	TIM_TimeBaseInit(TIM4,&timer4struct);
	

	//�����ж�����
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	//�ж�ʹ��
	TIM_Cmd(TIM4,ENABLE);
	
	//����NVIC �жϿ���������
	NVIC_InitTypeDef nvicstruct;
	nvicstruct.NVIC_IRQChannel = TIM4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//�жϺ���
void TIM4_IRQHandler()
{
	char temp[2] = {0};
	char humi[2] = {0};
	//��ʱʱ�䵽����ȡ��ʪ��
	int DHT11_Flag =  DHT11_Readdata(humi,humi+1,temp,temp+1);
	//����
	unsigned short Lightvalue = Get_ADC_Average(0,5);	
	//��λ����
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
	//OLED��ʾ
	//�¶�
	char tempvalue_1[128] = {0};
	sprintf(tempvalue_1,"%d.%d",temp[0],temp[1]);
	Oled_print(50,0,tempvalue_1);
	OLed_ShowChina(90,0,SHESHIDU);
	//ʪ��
	char humivalue_1[128] = {0};
	sprintf(humivalue_1,"%d.%d",humi[0],humi[1]);
	Oled_print(50,2,humivalue_1);
	Oled_print(90,2,"%");
	//����
	char lihgtvalue_1[128] = {0};

	sprintf(lihgtvalue_1,"%d",Lightvalue);
	Oled_print(50,4,lihgtvalue_1);

	//��λ
	char potenvalue_1[128] = {0};
	sprintf(potenvalue_1,"%fV",potential_1);
	Oled_print(50,6,potenvalue_1);
	}
	else
	{
		printf("DHT11 �쳣\r\n");
	}	
	//�����־λ
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}



























