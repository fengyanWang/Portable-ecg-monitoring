#include "oled.h"
#include "stdlib.h" 	 
#include "delay.h"
#include "oledfont.h" 

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
u8 OLED_GRAM[128][8];	
/***********************************************
**函数名称：IIC启动代码
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void IIC_Start(void)
{

	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
	
}


/***********************************************
**函数名称：IIC停止代码
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void IIC_Stop(void)
{
	
	OLED_SCLK_Set() ;
//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

/***********************************************
**函数名称：IIC等待応答信号
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void IIC_Wait_Ack(void)
{

	OLED_SCLK_Set();
	OLED_SCLK_Clr();
	
}

/***********************************************
**函数名称：IIC Write byte
**输入参数：IIC_Byte：待写入的字节
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
		}


}

/***********************************************
**函数名称：IIC Write Command
**输入参数：IIC_Command：待写入的命令
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
   IIC_Stop();
}

/***********************************************
**函数名称：IIC Write Data
**输入参数：IIC_Data：待写入的数据
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
   IIC_Stop();
}

/***********************************************
**函数名称：OLED写入数据或者命令函数
**输入参数：dat：待写入的数据   cmd：待写入的命令
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
			{

			Write_IIC_Data(dat);
   
		}
	else {
   Write_IIC_Command(dat);
		
	}


}



/***********************************************
**函数名称：OLED显示图片
**输入参数：fill_Data：图片数据
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}



/***********************************************
**函数名称：延时50毫秒函数
**输入参数：Del_50ms
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

/***********************************************
**函数名称：延时1毫秒函数
**输入参数：Del_1ms
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}


/***********************************************
**函数名称：坐标设置函数
**输入参数：x,y坐标
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  

/***********************************************
**函数名称：开启OLED显示
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

/***********************************************
**函数名称：关闭OLED显示 
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 

/***********************************************
**函数名称：清屏函数 
**输入参数：无
**返回值：无
**其他说明：清完屏,整个屏幕是黑色的!和没点亮一样!!!
**作者：WFY
************************************************/
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}

/***********************************************
**函数名称：点亮OLED
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //更新显示
}

/***********************************************
**函数名称：在指定位置显示一个字符,包括部分字符
**输入参数：坐标：x:0~127  y:0~63  字符：chr：显示字符  Char_Size：字符大小
**返回值：无
**其他说明：mode:0,反白显示;1,正常显示	size:选择字体 16/12 
**作者：WFY
************************************************/
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//得到偏移后的值			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}

/***********************************************
**函数名称：m^n函数
**输入参数：u8 m,u8 n
**返回值：算术得出的值
**其他说明：无
**作者：WFY
************************************************/
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
 
/***********************************************
**函数名称：显示2个数字
**输入参数：x,y :起点坐标 len :数字的位数  size2:字体大小	  num:数值(0~4294967295);
**返回值：算术得出的值
**其他说明：无
**作者：WFY
************************************************/
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 


void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

/***********************************************
**函数名称：显示汉字
**输入参数：x,y :起点坐标 len :数字的位数  size2:字体大小	  num:数值(0~4294967295);
**返回值：算术得出的值
**其他说明：无
**作者：WFY
************************************************/
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
  for(t=0;t<16;t++)
	{
		OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
		adder+=1;
    }	
	OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
	{	
		OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
		adder+=1;
    }					
}

/***********************************************
**函数名称：显示显示BMP图片128×64
**输入参数：起始点坐标(x,y),x的范围0～127 y为页的范围0～7
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

//更新显存到LCD		 
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=2;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}


//x1,y1,x2,y2 填充区域的对角坐标
//确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,清空;1,填充	  
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
	u8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//更新显示
}


//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空				   
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;
	OLED_Refresh_Gram();//更新显示
		
}

	
/***********************************************
**函数名称：初始化OLED
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_Init(void)
{ 	 	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能A端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;	 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化GPIOD3,6
 	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11);	


	delay_ms(200);

	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	
	OLED_Clear();
}  
/***********************************************
**函数名称：OLED画线函数
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)
{
	double k,b;
	int i=0;
	double y;
	k=(y2-y1)*1.0/(x2-x1);
	b=y1-k*x1;
	for(i=x1;i<=x2;i++)
	{
		y=k*i+b;
		OLED_DrawPoint(i,y,dot);
	}	
}

/***********************************************
**函数名称：OLED显示蓝牙连接状态
**输入参数：无
**返回值：无
**其他说明：无
**作者：WFY
************************************************/
u8 OLED_Show_HC05Status(void)
{
	u8 t;
	t=HC05_Sta_Show();
	if(t==1)//蓝牙连接成功
	{
		OLED_ShowCHinese(8,3,29);//蓝
		OLED_ShowCHinese(26,3,30);//牙
		OLED_ShowCHinese(44,3,31);//连
		OLED_ShowCHinese(62,3,32);//接
		OLED_ShowCHinese(80,3,33);//成
		OLED_ShowCHinese(98,3,34);//功
		OLED_ShowCHinese(116,3,35);//!
		return 0;
		
	}
	else//蓝牙连接未成功
	{
		
		OLED_ShowCHinese(8,3,29);//蓝
		OLED_ShowCHinese(26,3,30);//牙
		OLED_ShowCHinese(44,3,31);//连
		OLED_ShowCHinese(62,3,32);//接
		OLED_ShowCHinese(80,3,36);//失
		OLED_ShowCHinese(98,3,37);//败
		OLED_ShowCHinese(116,3,35);//!
		One_Long_Three_Short();
		return 1;
	}
}


























