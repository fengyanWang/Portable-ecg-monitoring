#include "function.h"


int Key0_Flag=0;
static int Key1_Count=0;
static int Key2_Count=0;
static int lineCount=0;

extern  u8  ECGDateHandleOverFlag;


/***********************************************
**函数名称：电极脱落OLED报警电极脱落
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void ElectrodeOff()
{
	OLED_ShowCHinese(24,3,38);//电
	OLED_ShowCHinese(42,3,39);//极
	OLED_ShowCHinese(60,3,40);//脱
	OLED_ShowCHinese(78,3,41);//落
	OLED_ShowCHinese(96,3,42);//！
	
	Two_Long_Two_Short();
}



/***********************************************
**函数名称：OLED显示界面的框架
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Show_Frame()
{
		OLED_ShowCHinese(0,0,4);//心
		OLED_ShowCHinese(21,0,5);//电
		OLED_ShowCHinese(42,0,6);//监
		OLED_ShowCHinese(63,0,7);//测
		OLED_ShowCHinese(84,0,8);//系
		OLED_ShowCHinese(105,0,9);//统
		OLED_ShowCHinese(0,6,10);//郑
		OLED_ShowCHinese(16,6,12);//大
		OLED_ShowCHinese(32,6,14);//电
		OLED_ShowCHinese(48,6,15);//气
		OLED_ShowCHinese(64,6,16);//工
		OLED_ShowCHinese(80,6,17);//程
		OLED_ShowCHinese(96,6,18);//学
		OLED_ShowCHinese(112,6,19);//院
}

/***********************************************
**函数名称：OLED显示当前的时间
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_ShowDate()
{
	
	while(RTC_Init())		//RTC初始化	，一定要初始化成功
	{ 
		delay_ms(800);
		OLED_Clear();
		OLED_ShowString(16,2,"RTC Error!!!",16);
		One_Long_One_Short();
	}	

	OLED_Show_Frame();
	OLED_ShowString(0,2,"Date:",16);
	OLED_ShowNum(48,2,calendar.w_year,4,12);
	OLED_ShowChar(72,2,'-',12);
	OLED_ShowNum(76,2,calendar.w_month,2,12);
	OLED_ShowChar(88,2,'-',12);
	OLED_ShowNum(92,2,calendar.w_date,2,12);
	
	OLED_ShowNum(48,3,calendar.hour,2,12);
	OLED_ShowChar(60,3,':',12);
	OLED_ShowNum(64,3,calendar.min,2,12);
	OLED_ShowChar(76,3,':',12);
	OLED_ShowNum(80,3,calendar.sec,2,12);
	
}

/***********************************************
**函数名称：OLED显示当前的时间
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_ShowDate1()
{
	
	while(RTC_Init())		//RTC初始化	，一定要初始化成功
	{ 
		delay_ms(800);
		OLED_Clear();
		OLED_ShowString(0,2,"RTC Error!!!",16);
		One_Long_One_Short();
	}	

	OLED_ShowString(0,2,"Date:",16);
	OLED_ShowNum(48,2,calendar.w_year,4,12);
	OLED_ShowChar(72,2,'-',12);
	OLED_ShowNum(76,2,calendar.w_month,2,12);
	OLED_ShowChar(88,2,'-',12);
	OLED_ShowNum(92,2,calendar.w_date,2,12);
	
	OLED_ShowNum(48,3,calendar.hour,2,12);
	OLED_ShowChar(60,3,':',12);
	OLED_ShowNum(64,3,calendar.min,2,12);
	OLED_ShowChar(76,3,':',12);
	OLED_ShowNum(80,3,calendar.sec,2,12);
	
}
/***********************************************
**函数名称：OLED显示当前的温度
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Show_Temp()
{
	static int num=0;
	char Date[30];
	double t;
	while(DS18B20_Init())	//DS18B20初始化	
	{
		num++;
		OLED_Clear();
		OLED_ShowString(0,2,"DS18B20 Error!!!",16);
		One_Long_Two_Short();
		if(num==3)
		{
			num=0;
			break;
		}
	}
	
	temperature=DS18B20_Get_Temp();
	t=temperature/10+(temperature%10)*0.1;
	sprintf(Date,"%7.1lf",t);
	u2_printf("T  :");
	u2_printf("\r\n");
	u2_printf(Date);
	u2_printf("\r\n");
	
	
	
	OLED_Show_Frame();
	OLED_ShowString(0,2,"Temp:",16);
	OLED_ShowNum(48,2,temperature/10,2,16);
	OLED_ShowChar(64,2,'.',16);
	OLED_ShowNum(72,2,temperature%10,1,16);
	OLED_ShowCHinese(90,2,20);
	OLED_ShowChar(100,2,'C',16);		
}

/***********************************************
**函数名称：OLED显示当前的温度
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Show_Temp1()
{
	static int num=0;
	char Date[30];
	double t;
	while(DS18B20_Init())	//DS18B20初始化	
	{
		num++;
		OLED_Clear();
		OLED_ShowString(0,2,"DS18B20 Error!!!",16);
		One_Long_Two_Short();
		if(num==3)
		{
			num=0;
			break;
		}
	}
	
	temperature=DS18B20_Get_Temp();
	t=temperature/10+(temperature%10)*0.1;
	sprintf(Date,"%7.1lf",t);
	u2_printf("T  :");
	u2_printf("\r\n");
	u2_printf(Date);
	u2_printf("\r\n");
	
	OLED_ShowString(0,2,"Temp:",16);
	OLED_ShowNum(48,2,temperature/10,2,16);
	OLED_ShowChar(64,2,'.',16);
	OLED_ShowNum(72,2,temperature%10,1,16);
	OLED_ShowCHinese(90,2,20);
	OLED_ShowChar(100,2,'C',16);		
}



/***********************************************
**函数名称：OLED显示当前的时间和温度
**输入参数：time:延时时间
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Show_Date_Temp(int time)
{
		OLED_Clear();	
		OLED_ShowDate();
		delay_ms(time);
		delay_ms(time);
		delay_ms(time);
		delay_ms(time);
		OLED_Clear();
		OLED_Show_Temp();
		delay_ms(time);
		delay_ms(time);
		OLED_Clear();
}
/***********************************************
**函数名称：OLED显示坐标
**输入参数：time:延时时间
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_ShowCoordinate(int num)
{
	OLED_ShowCHinese(10,0,21);//心
	OLED_ShowCHinese(34,0,22);//电
	OLED_ShowCHinese(58,0,23);//波
	OLED_ShowCHinese(82,0,24);//形
	OLED_ShowNum(116,0,num,1,16);
	OLED_Fill(0,0,127,0,1);//x轴	
	OLED_Fill(0,0,0,47,1);//y轴
}


/***********************************************
**函数名称：OLED显示心电波形0
**输入参数：time:延时时间
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Plot_ECG()
{
	int x=0;
	int y=0;
	int i=0,j=0;
	u8 t=0;
	int tempArry[128];
	static int count=0;
	static int ECGcount=0;
	double max,min,offset;
	OLED_ShowCoordinate(1);
	Max_Min(ECGArry,&max,&min,1280);
	if(min<0)
	{
		offset=-min;
	}
	else
	{
		offset=0;
	}
	
	for(i=0;i<1280;i++)
	{
		x=i-count*128+2;
		y=((ECGArry[i]+offset)/(max-min))*45+8;
		tempArry[i-count*128]=y;
		OLED_DrawPoint(x,y,1);
		if((i+1)%128==0)
		{
			
			for(j=0;j<128;j++)
			{
				OLED_DrawPoint(j+2,tempArry[j],0);
			}
			count++;
			t=KEY_Scan();
			if(t==KEY1_PRES)
			{
				ECGcount++;
			}
			if(ECGcount%4==0)
			{
				;
			}
			else if(ECGcount%4==1)
			{
				OLED_Clear();
				OLED_Plot_ECG1();
				break;
			}
			else if(ECGcount%4==2)
			{
				OLED_Clear();
				OLED_Plot_ECG2();
				count=0;
				break;
			}
			else
			{
				OLED_Clear();
				count=0;
				break;
			}
			
		}
	}
	count=0;	
}

/***********************************************
**函数名称：OLED显示心电波形1
**输入参数：time:延时时间
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Plot_ECG1()
{
	int x=0;
	int y=0;
	int i=0,j=0;
	u8 t;
	int tempArry[128];
	static int count=0;
	static int ECGcount1=0;
	double max,min,offset;
	OLED_ShowCoordinate(2);
	Max_Min(ECGArry1,&max,&min,1280);
	if(min<0)
	{
		offset=-min;
	}
	else
	{
		offset=0;
	}
	for(i=0;i<1280;i++)
	{
		x=i-count*128+2;
		y=((ECGArry1[i]+offset)/(max-min))*45+8;
		tempArry[i-count*128]=y;
		OLED_DrawPoint(x,y,1);
		if((i+1)%128==0)
		{
			for(j=0;j<128;j++)
			{
				OLED_DrawPoint(j+2,tempArry[j],0);
			}
			count++;
			t=KEY_Scan();
			if(t==KEY1_PRES)
			{
				ECGcount1++;
			}
			if(ECGcount1%2==0)
			{
				;
			}
			else 
			{
				count=0;
				OLED_Clear();
				OLED_Plot_ECG2();
				break;
			}
		}
	}
	count=0;	
}

/***********************************************
**函数名称：OLED显示心电波形2
**输入参数：time:延时时间
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Plot_ECG2()
{
	int x=0;
	int y=0;
	int i=0,j=0;
	u8 t;
	int tempArry[128];
	static int count=0;
	static int ECGcount2=0;
	double max,min,offset;
	OLED_ShowCoordinate(3);
	Max_Min(ECGArry2,&max,&min,1280);
	if(min<0)
	{
		offset=-min;
	}
	else
	{
		offset=0;
	}
	for(i=0;i<1280;i++)
	{
		x=i-count*128+2;
		y=((ECGArry2[i]+offset)/(max-min))*45+8;
		tempArry[i-count*128]=y;
		OLED_DrawPoint(x,y,1);
		if((i+1)%128==0)
		{
			for(j=0;j<128;j++)
			{
				OLED_DrawPoint(j+2,tempArry[j],0);
			}
			count++;
			t=KEY_Scan();
			if(t==KEY1_PRES)
			{
				ECGcount2++;
			}
			if(ECGcount2%2==0)
			{
				;
			}
			else 
			{
				count=0;
				OLED_Clear();
				OLED_Plot_ECG();
			}
		}
	}
	count=0;	
}
/***********************************************
**函数名称：OLED显示心率
**输入参数：time:延时时间
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Show_HeartRate()
{
	OLED_ShowCHinese(16,0,25);//心
	OLED_ShowCHinese(40,0,26);//率
	OLED_ShowCHinese(64,0,27);//显
	OLED_ShowCHinese(88,0,28);//示
	
	OLED_ShowCHinese(8,4,25);//心
	OLED_ShowCHinese(32,4,26);//率
	
	OLED_ShowChar(50,4,':',16);
	
	OLED_ShowNum(68,4,75,2,16);
	
	OLED_ShowString(96,4,"bpm",16);
	
}
/***********************************************
**函数名称：OLED显示心率和心电波形
**输入参数：time:延时时间
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Show_ECG_HeartRate(int time)
{
	int x=0;
	int y=0;
	int i=0,j=0;
	int tempArry[128];
	static int count=0;
	double max,min,offset;
	OLED_ShowCoordinate(1);
	Max_Min(ECGArry,&max,&min,1280);
	if(min<0)
	{
		offset=-min;
	}
	else
	{
		offset=0;
	}

	for(i=0;i<1280;i++)
	{
		
		x=i-count*128+2;
		y=((ECGArry[i]+offset)/(max-min))*45+8;
		tempArry[i-count*128]=y;
		OLED_DrawPoint(x,y,1);
		if((i+1)%128==0)
		{
			for(j=0;j<128;j++)
			{
				OLED_DrawPoint(j+2,tempArry[j],0);
			}
			OLED_Clear();
			OLED_Show_HeartRate();
			delay_ms(time);
			OLED_Clear();
			count++;
			if((Key0_Flag%4)!=1)
			{
				OLED_Clear();
				count=0;
				break;
			}
			OLED_ShowCoordinate(1);
		}
	}
	count=0;
}


/***********************************************
**函数名称：找数组中最大值和最小值
**输入参数：arry：数组  max：最大值 min：最小值 len：数组长度
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void Max_Min(const double* arry,double* max,double* min,int len)
{
	int i=0;
	
	*max=arry[0];
	*min=arry[0];
	
	for(i=0;i<len;i++)
	{
		if(arry[i]>*max)
		{
			*max=arry[i];
		}
	}
	
	for(i=0;i<len;i++)
	{
		if(arry[i]<*min)
		{
			*min=arry[i];
		}
	}	
}
/***********************************************
**函数名称：根据按键显示相应的窗口
**输入参数：无
**返回值：
**其他说明：无
**作者：WFY
************************************************/
void Display1_Function()
{
	u8 KeyValue=KEY_Scan();
	
	switch(KeyValue)
	{
		case KEY1_PRES:
		{
			Key1_Count++;
			if(Key1_Count%2==0)
			{
				OLED_Clear();
				OLED_ShowDate1();
				break;
			}
			else
			{
				OLED_Clear();
				OLED_Show_Temp1();
				break;
			}
		}
		case KEY2_PRES:
		{
			Key2_Count++;
			if(Key2_Count%2==0)
			{
				OLED_Clear();
				OLED_Plot_ECG();
				break;
			}
			else
			{
				OLED_Clear();
				OLED_Show_HeartRate();
				break;
			}
		}
	}
}

