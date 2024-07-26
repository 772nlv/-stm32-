#include "user.h"
//�¶ȡ�ʪ������

unsigned short ret = 0;
extern char tempvalue_1[128];
extern char humivalue_1[128];
extern char lihgtvalue_1[128];
extern char potenvalue_1[128];
char tempvalue_1[128] = {0};
char humivalue_1[128] = {0};
char lihgtvalue_1[128] = {0};
char potenvalue_1[128] = {0};

char temp[2] = "";
char humi[2] = "";
extern int PWM_LED2_flag;

//������־
extern int SYSTEM_ON_FLAG;
int SYSTEM_ON_FLAG = 0;

//�ɼ�����״̬λ
extern int COLLECT_DATA_ON_FLAG;
int COLLECT_DATA_ON_FLAG = 1;

//PWM����������״̬λ
extern int PWM_BEEP_flag;
int PWM_BEEP_flag = 0;
//w25q128 �Լ� a24c04��ȡ��������

//------������
//�������
//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);


//_-------LED2����
//�������ȼ�
#define LED0_TASK_PRIO		2
//�����ջ��С	
#define LED0_STK_SIZE 		50  
//������
TaskHandle_t LED0Task_Handler;
//������
void led0_task(void *pvParameters);


//-------------LED3��˸
//�������ȼ�
#define LIGHT_TASK_PRIO		4
//�����ջ��С	
#define LIGHT_STK_SIZE 		50  
//������
TaskHandle_t LIGHTTask_Handler;
//������
void light_task(void *pvParameters);



//-------�ɼ�����
//�������ȼ�
#define DATA_TASK_PRIO		10
//�����ջ��С	
#define DATA_STK_SIZE 		200  
//������
TaskHandle_t DATATask_Handler;
//������
void Collect_DATA_task(void *pvParameters);

//------- PWM������
//�������ȼ�
#define PWM_BEEP_TASK_PRIO		5
//�����ջ��С	
#define PWM_BEEP_STK_SIZE 		50
//������
TaskHandle_t PWM_BEEPTask_Handler;
//������
void PWM_BEEP_task(void *pvParameters);


int main()
{
	//�жη��麯��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	//��ʼ��LED��
	LED_config();
	//�ӳٳ�ʼ��
	delay_init(168);
	//��ʼ��BEEP
	BEEP_Config();
	//1����ʼ������__PE_456
	KEY1_2_3_Config();
	//��ʼ��key4
	KEY4_Config();
	//���ڳ�ʼ��
	USART1_Config();
	uart2init();
	printf("���ڳ�ʼ�����\r\n");
	//�жϳ�ʼ��
	INTERRUPT_KEY1_Config();
	INTERRUPT_KEY2_Config();
	INTERRUPT_KEY3_Config();
	INTERRUPT_KEY4_Config();

	//���ȳ�ʼ��
	TIM12_CH2_PB15_Fan_Config();
	printf("led beep key fan ��ʼ���ɹ�\r\n");
	Fan_TurnOn();
	Fan_Control(0);
	//��ʼ��IIC
	IIC_Config();
	InitOLed();


	DHT11_Config();
	PWM_LED3_Config();
	
	//��ʱ����ʼ��
	//���ö�ʱ��4 ʵ�ֶ�ʱ10��
	//Ԥ��Ƶϵ��42000 Tim
	//	Timer4_Config(42000 - 1,20000 - 1);
//	DHT11_Readdata(humi,humi+1,temp,temp+1);
//	 char valuearr[128] = "";
//	sprintf(valuearr,"%d.%d  %d.%d\n",temp[0],temp[1],humi[0],humi[1]);
//	printf("%s",valuearr);


	//��ʱʱ�䵽����ȡ��ʪ��
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED2����Ŷ����
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler); 
							
    //�����ɼ���������
    xTaskCreate((TaskFunction_t )Collect_DATA_task,     
                (const char*    )"data_task",   
                (uint16_t       )DATA_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )DATA_TASK_PRIO,
                (TaskHandle_t*  )&DATATask_Handler);
				
				
	//LED3��˸
	xTaskCreate((TaskFunction_t )light_task,     
                (const char*    )"LED2_task",   
                (uint16_t       )LIGHT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LIGHT_TASK_PRIO,
                (TaskHandle_t*  )&LIGHTTask_Handler);   

	//PWM����������
	xTaskCreate((TaskFunction_t )PWM_BEEP_task,     
                (const char*    )"PWM_BEEP_task",   
                (uint16_t       )PWM_BEEP_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )PWM_BEEP_TASK_PRIO,
                (TaskHandle_t*  )&PWM_BEEPTask_Handler); 				
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}



