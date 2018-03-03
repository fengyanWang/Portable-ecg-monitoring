#include "ADS1293_Driver.h"

unsigned char	ADS1293_ECG_Array[9]	=	{0,0,0, 0,0,0, 0,0,0};

unsigned char	ADS1293_Error_Array[7]	=	{0,0,0, 0,0,0, 0};

ECG_DataTypeDef		ADS1293_ECG_CH1;
ECG_DataTypeDef		ADS1293_ECG_CH2;
ECG_DataTypeDef		ADS1293_ECG_CH3;

Package_TypeDef		ECG_CH1_Package;
Package_TypeDef		ECG_CH2_Package;
Package_TypeDef		ECG_CH3_Package;
Package_TypeDef		Reg_FeedBack_Package;

//采集到的数据
unsigned char ECGCh1[128];
unsigned char ECGCh2[128];
unsigned char ECGCh3[128];

//处理后的心电数据
double ECGDateCh1[128];
double ECGDateCh2[128];
double ECGDateCh3[128];

static int ECG_Count=0;
u8  ECGDateHandleOverFlag=0;//数据处理完成标志


unsigned char		ADS1293_Error_State			= 0;	//0:default, no errors find. 1:find errors
unsigned char		ADS1293_Error_Feedback_Flag	= 0;	//0:not need feedback. 1:need to feedback errors


unsigned char ADS1293_InitRegArray[ADS1293_RW_RegisterQuantity][2]	=	{ 	//5 electrode; 3-Lead
{0x00, 0x00},		//
{0x01, 0x25},		//Connects channel 1’s INP to IN4(LA) and INN to IN5(RA).
{0x02, 0x23},		//Connect channel 2’s INP to IN4(LA) and INN to IN3(LL).
{0x03, 0x31},		//Connects channel 3’s INP to IN6(Wilson) and INN to IN1(V1).
{0x04, 0x00},
{0x05, 0x00},
{0x06, 0x08},
{0x07, 0x1F},		//Enable Lead-off of IN5--IN1
{0x08, 0xff},		//Lead-off Detect Current is 2.040uA
{0x09, 0x00},
{0x0a, 0x1C},		//Enables the common-mode detector on input pins IN3(LL), IN4(LA) and IN5(RA).
{0x0b, 0x00},
{0x0c, 0x02},		//Connects the output of the RLD amplifier internally to pin IN2(RL).
{0x0d, 0x01},		//first buffer of the Wilson reference to the IN1 pin
{0x0e, 0x02},		//the second buffer to the IN2 pin
{0x0f, 0x03},		//the third buffer to the IN3 pin
{0x10, 0x01},		//Connects the output of the Wilson reference internally to IN6
{0x11, 0x00},
{0x12, 0x04},		//Uses external crystal and feeds the output of the internal oscillator module to the digital.
{0x13, 0x00},
{0x14, 0x00},
{0x15, 0x00},
{0x16, 0x00},
{0x17, 0x05},
{0x1F, 0x03},		//Digital High drive mode(default)
{0x21, 0x02},		//Configures the R2 decimation rate as 5 for all channels.
{0x22, 0x08},		//Configures the R3 decimation rate as 12 for channel 1.
{0x23, 0x08},		//Configures the R3 decimation rate as 12 for channel 2.
{0x24, 0x08}, 		//Configures the R3 decimation rate as 12 for channel 3.
{0x25, 0x00}, 		//CH1_R1=4; CH2_R1=4; CH3_R1=4;
{0x26, 0x00},
{0x27, 0x08},		//Configures the DRDYB source to ECG channel 1
{0x28, 0x00},
{0x29, 0x00},
{0x2a, 0x00},
{0x2e, 0x33},
{0x2f, 0x70},		//Enables ECG channel 1, ECG channel 2, and ECG channel 3 for loop read-back
};

/*******************************************************************************
* Function Name  : ADS1293_ResetControl
* Description    : 
* Input          : ResetState
* Output         : None
* Return         : None
*******************************************************************************/
void	ADS1293_ResetControl(unsigned char ResetState)
{
	if(ResetState == ADS1293_Reset_Enable)
		{
			GPIO_WriteBit(GPIOB, ADS1293_RESET, Bit_RESET);	
		}
	else
		{
			GPIO_WriteBit(GPIOB, ADS1293_RESET, Bit_SET); 
		}
		
	delay_us(10000);

}

/*******************************************************************************
* Function Name  : ADS1293_SPI_CS_Set
* Description    : According the value of cs_state to set SPI_CS signal state
* Input          : cs_state
* Output         : None
* Return         : None
*******************************************************************************/
void	ADS1293_SPI_CS_Set(unsigned char cs_state)
{
	if(cs_state == ADS1293_CS_LOW)
	{	GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);}
	else
	{	GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);	}	
}


