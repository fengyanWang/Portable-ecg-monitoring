#include "SPI_UserDriver.h"



unsigned char SPI2_BusyReg = 0x00;			//0:means SPI2 is free; 1 or other value: means SPI2 is busy
unsigned char SPI2_WorkDescription[5];		//Record who is using SPI2, It valid only when SPI2_BusyReg not equal to 0;


/*******************************************************************************
* Function Name  : SPI2_CS_Set
* Description    : According the value of cs_state to set SPI1_CS signal state
* Input          : cs_state
* Output         : None
* Return         : None
*******************************************************************************/
void	SPI2_CS_Set(unsigned char cs_state)
{
	if(cs_state == CS_LOW)
	{	GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_RESET);}
	else
	{	GPIO_WriteBit(GPIOC, GPIO_Pin_6, Bit_SET);	}	
}


/*******************************************************************************
* Function Name  : SPI2_SendAndGet_Byte
* Description    : sends a byte via SPI1 and return the byte received from SPI1
* Input          : Byte: needed to be send
* Output         : None
* Return         : value of the received byte
*******************************************************************************/
unsigned char	SPI2_SendAndGet_Byte(unsigned char Byte)
{
	unsigned char	ReadByte;
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE)!=SET);	//Waiting for Tx-Empty flag sets(=1)
	SPI_I2S_SendData(SPI2,Byte);
	while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE)!=SET);	//Waiting Rx non-empty Flag, if RXNE = 1 means SPI receive data.
	ReadByte	=	SPI_I2S_ReceiveData(SPI2);		//read SPI received Data, and clear RXNE flag
	return(ReadByte);
}

/*******************************************************************************
* Function Name  : SPI2_SingleByteRead
* Description    : Read a byte data via SPI2 bus
* Input          : the address of register
* Output         : None
* Return         : value of register
*******************************************************************************/
unsigned char	SPI2_SingleByteRead(unsigned char Addr)
{	
	unsigned char	RegValue;

	SPI2_SendAndGet_Byte(Addr);
	RegValue	=	SPI2_SendAndGet_Byte(DummyByte);		//Get valid Data

	return(RegValue);
}

/*******************************************************************************
* Function Name  : SPI2_MultiByteRead
* Description    : Read multy bytes data via SPI2 bus
* Input          : the address of register, quntity of read, and pointer of read out buffer
* Output         : None
* Return         : Operation state TRUE of FALSE
*******************************************************************************/
unsigned char	SPI2_MultiByteRead(unsigned char StartAddr,unsigned char ReadNum, unsigned char * ReadBuf_pt)
{	
//	unsigned char	RegValue_Temp;
	unsigned char	ReadCounter = 0;

	SPI2_SendAndGet_Byte(StartAddr);
	
	while(ReadCounter < ReadNum)
	{
		*ReadBuf_pt	=	SPI2_SendAndGet_Byte(DummyByte);		//Read valid Data
		ReadBuf_pt ++;
		ReadCounter ++;
	}

	return(TRUE);
}

/*******************************************************************************
* Function Name  : SPI2_SingleByteWrite
* Description    : write a byte data to a register via SPI2 bus
* Input          : the address of register and the value
* Output         : None
* Return         : operation state TRUE of FALSE
*******************************************************************************/
unsigned char	SPI2_SingleByteWrite(unsigned char Addr, unsigned char Value)
{
	SPI2_SendAndGet_Byte(Addr);

	SPI2_SendAndGet_Byte(Value);

	return(TRUE);
}

