#ifndef __FUNCTION_H
#define __FUNCTION_H	


#include "stm32f10x.h"
#include "oled.h"
#include "rtc.h" 
#include "delay.h"
#include "ds18b20.h"
#include "key.h"
#include "beep.h"
#include "math.h"
#include "usart.h"
#include "exti.h"
#include "mmc_sd.h"	
#include "spi.h"
#include "ADS1293_Driver.h"
#include "stm32f10x_init.h"
#include "usart2.h"
#include "DateProce.h"

extern double ECGArry[1280];
extern double ECGArry1[1280];
extern double ECGArry2[1280];

extern unsigned int Leads[];




void ElectrodeOff(void);
void OLED_Show_Frame(void);
void OLED_ShowDate(void);
void OLED_ShowDate1(void);
void OLED_Show_Temp(void);
void OLED_Show_Temp1(void);
void OLED_Show_Date_Temp(int time);
void OLED_Plot_ECG(void);
void OLED_Plot_ECG1(void);
void OLED_Plot_ECG2(void);
void OLED_ShowCoordinate(int num);
void Max_Min(const double* arry,double* max,double* min,int len);
void OLED_Show_HeartRate(void);
void OLED_Show_ECG_HeartRate(int time);
void Display1_Function(void);

void BspInit(void);
void ECGDate_Handle(void);
u8 ElectrodeDetection(unsigned int* leadarry);


#endif  