/*******************************************************************************
* Function Name  : ADS1293_RegWrite
* Description    : 
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
unsigned char	ADS1293_RegWrite(unsigned char RegAddr, unsigned char RegValue)
{	
	unsigned char OperationState;

	ADS1293_SPI_CS_Set(ADS1293_CS_LOW);
	delay_us(2);
	
	SPI2_SendAndGet_Byte(RegAddr&0x7F);
	
	SPI2_SendAndGet_Byte(RegValue);
	
	delay_us(2);
	ADS1293_SPI_CS_Set(ADS1293_CS_HIGH);

	OperationState = TRUE;
	if(OperationState == TRUE)
		{return(TRUE);}
	else
		{return(FALSE);}	
}

/*******************************************************************************
* Function Name  : ADS1293_RegRead
* Description    : Read a regisger value of ADS1293, Just read one register
* Input          : register address
* Output         : None
* Return         : The Value of register
*******************************************************************************/
unsigned char	ADS1293_RegRead(unsigned char RegAddr)
{
	unsigned char	RegValue = 0x00;
	ADS1293_SPI_CS_Set(ADS1293_CS_LOW);
	delay_us(2);
			
	SPI2_SendAndGet_Byte(RegAddr | 0x80);
	RegValue	=	SPI2_SendAndGet_Byte(DummyByte);
	
	delay_us(2);
	ADS1293_SPI_CS_Set(ADS1293_CS_HIGH);

	return(RegValue);

}

/*******************************************************************************
* Function Name  : ADS1293_MultiRegRead
* Description    : Read multy regisgers value of ADS1293
* Input          : register address, register quantity, read buffer pointer
* Output         : None
* Return         : Operation State, TRUE or FALSE
*******************************************************************************/
unsigned char	ADS1293_MultiRegRead(unsigned char RegAddr, unsigned char Quantity, unsigned char * ReadBuf_pt)
{
	unsigned char	RegValue = 0x00;
	unsigned int	counter		= 0;
	
	ADS1293_SPI_CS_Set(ADS1293_CS_LOW);
	delay_us(1);
	
	SPI2_SendAndGet_Byte(RegAddr&0x7F);			//Send command and address
	
	for(counter = 0; counter <Quantity; counter++)
	{
		(*ReadBuf_pt)	=	SPI2_SendAndGet_Byte(DummyByte);
		ReadBuf_pt ++;
	}
		
	delay_us(1);
	ADS1293_SPI_CS_Set(ADS1293_CS_HIGH);

	return(RegValue);

}