//������
void led0_task(void *pvParameters)
{  
	u16 led0pwmval = 0;   
	
	u8 dir=1;
	
	while(1) //ʵ�ֱȽ�ֵ��0-300��������300���300-0�ݼ���ѭ��
	{
		if(PWM_LED2_flag == 1 && SYSTEM_ON_FLAG == 1)
		{

			//dir==1 led0pwmval����
			if(dir)
				led0pwmval++;
			else     //dir==0 led0pwmval�ݼ� 
				led0pwmval--;
			//led0pwmval����300�󣬷���Ϊ�ݼ�
			if(led0pwmval>100)
				dir=0;
			//led0pwmval�ݼ���0�󣬷����Ϊ����
			if(led0pwmval==0)
				dir=1;	
			//�޸ıȽ�ֵ���޸�ռ�ձ�	
			TIM_SetCompare1(TIM1,led0pwmval);	
				vTaskDelay(10);
		}
		else
		{
			//9�������ģʽ��ʹ��
			TIM_SetCompare1(TIM1,0);	
//			TIM_CtrlPWMOutputs(TIM1, DISABLE);	
		}
		}
}
//��˸
void light_task(void *pvParameters)
{  
	while(1)
	{
	if(SYSTEM_ON_FLAG)
	{
		GPIO_ToggleBits(GPIOE,GPIO_Pin_10);
	}
    
	vTaskDelay(1000);
	}	
	
}

//�ɼ�����������
void Collect_DATA_task(void *pvParameters)
{  
    while(1)
    {
		if(COLLECT_DATA_ON_FLAG)
		{
		
		int DHT11_Flag = DHT11_Readdata(humi,humi+1,temp,temp+1);
		//��ʱʱ�䵽����ȡ��ʪ��
		//����
		//����ADC��·������������
		ADC1_Light_Config();

		unsigned short Lightvalue = Get_ADC_Average(0,5);

		//LED1 ��ص�
		if(Lightvalue <= 700)
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_8);
			
		}
		else
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_8);
		}
		//��λ����
		unsigned short potential = Get_ADC_Average(10,5);
		float potential_1 = ((float)potential/(float)4096)*(float)3.3;
		if(DHT11_Flag == 0)
		{
			char valuearr[128] = "";
			sprintf(valuearr,"%d.%d  %d.%d  %f  %d  \n",temp[0],temp[1],humi[0],humi[1],potential_1,Lightvalue);
			printf("%s",valuearr);
			if(temp[0] >= 28)
			{
				Fan_Control(100);
				PWM_BEEP_flag = 1;
				vTaskDelay(3000);	
				PWM_BEEP_flag = 0;
			}
			else
			{				
				Fan_Control(0);
			}

			//�����ݸ�AT24C02
			char buf[128] ="";
			sprintf(buf,"%d.%d %d.%d",temp[0],temp[1],humi[0],humi[1]);
			int i = 0 ;
			for(i = 0 ; i < strlen(buf);i++)
			{
				while(AT24C02_Write_Bytes(i,buf[i]));
			}
			
		//OLED��ʾ
		//�¶�
		sprintf(tempvalue_1,"%d.%d",temp[0],temp[1]);
		//ʪ��
		sprintf(humivalue_1,"%d.%d",humi[0],humi[1]);
		//����
		sprintf(lihgtvalue_1,"%d",Lightvalue);
		//��λ
		sprintf(potenvalue_1,"%fV",potential_1);

		}
		else
		{
			printf("DHT11 �쳣\r\n");
		}	
		}

      	vTaskDelay(2000);		
    }
}

//PWM������������
void PWM_BEEP_task(void *pvParameters)
{  
	unsigned int led0pwmval=0;    
	unsigned char  dir=1;

	pwm2init();
	while(1)      
	{
		if(PWM_BEEP_flag == 1)
		{
		
		vTaskDelay(10);
		//dir==1 led0pwmval����
		if(dir)
			led0pwmval++;
		else     //dir==0 led0pwmval�ݼ� 
			led0pwmval--;
		//led0pwmval����300�󣬷���Ϊ�ݼ�
 		if(led0pwmval>60) 
			dir=0;
		//led0pwmval�ݼ���0�󣬷����Ϊ����
		if(led0pwmval==0)
			dir=1;	
		//�޸ıȽ�ֵ���޸�ռ�ձ�	
		TIM_SetCompare3(TIM2,led0pwmval);
			vTaskDelay(10);
		}
		else
		{
			TIM_SetCompare3(TIM2,0);
			vTaskDelay(10);
		}
 		
	}
	
}





















