#include "sys.h"
#include "beep.h"
#include "delay.h"

/***********************************************
**函数名称：蜂鸣器驱动函数
**输入参数：无
**返回值：无
**其他说明：BEEP--PC13
**作者：WFY
************************************************/
void Beep_Init(void)
{
	GPIO_InitTypeDef  GPIO_Initstructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //GPIOC的时钟使能
		
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC,&GPIO_Initstructure);//对GPIOC8设置50M的推挽输出
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);//先关闭蜂鸣器
}

void One_Long_One_Short(void)
{
	
	BEEP=1;
	delay_ms(800);
	BEEP=0;
	delay_ms(800);//蜂鸣器发声500ms
	
	BEEP=1;//打开蜂鸣器
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//蜂鸣器发声500ms
	
}

void One_Long_Two_Short(void)
{
	BEEP=1;
	delay_ms(800);
	BEEP=0;
	delay_ms(800);//蜂鸣器发声500ms
	
	BEEP=1;//打开蜂鸣器
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//蜂鸣器发声500ms
	
	BEEP=1;//打开蜂鸣器
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//蜂鸣器发声500ms
}

void One_Long_Three_Short(void)
{
	One_Long_Two_Short();
	
	BEEP=1;//打开蜂鸣器
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//蜂鸣器发声500ms
}

void One_Long_Four_Short(void)
{
	One_Long_Three_Short();
	BEEP=1;//打开蜂鸣器
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//蜂鸣器发声500ms
}

void Two_Long_Two_Short(void)
{
	BEEP=1;
	delay_ms(800);
	BEEP=0;
	delay_ms(800);//蜂鸣器发声500ms
	
	BEEP=1;
	delay_ms(800);
	BEEP=0;
	delay_ms(800);//蜂鸣器发声500ms
	
	BEEP=1;//打开蜂鸣器
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//蜂鸣器发声500ms
	
	BEEP=1;//打开蜂鸣器
	delay_ms(200);
	BEEP=0;
	delay_ms(800);//蜂鸣器发声500ms
}