/*******************************************************************************
* Function Name  : ADS1293_Read_ChipRevID
* Description    : Read revision ID value of ADS1293, Just read one register
* Input          : None
* Output         : None
* Return         : The Value of revision ID
*******************************************************************************/
unsigned int	ADS1293_Read_ChipRevID(void)
{
	unsigned int	RevID = 0;
	RevID	=	ADS1293_RegRead(REG_REVID_ADDR);

// Just For Debug
//	Reg_FeedBack_Package.Head_Index_Byte	=	PackageHeadID | PcakageIndex_REG;	
//	Reg_FeedBack_Package.High_Byte			=	REG_REVID_ADDR;
//	Reg_FeedBack_Package.Low_Byte			=	RevID;
//	Fill_TxPackage(Reg_FeedBack_Package, &USART3_TxBuffer);
	
	return(RevID);
}
/*******************************************************************************
* Function Name  : ADS1293_Init
* Description    : Inital ADS1293
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
unsigned char	ADS1293_Init(void)
{
	unsigned char	counter = 0x00;
//	unsigned char	ReadOut = 0x00;
	unsigned char	RegAddr = 0x00;
	unsigned char	RegValue = 0x00;

	ECG_CH1_Package.Head_Index_Byte	=	PackageHeadID | PcakageIndex_ECG_1ch;
	ECG_CH2_Package.Head_Index_Byte	=	PackageHeadID | PcakageIndex_ECG_2ch;
	ECG_CH3_Package.Head_Index_Byte	=	PackageHeadID | PcakageIndex_ECG_3ch;
	Reg_FeedBack_Package.Head_Index_Byte	=	PackageHeadID | PcakageIndex_REG;

	for(counter = 0x00; counter < ADS1293_RW_RegisterQuantity; counter ++)
		{
			RegAddr 	=	ADS1293_InitRegArray[counter][0];
			RegValue	=	ADS1293_InitRegArray[counter][1];
			ADS1293_RegWrite(RegAddr, RegValue);
			
// Just For Debug		
//			ReadOut = ADS1293_RegRead(ADS1293_InitRegArray[counter][0]);
//			Reg_FeedBack_Package.High_Byte	=	RegAddr;
//			Reg_FeedBack_Package.Low_Byte	=	ReadOut;
//			Fill_TxPackage(Reg_FeedBack_Package, &USART3_TxBuffer);			
		}

	return(SUCCESS);
}

/*******************************************************************************
* Function Name  : ADS1293_StartConversion
* Description    : Start ADS1293 conversion
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void	ADS1293_StartConversion(void)
{
	ADS1293_RegWrite(0x00, 0x01);	//Start Conversion
}


/*******************************************************************************
* Function Name  : ADS1293_StopConversion
* Description    : Stop ADS1293 conversion
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void	ADS1293_StopConversion(void)
{
	ADS1293_RegWrite(0x00, 0x00);	//Stop Conversion
}



/*******************************************************************************
* Function Name  : ADS1293_Handler
* Description    : ADS1293_Handler, read DRDYB and ALARM pins
* Input          : 
* Output         : None
* Return         : None
*******************************************************************************/
void	ADS1293_Handler(void)
{
	unsigned char	DRDYB_Pin_State;
	unsigned char	ALARM_Pin_State;
	unsigned char	counter = 0;
	double ECGCH1;
	double ECGCH2;
	double ECGCH3;

	DRDYB_Pin_State	=	GPIO_ReadInputDataBit(GPIOC, ADS1293_DRDYB);
	if(DRDYB_Pin_State)
		{
			//Read ECG Data from loop-back register
//			ADS1293_MultiRegRead(REG_DATA_LOOP_ADDR, 9, ADS1293_ECG_Array);
//			ADS1293_MultiRegRead(REG_DATA_LOOP_ADDR, 8, ADS1293_ECG_Array);	
			ADS1293_MultiRegRead(REG_DATA_CH1_ECG_H_ADDR, 9, ADS1293_ECG_Array);	
			
			ADS1293_ECG_CH1.H_Byte	=	ADS1293_ECG_Array[0];
			ADS1293_ECG_CH1.L_Byte	=	ADS1293_ECG_Array[1];

			ADS1293_ECG_CH2.H_Byte	=	ADS1293_ECG_Array[3];
			ADS1293_ECG_CH2.L_Byte	=	ADS1293_ECG_Array[4];

			ADS1293_ECG_CH3.H_Byte	=	ADS1293_ECG_Array[6];
			ADS1293_ECG_CH3.L_Byte	=	ADS1293_ECG_Array[7];

			ECG_CH1_Package.High_Byte	=	ADS1293_ECG_Array[0];
			ECG_CH1_Package.Low_Byte	=	ADS1293_ECG_Array[1];

			ECG_CH2_Package.High_Byte	=	ADS1293_ECG_Array[3];
			ECG_CH2_Package.Low_Byte	=	ADS1293_ECG_Array[4];

			ECG_CH3_Package.High_Byte	=	ADS1293_ECG_Array[6];
			ECG_CH3_Package.Low_Byte	=	ADS1293_ECG_Array[7];

			ECGCh1[ECG_Count]=(ADS1293_ECG_CH1.H_Byte<<8)+(ADS1293_ECG_CH1.L_Byte);
			ECGCh2[ECG_Count]=(ADS1293_ECG_CH2.H_Byte<<8)+(ADS1293_ECG_CH2.L_Byte);
			ECGCh3[ECG_Count]=(ADS1293_ECG_CH3.H_Byte<<8)+(ADS1293_ECG_CH3.L_Byte);
			
			ECGCH1=(ECGCh1[ECG_Count]-4194304)*0.000163487;
			ECGCH2=(ECGCh2[ECG_Count]-4194304)*0.000163487;
			ECGCH3=(ECGCh3[ECG_Count]-4194304)*0.000163487;
			
			ECGDateCh1[ECG_Count]=ECGCH1;
			ECGDateCh2[ECG_Count]=ECGCH2;
			ECGDateCh3[ECG_Count]=ECGCH3;
				
			ECG_Count++;
			if(ECG_Count==127)
			{
				ECG_Count=0;
				ECGDateHandleOverFlag=1;//一帧数据处理完成
				
			}
			
		}

	ALARM_Pin_State	=	GPIO_ReadInputDataBit(GPIOC, ADS1293_ALARMB);	
	if(ALARM_Pin_State == 0x00)
		{
		ADS1293_Error_State = 1;
		if(ADS1293_Error_Feedback_Flag)
			{
			ADS1293_Error_Feedback_Flag = 0;
			delay_us(10);
			ADS1293_MultiRegRead(REG_ERROR_LOD, 7, ADS1293_Error_Array);
			for(counter = 0; counter <7; counter++)
				{
				Reg_FeedBack_Package.High_Byte	=	(REG_ERROR_LOD + counter);
				Reg_FeedBack_Package.Low_Byte	=	ADS1293_Error_Array[counter];
				Fill_TxPackage(Reg_FeedBack_Package, &USART3_TxBuffer);
				}					
			}					
		}
	else
		{
		ADS1293_Error_State = 0;
		}
}










