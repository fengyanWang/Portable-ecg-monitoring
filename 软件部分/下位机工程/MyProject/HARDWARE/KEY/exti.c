#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"




//static int Key1_Count;
//static int Key2_Count; 
 
//外部中断初始化函数
void EXTIX_Init(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;

	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟

	  KEY_Init();//初始化按键对应io模式
	
//key0
    //GPIOC.5 中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

////key1
//    //GPIOB.0	  中断线以及中断初始化配置
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);

//  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
////key2
//    //GPIOB.1	  中断线以及中断初始化配置
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);

//   	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


 
//  	NVIC_InitStructure.NVIC_IRQChannel = EXTI_Line0;			//使能按键所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
 
//   	NVIC_InitStructure.NVIC_IRQChannel = EXTI_Line1;			//使能按键所在的外部中断通道
//  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
//  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级1
//  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
//  	NVIC_Init(&NVIC_InitStructure); 
 
}

 
//void EXTI0_IRQHandler(void)
//{
//  printf("key1\r\n");
//	delay_ms(10);    //消抖
//	if(KEY1==0)
//	{
//		Key1_Count++;
//	}
//	while(!KEY1);
//	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
//}


 void EXTI9_5_IRQHandler(void)
{			
	printf("key0\r\n");
	delay_ms(10);   //消抖			 
	if(KEY0==0)	
	{
		Key0_Count++;
		Key0_Flag=Key0_Count;
	}
	while(!KEY0);
  EXTI_ClearITPendingBit(EXTI_Line5);    //清除LINE5上的中断标志位  
}

//void EXTI1_IRQHandler(void)
//{
//	printf("key2\r\n");
//	delay_ms(10);    //消抖
//	if(KEY2==0)
//	{
//		Key2_Count++;
//	}
//	while(!KEY2);
//	EXTI_ClearITPendingBit(EXTI_Line1);  //清除EXTI1线路挂起位
//}

/***********************************************
**函数名称：根据按键确定相应的功能
**输入参数：无
**返回值：
**其他说明：无
**作者：WFY
************************************************/
u8 Key_Function(void)
{
	
	
	if(Key0_Count%4==0)
	{
		return DATE_TEMP_FLAG;
	}
	else if(Key0_Count%4==1)
	{
		
		return ECG_HEARTRATE_FLAG;
	}
	else if(Key0_Count%4==2)
	{
		return ECGDATEHANDLE;
	}
	else
	{
		return OTHER_FLAG;
	}	
}


/***********************************************
**函数名称：根据按键显示相应的窗口
**输入参数：无
**返回值：
**其他说明：无
**作者：WFY
************************************************/
void Display_Function(void)
{
	u8 f=0;
	f=Key_Function();
	switch(f)
	{
		case DATE_TEMP_FLAG:  //时间温度切换显示
		{
			Set_LED_Status(0,1,1,1,0,0,100,0,0);
			OLED_Show_Date_Temp(8000);
			break;
		}
		case ECG_HEARTRATE_FLAG:  //心电波形和心率切换显示
		{
			Set_LED_Status(1,0,1,0,1,0,0,100,0);
			OLED_Show_ECG_HeartRate(1000);
			break;
		}
		case ECGDATEHANDLE:
		{
			WaterLights();
			ECGDate_Handle();//心电数据处理
		}
		case OTHER_FLAG:
		{
			Set_LED_Status(1,1,0,0,0,1,0,0,100);
			Display1_Function();
			break;
		}
	}
}
	

