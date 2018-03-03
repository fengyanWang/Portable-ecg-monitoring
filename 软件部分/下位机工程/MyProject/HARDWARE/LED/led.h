#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "delay.h"

#define LED1 PAout(8)//PA8
#define LED2 PAout(11)//PA11
#define LED3 PAout(12)//PA12


void led_Init(void);//LED函数初始化声明
void Set_LED_Status(u8 led1_status,u8 led2_status,u8 led3_status,
	int count1,int count2,int count3,
		int time1,int time2,int time3);
void WaterLights(void);

		 				    
#endif
