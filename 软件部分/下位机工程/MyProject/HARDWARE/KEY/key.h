#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
	 

#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//读取按键2 
 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define KEY2_PRES	3		//KEY2  

void KEY_Init(void);//按键驱动函数声明
u8 KEY_Scan(void);  	//按键扫描函数声明


#endif
