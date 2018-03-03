#include "stm32f10x_init.h"



/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//使能APB2上GPIOA外设的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//使能APB2上GPIOB外设的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	//Config PC.7 as ADS1293_DRDYB signal, input
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure); 

	//Config PC.8 as ADS1293_ALARMB signal, input
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPU;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

//	//Config PB.1 as ADS1293_RESET signal, Output
//	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configures the UART interface.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/*------------Clock configurations------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能APB2上GPIOB外设的时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//使能APB1上USART3外设的时钟

	/*------------Pins configurations------------*/
	/* Configure USART3 Tx (PB10) as alternate function open-drain */
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	/* Configure USART3 Rx (PB11) as input floating */
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	/* Configure (PB12) as UART_RX_ACTIVE input floating */
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	/* Configure (PB13) as USART3_CTS input floating */
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	/* Configure (PB14) as USART3_RTS alternate function open-drain */
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_10MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure); 

	/*------------USART Controller configurations------------*/
  USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate 		= 115200;						//  9600
	USART_InitStructure.USART_WordLength 	= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 		= USART_StopBits_1;
	USART_InitStructure.USART_Parity 		= USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode 			= USART_Mode_Tx | USART_Mode_Rx;
	USART_Init(USART3, &USART_InitStructure);			//Configure the USART3

	/* Enable the USART3 RX buffer Non-Empty Interrupt */
  	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
  	USART_Cmd(USART3, ENABLE); 							//Enable USART3 
		               
}

/*******************************************************************************
* Function Name  : SPI_Configuration
* Description    : Configures the SPI interface.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef   SPI_InitStructure;

/* -----------------------------SPI2 Config --------------------------------*/
	//使能APB2上SPI2外设的时钟,GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	// Configure SPI2 pins: PB.13->SCK, PB.14->MISO, PB.15->MOSI 
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
   	
	//Config PC.6->SPI_CS signal
	GPIO_InitStructure.GPIO_Pin		=	GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed 	= 	GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= 	GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);

	// SPI2 Config -------------------------------------------------------------
	SPI_InitStructure.SPI_Direction		= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode			= SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize		= SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL 			= SPI_CPOL_Low;				//Capture polarity = 0, means sclk pin asserted as low, when bus is free
	SPI_InitStructure.SPI_CPHA 			= SPI_CPHA_1Edge;			//Capture Phase	= 1,
	SPI_InitStructure.SPI_NSS 			= SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;	//
	SPI_InitStructure.SPI_FirstBit 		= SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI2, &SPI_InitStructure);
	
	/* Enable SPI2 */
	SPI_Cmd(SPI2, ENABLE);

}

/*******************************************************************************
* Function Name  : TIMER_Configuration
* Description    : Configures the Timer.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIMER_Configuration(void)
{
	/* STM32F103RBT6 have 4 timers, Timer1 -- Timer4.
		Timer1 is advanced-control timer;
		Timer2 - Timer4 are general purpose timer	*/	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* -----------------------------Clock Enable --------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//Enable Clock source of Timer4
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//Enable Clock source of Timer2
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//Enable Clock source of Timer3	
	/* -----------------------------Clock Reserved --------------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//Enable Clock source of Timer1	
	*/
	///////////////////////////////////////////////////////////////////////////////////////
	/* Timer2 Configuration	*/
	//Timer2 used for detect EXTI
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Prescaler			=	(72 - 1);				//Timer2 输入时钟 72MHz/(72) = 1MHz; Period = 1us
	TIM_TimeBaseStructure.TIM_Period				=	1172;						//1us * 1172 = 1.172 ms
	TIM_TimeBaseStructure.TIM_ClockDivision			=	TIM_CKD_DIV1;			//TDTS = 1Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode			=	TIM_CounterMode_Up;		//TIM 向上计数模式	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM2, TIM_FLAG_Update);			//Clear interrupt flag
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		//Enable interrupt
	TIM_Cmd(TIM2, ENABLE);

	/* Timer3 Configuration	*/
	//Timer3 used for creat 20Hz error report frequency
	TIM_TimeBaseStructure.TIM_Prescaler			    =	(72 - 1);				//Timer2 输入时钟 72MHz/(72) = 1MHz; Period = 1us
	TIM_TimeBaseStructure.TIM_Period				=	50000;					//1us * 50000 = 50 ms , 20Hz
	TIM_TimeBaseStructure.TIM_ClockDivision			=	TIM_CKD_DIV1;			//TDTS = 1Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode			=	TIM_CounterMode_Up;		//TIM 向上计数模式	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);			//Clear interrupt flag
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);		//Enable interrupt
	TIM_Cmd(TIM3, ENABLE);
		
}

