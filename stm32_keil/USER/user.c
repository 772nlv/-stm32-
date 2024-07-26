#include "user.h"
//温度、湿度数组

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

//开机标志
extern int SYSTEM_ON_FLAG;
int SYSTEM_ON_FLAG = 0;

//采集数据状态位
extern int COLLECT_DATA_ON_FLAG;
int COLLECT_DATA_ON_FLAG = 1;

//PWM蜂鸣器数据状态位
extern int PWM_BEEP_flag;
int PWM_BEEP_flag = 0;
//w25q128 以及 a24c04读取数据数组

//------父任务
//任务调度
//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);


//_-------LED2呼吸
//任务优先级
#define LED0_TASK_PRIO		2
//任务堆栈大小	
#define LED0_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED0Task_Handler;
//任务函数
void led0_task(void *pvParameters);


//-------------LED3闪烁
//任务优先级
#define LIGHT_TASK_PRIO		4
//任务堆栈大小	
#define LIGHT_STK_SIZE 		50  
//任务句柄
TaskHandle_t LIGHTTask_Handler;
//任务函数
void light_task(void *pvParameters);



//-------采集数据
//任务优先级
#define DATA_TASK_PRIO		10
//任务堆栈大小	
#define DATA_STK_SIZE 		200  
//任务句柄
TaskHandle_t DATATask_Handler;
//任务函数
void Collect_DATA_task(void *pvParameters);

//------- PWM蜂鸣器
//任务优先级
#define PWM_BEEP_TASK_PRIO		5
//任务堆栈大小	
#define PWM_BEEP_STK_SIZE 		50
//任务句柄
TaskHandle_t PWM_BEEPTask_Handler;
//任务函数
void PWM_BEEP_task(void *pvParameters);


int main()
{
	//中段分组函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	//初始化LED；
	LED_config();
	//延迟初始化
	delay_init(168);
	//初始化BEEP
	BEEP_Config();
	//1、初始化按键__PE_456
	KEY1_2_3_Config();
	//初始化key4
	KEY4_Config();
	//串口初始化
	USART1_Config();
	uart2init();
	printf("串口初始化完成\r\n");
	//中断初始化
	INTERRUPT_KEY1_Config();
	INTERRUPT_KEY2_Config();
	INTERRUPT_KEY3_Config();
	INTERRUPT_KEY4_Config();

	//风扇初始化
	TIM12_CH2_PB15_Fan_Config();
	printf("led beep key fan 初始化成功\r\n");
	Fan_TurnOn();
	Fan_Control(0);
	//初始化IIC
	IIC_Config();
	InitOLed();


	DHT11_Config();
	PWM_LED3_Config();
	
	//定时器初始化
	//配置定时器4 实现定时10秒
	//预分频系数42000 Tim
	//	Timer4_Config(42000 - 1,20000 - 1);
//	DHT11_Readdata(humi,humi+1,temp,temp+1);
//	 char valuearr[128] = "";
//	sprintf(valuearr,"%d.%d  %d.%d\n",temp[0],temp[1],humi[0],humi[1]);
//	printf("%s",valuearr);


	//计时时间到，读取温湿度
	//创建开始任务
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}

//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    //创建LED2呼吸哦任务
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler); 
							
    //创建采集数据任务
    xTaskCreate((TaskFunction_t )Collect_DATA_task,     
                (const char*    )"data_task",   
                (uint16_t       )DATA_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )DATA_TASK_PRIO,
                (TaskHandle_t*  )&DATATask_Handler);
				
				
	//LED3闪烁
	xTaskCreate((TaskFunction_t )light_task,     
                (const char*    )"LED2_task",   
                (uint16_t       )LIGHT_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LIGHT_TASK_PRIO,
                (TaskHandle_t*  )&LIGHTTask_Handler);   

	//PWM蜂鸣器任务
	xTaskCreate((TaskFunction_t )PWM_BEEP_task,     
                (const char*    )"PWM_BEEP_task",   
                (uint16_t       )PWM_BEEP_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )PWM_BEEP_TASK_PRIO,
                (TaskHandle_t*  )&PWM_BEEPTask_Handler); 				
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}



//呼吸灯
void led0_task(void *pvParameters)
{  
	u16 led0pwmval = 0;   
	
	u8 dir=1;
	
	while(1) //实现比较值从0-300递增，到300后从300-0递减，循环
	{
		if(PWM_LED2_flag == 1 && SYSTEM_ON_FLAG == 1)
		{

			//dir==1 led0pwmval递增
			if(dir)
				led0pwmval++;
			else     //dir==0 led0pwmval递减 
				led0pwmval--;
			//led0pwmval到达300后，方向为递减
			if(led0pwmval>100)
				dir=0;
			//led0pwmval递减到0后，方向改为递增
			if(led0pwmval==0)
				dir=1;	
			//修改比较值，修改占空比	
			TIM_SetCompare1(TIM1,led0pwmval);	
				vTaskDelay(10);
		}
		else
		{
			//9控制输出模式不使能
			TIM_SetCompare1(TIM1,0);	
//			TIM_CtrlPWMOutputs(TIM1, DISABLE);	
		}
		}
}
//闪烁
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

//采集数据任务函数
void Collect_DATA_task(void *pvParameters)
{  
    while(1)
    {
		if(COLLECT_DATA_ON_FLAG)
		{
		
		int DHT11_Flag = DHT11_Readdata(humi,humi+1,temp,temp+1);
		//计时时间到，读取温湿度
		//光照
		//配置ADC电路——光敏电阻
		ADC1_Light_Config();

		unsigned short Lightvalue = Get_ADC_Average(0,5);

		//LED1 光控灯
		if(Lightvalue <= 700)
		{
			GPIO_ResetBits(GPIOE,GPIO_Pin_8);
			
		}
		else
		{
			GPIO_SetBits(GPIOE,GPIO_Pin_8);
		}
		//电位计算
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

			//发数据给AT24C02
			char buf[128] ="";
			sprintf(buf,"%d.%d %d.%d",temp[0],temp[1],humi[0],humi[1]);
			int i = 0 ;
			for(i = 0 ; i < strlen(buf);i++)
			{
				while(AT24C02_Write_Bytes(i,buf[i]));
			}
			
		//OLED显示
		//温度
		sprintf(tempvalue_1,"%d.%d",temp[0],temp[1]);
		//湿度
		sprintf(humivalue_1,"%d.%d",humi[0],humi[1]);
		//光照
		sprintf(lihgtvalue_1,"%d",Lightvalue);
		//电位
		sprintf(potenvalue_1,"%fV",potential_1);

		}
		else
		{
			printf("DHT11 异常\r\n");
		}	
		}

      	vTaskDelay(2000);		
    }
}

//PWM蜂鸣器任务函数
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
		//dir==1 led0pwmval递增
		if(dir)
			led0pwmval++;
		else     //dir==0 led0pwmval递减 
			led0pwmval--;
		//led0pwmval到达300后，方向为递减
 		if(led0pwmval>60) 
			dir=0;
		//led0pwmval递减到0后，方向改为递增
		if(led0pwmval==0)
			dir=1;	
		//修改比较值，修改占空比	
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





















