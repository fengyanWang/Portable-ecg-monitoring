#ifndef __BEEP_H
#define __BEEP_H
#include "sys.h"

#define BEEP PCout(13)//PC13

void Beep_Init(void);//蜂鸣器初始化函数声明

void One_Long_One_Short(void);//一长一短

void One_Long_Two_Short(void);//一长两短

void One_Long_Three_Short(void);//一长三短

void One_Long_Four_Short(void);//一长四短

void Two_Long_Two_Short(void);//两长两短




#endif