/***********************************************
**函数名称：系统的硬件资源初始化
**输入参数：无
**返回值：
**其他说明：无
**作者：WFY
************************************************/
void BspInit()
{
	delay_init();	    	 //延时函数初始化	
	uart_init(9600);		//串口1初始化波特率为9600
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
	OLED_Init();			//初始化OLED  
	Beep_Init();			//初始化蜂鸣器
	led_Init();				//初始化LED
	EXTIX_Init();			//初始化外部中断
	
	HC05_Init(); 			//初始化蓝牙
	
	SPI3_Init();			//初始化SD卡的SPI接口
	SD_Initialize();	//初始化SD卡
	
	SPI_Configuration();//ADS1293  spi接口初始化
	TIMER_Configuration();//初始化定时器
	ADS1293_ResetControl(ADS1293_Reset_Disable);		//Release reset pin, assert it as high
	ADS1293_Init();//ADS1293初始化
	
	while(ElectrodeDetection(Leads));
	
	
	ADS1293_StartConversion();//开始ADS1293数据采集
}

/***********************************************
**函数名称：心电数据的采集与发送和写SD卡
**输入参数：无
**返回值：
**其他说明：无
**作者：WFY
************************************************/
void ECGDate_Handle()
{
	ADS1293_Handler();//心电数据处理
//	if(ECGDateHandleOverFlag==1)//一帧数据处理完成
	if(1)	
	{
			
//蓝牙发送数据部分		
		ECGDateHandleOverFlag=0;
		u2_printf("\r\n");
		u2_printf("ECGCh1:");
		u2_printf("\r\n");
		HC05_SendDate(ECGArry,lineCount,128);//蓝牙发送通道1的数据
		u2_printf("\r\n");
		u2_printf("ECGCh2:");
		u2_printf("\r\n");
		HC05_SendDate(ECGArry1,lineCount,128);//蓝牙发送通道2的数据
		u2_printf("\r\n");
		u2_printf("ECGCh3:","\r\n");
		u2_printf("\r\n");
		HC05_SendDate(ECGArry2,lineCount,128);//蓝牙发送通道3的数据
		u2_printf("\r\n");
		lineCount++;
//SD卡写数据部分
		SD_WriteDisk((u8*)ECGArry,lineCount,lineCount);
		SD_WriteDisk((u8*)ECGArry1,lineCount,lineCount);
		SD_WriteDisk((u8*)ECGArry2,lineCount,lineCount);
		if(lineCount==9)
		{
			lineCount=0;
		}
	}	
}
//电极检测函数
u8 ElectrodeDetection(unsigned int* leadarry)
{
	int i=0;
	for(i=0;i<5;i++)
	{
		if(leadarry[i]==0)
		{
			ElectrodeOff();
			return 1;
		}
	}
	return 0;
}


