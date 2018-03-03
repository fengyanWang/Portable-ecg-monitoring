#include "delay.h" 			 
#include "usart.h" 			 
#include "usart2.h" 			 
#include "hc05.h" 
#include "led.h" 
#include "string.h"	 
#include "math.h"
 	   
/**************************
**函数名称：HC05_Init
**函数功能：初始化ATK-HC05模块
**函数参数：无
**函数返回：返回值:0,成功;1,失败.
**函数作者：王丰焱
**修改时间：2016.05.17
**特别说明：PA4-LED    PC4-KEY
****************************/
void HC05_Init(void)
{
	  		 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC,ENABLE);	//使能PORTA C时钟	
//LED 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //上拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化A4
	 
//KEY
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC4

	USART2_Init(9600);	//初始化串口2为:9600,波特率.
	HC05_KEY=1;					//KEY置高,进入AT模式	 
}	 


/**************************
**函数名称：HC05_Get_Role
**函数功能：获取ATK-HC05模块的角色
**函数参数：无
**函数返回：返回值:0,从机;1,主机;0XFF,获取失败.
**函数作者：王丰焱
**修改时间：2016.05.17
**特别说明：无
****************************/
u8 HC05_Get_Role(void)
{	 		    
	u8 retry=0X0F;
	u8 temp,t;
	while(retry--)
	{
		HC05_KEY=1;					//KEY置高,进入AT模式
		delay_ms(10);
		u2_printf("AT+ROLE?\r\n");	//查询角色
		for(t=0;t<20;t++) 			//最长等待200ms,来接收HC05模块的回应
		{
			delay_ms(10);
			if(USART2_RX_STA&0X8000)break;
		}		
		HC05_KEY=0;					//KEY拉低,退出AT模式
		if(USART2_RX_STA&0X8000)	//接收到一次数据了
		{
			temp=USART2_RX_STA&0X7FFF;	//得到数据长度
			USART2_RX_STA=0;			 
			if(temp==13&&USART2_RX_BUF[0]=='+')//接收到正确的应答了
			{
				temp=USART2_RX_BUF[6]-'0';//得到主从模式值
				break;
			}
		}		
	}
	if(retry==0)temp=0XFF;//查询失败.
	return temp;
} 							   

/**************************
**函数名称：HC05_Set_Cmd
**函数功能：ATK-HC05设置命令
**函数参数：atstr:AT指令串.比如:"AT+RESET"/"AT+UART=9600,0,0"/"AT+ROLE=0"等字符串
**函数返回：返回值:0,设置成功;其他,设置失败.
**函数作者：王丰焱
**修改时间：2016.05.17
**特别说明：此函数用于设置ATK-HC05,适用于仅返回OK应答的AT指令
****************************/
u8 HC05_Set_Cmd(u8* atstr)
{	 		    
	u8 retry=0X0F;
	u8 temp,t;
	while(retry--)
	{
		HC05_KEY=1;					//KEY置高,进入AT模式
		delay_ms(10);
		u2_printf("%s\r\n",atstr);	//发送AT字符串
		HC05_KEY=0;					//KEY拉低,退出AT模式
		for(t=0;t<20;t++) 			//最长等待100ms,来接收HC05模块的回应
		{
			if(USART2_RX_STA&0X8000)break;
			delay_ms(5);
		}		
		if(USART2_RX_STA&0X8000)	//接收到一次数据了
		{
			temp=USART2_RX_STA&0X7FFF;	//得到数据长度
			USART2_RX_STA=0;			 
			if(temp==4&&USART2_RX_BUF[0]=='O')//接收到正确的应答了
			{			
				temp=0;
				break;			 
			}
		}		
	}
	if(retry==0)temp=0XFF;//设置失败.
	return temp;
} 
///////////////////////////////////////////////////////////////////////////////////////////////////
//通过该函数,可以利用USMART,调试接在串口2上的ATK-HC05模块
//str:命令串.(这里注意不再需要再输入回车符)
void HC05_CFG_CMD(u8 *str)
{					  
	u8 temp;
	u8 t;		  
	HC05_KEY=1;						//KEY置高,进入AT模式
	delay_ms(10);
	u2_printf("%s\r\n",(char*)str); //发送指令
	for(t=0;t<50;t++) 				//最长等待500ms,来接收HC05模块的回应
	{
		if(USART2_RX_STA&0X8000)break;
		delay_ms(10);
	}									    
	HC05_KEY=0;						//KEY拉低,退出AT模式
	if(USART2_RX_STA&0X8000)		//接收到一次数据了
	{
		temp=USART2_RX_STA&0X7FFF;	//得到数据长度
		USART2_RX_STA=0;
		USART2_RX_BUF[temp]=0;		//加结束符		 
		printf("\r\n%s",USART2_RX_BUF);//发送回应数据到串口1
	} 				 
}

//显示ATK-HC05模块的主从状态
void HC05_Role_Show(void)
{
	if(HC05_Get_Role()==1)
		printf("ROLE:Master\n");//主机
	else 
		printf("ROLE:Slave\n");//从机
}


//显示ATK-HC05模块的连接状态
u8 HC05_Sta_Show(void)
{												 
	if(HC05_LED)
		return 1;//连接成功
	else 
		return 0;//未连接
}	
//给上位机发送心电数据
void HC05_SendDate(double *arry,int num,int len)
{
	int i=0;
	char DateTemp[30];
	for(i=num*128;i<len;i++)
		{
			if(arry[i]>=0)
			{
				sprintf(DateTemp,"%8.3lf",arry[i]);
				u2_printf(DateTemp);
				u2_printf("\r\n");	
			}
			else
			{
				sprintf(DateTemp,"%9.3lf",arry[i]);
				u2_printf(DateTemp);
				u2_printf("\r\n");
			}	
		}

}









