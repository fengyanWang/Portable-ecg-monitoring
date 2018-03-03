#ifndef __UART_COMMUNICATE_H
#define __UART_COMMUNICATE_H

#include "sys.h"


#define		PackageHeadID			(0xF0)

#define		PcakageIndex_ECG_1ch	(0x01)
#define		PcakageIndex_ECG_2ch	(0x02)
#define		PcakageIndex_ECG_3ch	(0x03)
#define		PcakageIndex_ECG_4ch	(0x04)
#define		PcakageIndex_ECG_5ch	(0x05)
#define		PcakageIndex_ECG_6ch	(0x06)
#define		PcakageIndex_REG		(0x07)

/*  structure definition */
#define		PACKAGE_BYTE_SIZE		(4)
#define		PACKAGE_MAX_QUANTITY	(64)

typedef struct
{
 	unsigned char 	WriteInPosition;
	unsigned char 	ReadOutPosition;
	unsigned char 	Quantity;
	unsigned char	TransmittingFlag;						//0: Not transmitting; 1: transmitting now
	unsigned char	SendByteCounter;						//用于记录已经发送字节数，数值范围为：0~3.
	unsigned char PackageArray[PACKAGE_MAX_QUANTITY][PACKAGE_BYTE_SIZE];
}Tx_PackageBufTypeDef;


typedef struct
{
 	unsigned char 	Head_Index_Byte;
	unsigned char 	High_Byte;
	unsigned char 	XORCheck_Bigh_Byte;
	unsigned char 	Low_Byte;
}Package_TypeDef;


extern Tx_PackageBufTypeDef	USART3_TxBuffer;


void	USART3_Transmit_Handler(void);
unsigned int	Fill_TxPackage(Package_TypeDef Package, Tx_PackageBufTypeDef* TxPkg_pt);





#endif /* __UART_COMMUNICATE_H */





