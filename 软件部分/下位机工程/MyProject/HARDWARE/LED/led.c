#include "led.h"

/***********************************************
**函数名称：led驱动代码
**输入参数：无
**返回值：无
**其他说明：LED1--PA8 LED2--PA11  LED3--PA12
**作者：WFY
************************************************/

void led_Init(void)
{
	GPIO_InitTypeDef  GPIO_Initstructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //GPIOA的时钟使能

	
//LED1--PA8	
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_8;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_Initstructure);//对GPIOA8设置50M的推挽输出
	GPIO_SetBits(GPIOA,GPIO_Pin_8);//将GPIOA8位置1，即默认LED1不亮
	
//LED2--PA11
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_Initstructure);//对GPIOA11设置50M的推挽输出
	GPIO_SetBits(GPIOA,GPIO_Pin_11);//将GPIOA11位置1，即默认LED2不亮
	
//LED2--PA12
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_Initstructure);//对GPIOA12设置50M的推挽输出
	GPIO_SetBits(GPIOA,GPIO_Pin_12);//将GPIOA12位置1，即默认LED3不亮	

}

void Set_LED_Status(u8 led1_status,u8 led2_status,u8 led3_status,
	int count1,int count2,int count3,
		int time1,int time2,int time3)
{
	int i=0;
	if(led1_status==0)
	{
		LED1=led1_status;
		LED2=led2_status;
		LED3=led3_status;
		for(i=0;i<count1;i++)
		{
			delay_ms(time1);
		}
		LED1=~led1_status;
		for(i=0;i<count1;i++)
		{
			delay_ms(time1);
		}
	}
	if(led2_status==0)
	{
		LED1=led1_status;
		LED2=led2_status;
		LED3=led3_status;
		for(i=0;i<count2;i++)
		{
			delay_ms(time2);
		}
		LED2=~led2_status;
		for(i=0;i<count2;i++)
		{
			delay_ms(time2);
		}
	}
	if(led3_status==0)
	{
		LED1=led1_status;
		LED2=led2_status;
		LED3=led3_status;
		for(i=0;i<count3;i++)
		{
			delay_ms(time3);
		}
		LED3=~led3_status;
		for(i=0;i<count3;i++)
		{
			delay_ms(time3);
		}
	}
}

void WaterLights(void)
{
	LED1=0;delay_ms(100);LED1=1;delay_ms(100);
	LED2=0;delay_ms(100);LED2=1;delay_ms(100);
	LED3=0;delay_ms(100);LED3=1;delay_ms(100);
}

