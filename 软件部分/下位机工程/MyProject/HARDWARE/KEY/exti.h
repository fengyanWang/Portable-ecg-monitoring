#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"
#include "stm32f10x_exti.h"
#include "function.h"
#include "led.h"

#define DATE_TEMP_FLAG  0  //时间温度切换显示
#define ECG_HEARTRATE_FLAG 1	//心电波形和心率切换显示
#define OTHER_FLAG 2	//心电波形和心率切换显示
#define ECGDATEHANDLE 3  //数据处理

static int Key0_Count;
static int ECG_Count;
extern int Key0_Flag;
extern int ECG_Count_Flag;

void EXTIX_Init(void);//IO初始化
u8 Key_Function(void);
void Display_Function(void);
		 					    
#endif

