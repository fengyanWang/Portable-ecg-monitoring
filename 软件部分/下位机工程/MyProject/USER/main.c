#include "delay.h"
#include "sys.h"
#include "bmp.h"
#include "function.h"
#include "usart.h"
#include "exti.h"
#include "led.h"
#include "hc05.h"
#include "usart2.h"
#include "malloc.h"	 
#include "mmc_sd.h"	

int main(void)
{		
	
	BspInit();//硬件初始化
	
	while(OLED_Show_HC05Status());//检查蓝牙是否连接成功
	
	while(1) 
	{	
		Display_Function();//心电数据显示
	}

}
