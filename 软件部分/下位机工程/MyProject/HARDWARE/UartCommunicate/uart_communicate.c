#include "uart_communicate.h"


Tx_PackageBufTypeDef	USART3_TxBuffer;



/*******************************************************************************
* Function Name  : Generate_CheckByte
* Description    : 
* Input          : source byte buffer pointer, and byte quantity
* Output         : None
* Return         : Xor result
*******************************************************************************/
unsigned char Generate_XorCheckByte(unsigned char *SourceByte_pt, unsigned char CheckByteNum)
{
	unsigned char	XorByte = 0x00;
	unsigned char	temp_counter	= 0x00;
	while(temp_counter < CheckByteNum)
		{
			XorByte	= XorByte ^ (* SourceByte_pt);
			SourceByte_pt ++;
			temp_counter ++;		
		}
	return(XorByte);
}

/*******************************************************************************
* Function Name  : Fill_TxPackage
* Description    : Needed test
* Input          : TxPkg_pt	TxPackage pointer
* Output         : None	
* Return         : 	ERROR		Tx Packag is fulled
					SUCCESS		
*******************************************************************************/
unsigned int	Fill_TxPackage(Package_TypeDef Package, Tx_PackageBufTypeDef* TxPkg_pt)
{
	unsigned char	WriteIN_Index = 0;
	if(TxPkg_pt->Quantity < PACKAGE_MAX_QUANTITY)
		{
			WriteIN_Index	=	TxPkg_pt->WriteInPosition;
			TxPkg_pt->PackageArray[WriteIN_Index][0]	=	Package.Head_Index_Byte;
			TxPkg_pt->PackageArray[WriteIN_Index][1]	=	Package.High_Byte;
			TxPkg_pt->PackageArray[WriteIN_Index][2]	=	Package.Low_Byte;
			TxPkg_pt->PackageArray[WriteIN_Index][3]	=	Generate_XorCheckByte((TxPkg_pt->PackageArray[WriteIN_Index]),(PACKAGE_BYTE_SIZE - 1));
			TxPkg_pt->Quantity++;
			TxPkg_pt->WriteInPosition ++;
			TxPkg_pt->WriteInPosition = TxPkg_pt->WriteInPosition % PACKAGE_MAX_QUANTITY;	
		}
	else
		{
			return(ERROR);//Package List Overfloat
		}
	return(SUCCESS);
}


/*******************************************************************************
* Function Name  : USART3_Transmit_Handler
* Description    : Needed test
* Input          : 
* Output         : 	None	
* Return         :	None	
*******************************************************************************/
void	USART3_Transmit_Handler(void)
{
	unsigned char	USART3_Tx_Byte;

	if(USART3_TxBuffer.TransmittingFlag != 1)	//判断是否处于发送空闲状态
	{
		if(USART3_TxBuffer.Quantity != 0)	//发送缓存中是否有数据需要发送
			{
				USART3_Tx_Byte = USART3_TxBuffer.PackageArray[USART3_TxBuffer.ReadOutPosition][0];		//发送缓存中的首个字节，触发整个发送。其它字节的发送都在USART1的中断中进行.
				USART_SendData(USART3,(u16)USART3_Tx_Byte);
				USART3_TxBuffer.SendByteCounter ++;	
				USART3_TxBuffer.TransmittingFlag = 1;							
				USART_ITConfig(USART3, USART_IT_TXE, ENABLE);		/* Enable the USART3 Tx buffer Empty Interrupt */	
			}
	}
}



