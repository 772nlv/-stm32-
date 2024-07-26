#include "user.h"

extern char tempvalue_1[128];
extern char humivalue_1[128];
extern char lihgtvalue_1[128];
extern char potenvalue_1[128];

//ϵͳ����
extern int SYSTEM_ON_FLAG;
//�ɼ�����״̬λ
extern int COLLECT_DATA_ON_FLAG;
//�ж�KEY_1��غ�������
void INTERRUPT_KEY1_Config(void)
{
	//1������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//����GPIO�ӿ�
	//2.��ʼ��IO�ӿ�
    GPIO_InitTypeDef keystruct;
    //���ź���
    keystruct.GPIO_Pin = GPIO_Pin_4;
    //����ģʽ
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //��������
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //����
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //��ʼ��
    GPIO_Init(GPIOE,&keystruct);
	
	//3���ⲿ�ж�����.E���ĺ��������ó��жϹ���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	
	//4���ⲿ�жϳ�ʼ��
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line4;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//�жϿ�����
	NVIC_InitTypeDef nvicstruct;
	//�ж����� ���� �ⲿ�ж�
	nvicstruct.NVIC_IRQChannel =  EXTI4_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//��ռ���ȼ� ��ѡһ
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//��Ӧ���ȼ�
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//�ж�KEY_2��غ�������
void INTERRUPT_KEY2_Config(void)
{
	//1������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	
	//����GPIO�ӿ�
	//2.��ʼ��IO�ӿ�
    GPIO_InitTypeDef keystruct;
    //���ź���
    keystruct.GPIO_Pin = GPIO_Pin_5;
    //����ģʽ
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //��������
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //����
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //��ʼ��
    GPIO_Init(GPIOE,&keystruct);
	
	//3���ⲿ�ж�����.E���ĺ��������ó��жϹ���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5);
	
	//4���ⲿ�жϳ�ʼ�����ô�������
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line5;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//�жϿ�����
	NVIC_InitTypeDef nvicstruct;
	//�����жϷ��飻
	nvicstruct.NVIC_IRQChannel =  EXTI9_5_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//��ռ���ȼ� ��ѡһ
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//��Ӧ���ȼ�
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//�ж�KEY_3��غ�������
void INTERRUPT_KEY3_Config(void)
{
	//1������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//����GPIO�ӿ�
	//2.��ʼ��IO�ӿ�
    GPIO_InitTypeDef keystruct;
    //���ź���
    keystruct.GPIO_Pin = GPIO_Pin_6;
    //����ģʽ
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //��������
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //����
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //��ʼ��
    GPIO_Init(GPIOE,&keystruct);
	
	//3���ⲿ�ж�����.E��6���������ó��жϹ���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource6);
	
	//4���ⲿ�жϳ�ʼ��
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line6;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//�жϿ�����
	NVIC_InitTypeDef nvicstruct;
	//�ж����� ���� �ⲿ�ж�
	nvicstruct.NVIC_IRQChannel =  EXTI9_5_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//��ռ���ȼ� ��ѡһ
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//��Ӧ���ȼ�
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}
//�ж�KEY_4��غ�������
void INTERRUPT_KEY4_Config(void)
{
	//1������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	//����GPIO�ӿ�
	//2.��ʼ��IO�ӿ�
    GPIO_InitTypeDef keystruct;
    //���ź���
    keystruct.GPIO_Pin = GPIO_Pin_13;
    //����ģʽ
    keystruct.GPIO_Mode = GPIO_Mode_IN;
    //��������
    keystruct.GPIO_PuPd = GPIO_PuPd_UP;
    //����
    keystruct.GPIO_Speed = GPIO_Low_Speed;
    //��ʼ��
    GPIO_Init(GPIOC,&keystruct);
	
	//3���ⲿ�ж�����.C��13�����������жϹ���
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
	
	//4���ⲿ�жϳ�ʼ��
	EXTI_InitTypeDef exitstruct;
	
	exitstruct.EXTI_Line = EXTI_Line13;
	exitstruct.EXTI_LineCmd = ENABLE;
	exitstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	exitstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	
	EXTI_Init(&exitstruct);
	
	//�жϿ�����
	NVIC_InitTypeDef nvicstruct;
	//�ж����� ���� �ⲿ�ж�
	nvicstruct.NVIC_IRQChannel =  EXTI15_10_IRQn;
	nvicstruct.NVIC_IRQChannelCmd = ENABLE;
	
	//��ռ���ȼ� ��ѡһ
	nvicstruct.NVIC_IRQChannelPreemptionPriority = 0;
	//��Ӧ���ȼ�
	nvicstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvicstruct);
}

//�жϺ���
//������ִ������ΪPE4��ƽ�ı�
void EXTI4_IRQHandler()
{

    //����ִ��������flag = 1 ��
    //ִ���Ժ�Ҫ���  flag = 0 ��
	BEEP_TurnOn();
	delay_ms(20);
	BEEP_TurnOff();
	OLed_Fill(0);
	Oled_print(15,3,"Welcome home");
	SYSTEM_ON_FLAG = 1;
	
    EXTI_ClearITPendingBit(EXTI_Line4);

}
void EXTI9_5_IRQHandler()
{
	
	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5))
	{
		BEEP_TurnOn();
		delay_ms(20);
		BEEP_TurnOff();
		
		if(COLLECT_DATA_ON_FLAG == 1)
		{
			COLLECT_DATA_ON_FLAG = 0;
		}
		
		else
		{
			COLLECT_DATA_ON_FLAG = 1;
		}
			
		OLed_Fill(0);
		Oled_print(0,0,"temp :");
		Oled_print(0,2,"humi :");
		Oled_print(0,4,"light:");
		Oled_print(0,6,"poten:");
		Oled_print(50,0,tempvalue_1);
		OLed_ShowChina(90,0,SHESHIDU);
		//ʪ��
		Oled_print(50,2,humivalue_1);
		Oled_print(90,2,"%");
		//����
		Oled_print(50,4,lihgtvalue_1);

		//��λ
		Oled_print(50,6,potenvalue_1);
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6))
	{
		BEEP_TurnOn();
		delay_ms(20);
		BEEP_TurnOff();
		char buftemp[128] = "";
		char bufhumi[128] = "";
		//��ȡat24c04��Ϣ
		for(int  i = 0 ; i < 5;i++)
		{
			buftemp[i] = AT24C02_Read_Bytes(i);
			bufhumi[i] = AT24C02_Read_Bytes(i + 5);
		}
		OLed_Fill(0);
		Oled_print(0,0,"Last Record:");
		Oled_print(10,3,"temp:");
		Oled_print(10,5,"humi:");
		Oled_print(50,3,buftemp);
		Oled_print(50,5,bufhumi);
		Oled_print(100,5,"%");
		OLed_ShowChina(100,3,SHESHIDU);
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}

void EXTI15_10_IRQHandler()
{
	BEEP_TurnOn();
	delay_ms(20);
	BEEP_TurnOff();
	OLed_Fill(0);
	Oled_print(35,3,"Bye Bye");
	SYSTEM_ON_FLAG = 0;
	GPIO_SetBits(GPIOE,GPIO_Pin_10);
	delay_ms(1000);
	OLed_Fill(0);
	EXTI_ClearITPendingBit(EXTI_Line13);
}




















