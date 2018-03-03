#include "key.h"
#include "delay.h"

/***********************************************
**º¯ÊýÃû³Æ£ºKEYÇý¶¯´úÂë
**ÊäÈë²ÎÊý£ºÎÞ
**·µ»ØÖµ£ºÎÞ
**ÆäËûËµÃ÷£ºKEY0--PC5 KEY1--PB0  KEY2--PB1
**×÷Õß£ºWFY
************************************************/
void KEY_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//Ê¹ÄÜPORTA,PORTCÊ±ÖÓ

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//¹Ø±Õjtag£¬Ê¹ÄÜSWD£¬¿ÉÒÔÓÃSWDÄ£Ê½µ÷ÊÔ
//KEY0	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ÉèÖÃ³ÉÉÏÀ­ÊäÈë
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//³õÊ¼»¯GPIOC5
//KEY1	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ÉèÖÃ³ÉÉÏÀ­ÊäÈë
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIOC5
//KEY2	 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;//PC5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //ÉèÖÃ³ÉÉÏÀ­ÊäÈë
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//³õÊ¼»¯GPIOC5
	
} 


/***********************************************
**º¯ÊýÃû³Æ£º°´¼ü´¦Àíº¯Êý
**ÊäÈë²ÎÊý£ºmode:0,²»Ö§³ÖÁ¬Ðø°´;1,Ö§³ÖÁ¬Ðø°´;
**·µ»ØÖµ£º·µ»Ø°´¼üÖµ
**ÆäËûËµÃ÷£º 0£¬Ã»ÓÐÈÎºÎ°´¼ü°´ÏÂ
			KEY0_PRES£¬KEY0°´ÏÂ
			KEY1_PRES£¬KEY1°´ÏÂ
			WKUP_PRES£¬WK_UP°´ÏÂ 
			×¢Òâ´Ëº¯ÊýÓÐÏìÓ¦ÓÅÏÈ¼¶,KEY0>KEY1>WK_UP!!
**×÷Õß£ºWFY
************************************************/
u8 KEY_Scan(void)
{
	if((KEY0==0)||(KEY1==0)||(KEY2==0))
	{
		delay_ms(10);
		if(KEY0==0)
		{
			while(!KEY0);
			return KEY0_PRES;
		}
		else if(KEY1==0)
		{
			while(!KEY1);
			return KEY1_PRES;
		}
		else if(KEY2==0)
		{
			while(!KEY2);
			return KEY2_PRES;
		}
		else
		{
			return 0;
		}
	}
}
//{	 
//	static u8 key_up=1;//°´¼ü°´ËÉ¿ª±êÖ¾
//	if(mode)key_up=1;  //Ö§³ÖÁ¬°´		  
//	if(key_up&&(KEY0==0||KEY1==0||KEY2==1))
//	{
//		delay_ms(10);//È¥¶¶¶¯ 
//		key_up=0;
//		if(KEY0==0)
//			return KEY0_PRES;
//		else if(KEY1==0)
//			return KEY1_PRES;
//		else if(KEY2==0)
//			return KEY2_PRES; 
//	}
//	else if(KEY0==1&&KEY1==1&&KEY2==1)
//		key_up=1; 	     
//	return 0;// ÎÞ°´¼ü°´ÏÂÂ
//}