/*******************************************************************************
* Function Name  : EXIT_Configuration
* Description    : Configures the EXIT.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXIT_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);			//使能APB2上AFIO 时钟

	//EXIT_Line0 configuration
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 		//外部中断管脚选择GPIOA.0
	EXTI_ClearITPendingBit(EXTI_Line0);								//清除 EXTI Line0线路挂起位
	EXTI_InitStruct.EXTI_Line 		= EXTI_Line0; 					//选择Line0
	EXTI_InitStruct.EXTI_Mode 		= EXTI_Mode_Interrupt ;			//中断请求
	EXTI_InitStruct.EXTI_Trigger 	= EXTI_Trigger_Rising_Falling;	//设置输入线路上升沿和下降沿为中断请求
	EXTI_InitStruct.EXTI_LineCmd 	= ENABLE;
	EXTI_Init(&EXTI_InitStruct);
	
	//EXIT_Line1 configuration
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource1); 		//外部中断管脚选择GPIOA.1
	EXTI_ClearITPendingBit(EXTI_Line1);								//清除 EXTI Line1线路挂起位
	EXTI_InitStruct.EXTI_Line 		= EXTI_Line1; 					//选择Line1
	EXTI_InitStruct.EXTI_Mode 		= EXTI_Mode_Interrupt ;			//中断请求
	EXTI_InitStruct.EXTI_Trigger 	= EXTI_Trigger_Rising_Falling;	//设置输入线路上升沿和下降沿为中断请求
	EXTI_InitStruct.EXTI_LineCmd 	= ENABLE;
	EXTI_Init(&EXTI_InitStruct);

	//EXIT_Line4 configuration
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource4); 		//外部中断管脚选择GPIOC.4
	EXTI_ClearITPendingBit(EXTI_Line4);								//清除 EXTI Line4线路挂起位
	EXTI_InitStruct.EXTI_Line 		= EXTI_Line4; 					//选择Line4
	EXTI_InitStruct.EXTI_Mode 		= EXTI_Mode_Interrupt ;			//中断请求
	EXTI_InitStruct.EXTI_Trigger 	= EXTI_Trigger_Rising_Falling;	//设置输入线路上升沿和下降沿为中断请求
	EXTI_InitStruct.EXTI_LineCmd 	= ENABLE;
	EXTI_Init(&EXTI_InitStruct);

	//EXIT_Line5 configuration
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5); 		//外部中断管脚选择GPIOB.5
	EXTI_ClearITPendingBit(EXTI_Line5);								//清除 EXTI Line5线路挂起位
	EXTI_InitStruct.EXTI_Line 		= EXTI_Line5; 					//选择Line5
	EXTI_InitStruct.EXTI_Mode 		= EXTI_Mode_Interrupt ;			//中断请求
	EXTI_InitStruct.EXTI_Trigger 	= EXTI_Trigger_Rising_Falling;	//设置输入线路上升沿和下降沿为中断请求
	EXTI_InitStruct.EXTI_LineCmd 	= ENABLE;
	EXTI_Init(&EXTI_InitStruct);
}





