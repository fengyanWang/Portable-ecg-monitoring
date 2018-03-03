#ifndef __ADS1293_DRIVER_H
#define __ADS1293_DRIVER_H

#include "sys.h"
#include "SPI_UserDriver.h"
#include "stm32f10x_gpio.h"
#include "uart_communicate.h"
#include "delay.h"
#include "usart.h"




/*	ADS1293 register defination	*/
#define		ADS1293_RegisterMaxQuantity		(65)
#define		ADS1293_RW_RegisterQuantity		(37)
#define		ADS1293_RO_RegisterQuantity		(20)

//#define		ADS1293_ADCout_MAX				(0xB964F0)
#define		ADS1293_ADCout_MAX				(0xB964)

/*	ADS1293 CS state defination	*/
#define		ADS1293_CS_LOW					(0)
#define		ADS1293_CS_HIGH					(1)

/*	ADS1293 Reset state defination	*/
#define		ADS1293_Reset_Enable			(0)
#define		ADS1293_Reset_Disable			(1)

/*	ADS1293 Pin defination	*/
#define		SPI_CS						(GPIO_Pin_6)	//PC.6
#define		SPI_SCK						(GPIO_Pin_13)	//PB.13
#define		SPI_MISO					(GPIO_Pin_14)	//PB.14
#define		SPI_MOSI					(GPIO_Pin_15)	//PB.15
#define		ADS1293_DRDYB				(GPIO_Pin_7)	//PC.3
#define		ADS1293_ALARMB				(GPIO_Pin_8)	//PC.8
#define		ADS1293_RESET				(GPIO_Pin_1)	//PB.1

/* ADS1293 Register structure definition */
typedef struct
{
 	unsigned char Address;
	unsigned char Value;
}ADS1293_RegisterTypeDef;

/* ADS1293 ECG Data structure definition */
typedef struct
{
 	unsigned char H_Byte;
	unsigned char L_Byte;
}ECG_DataTypeDef;


/*	ADS1293 Register defination	*/
#define		REG_CONFIG_ADDR				(0x00)		//Main Configuration	R/W		default value: 0x02	
	
#define		REG_LOD_CN_ADDR				(0x06)		//Lead-Off Detect Contro		R/W		default value: 0x08
#define		REG_LOD_EN_ADDR				(0x07)		//Lead-Off Detect Enable		R/W		default value: 0x00
#define		REG_LOD_CURRENT_ADDR		(0x08)		//Lead-Off Detect Current		R/W		default value: 0x00
#define		REG_LOD_AC_CN_ADDR			(0x09)		//AC Lead-Off Detect Control	R/W		default value: 0x00

#define		REG_ERROR_LOD				(0x18)		//Lead-Off Detect Error Status		RO
#define		REG_ERROR_STATUS			(0x19)		//Other Error Status				RO
#define		REG_ERROR_RANGE1			(0x1A)		//Channel1 AFE Out-of-Range Status	RO
#define		REG_ERROR_RANGE2			(0x1B)		//Channel2 AFE Out-of-Range Status	RO
#define		REG_ERROR_RANGE3			(0x1C)		//Channel3 AFE Out-of-Range Status	RO
#define		REG_ERROR_SYNC				(0x1D)		//Synchonization Error				RO
#define		REG_ERROR_MISC				(0x1E)		//Miscellaneous Errors				RO

#define		REG_DATA_STATUS_ADDR		(0x30)		//ECG and Pace Data Ready Status	RO		default value: 0x00
#define		REG_DATA_CH1_PACE_H_ADDR	(0x31)		//Channel 1 Pace Data upper byte	RO		default value: 0x00
#define		REG_DATA_CH1_PACE_L_ADDR	(0x32)		//Channel 1 Pace Data lower byte	RO		default value: 0x00
#define		REG_DATA_CH2_PACE_H_ADDR	(0x33)		//Channel 2 Pace Data upper byte	RO		default value: 0x00
#define		REG_DATA_CH2_PACE_L_ADDR	(0x34)		//Channel 2 Pace Data lower byte	RO		default value: 0x00
#define		REG_DATA_CH3_PACE_H_ADDR	(0x35)		//Channel 3 Pace Data upper byte	RO		default value: 0x00
#define		REG_DATA_CH3_PACE_L_ADDR	(0x36)		//Channel 3 Pace Data lower byte	RO		default value: 0x00

#define		REG_DATA_CH1_ECG_H_ADDR		(0x37)		//Channel 1 ECG Data upper byte, 	RO,	default value: None
#define		REG_DATA_CH1_ECG_M_ADDR		(0x38)		//Channel 1 ECG Data milddle byte, 	RO,	default value: None
#define		REG_DATA_CH1_ECG_L_ADDR		(0x39)		//Channel 1 ECG Data milddle byte, 	RO,	default value: None
#define		REG_DATA_CH2_ECG_H_ADDR		(0x3A)		//Channel 2 ECG Data upper byte, 	RO,	default value: None
#define		REG_DATA_CH2_ECG_M_ADDR		(0x3B)		//Channel 2 ECG Data milddle byte, 	RO,	default value: None
#define		REG_DATA_CH2_ECG_L_ADDR		(0x3C)		//Channel 2 ECG Data milddle byte, 	RO,	default value: None
#define		REG_DATA_CH3_ECG_H_ADDR		(0x3D)		//Channel 3 ECG Data upper byte, 	RO,	default value: None
#define		REG_DATA_CH3_ECG_M_ADDR		(0x3E)		//Channel 3 ECG Data milddle byte, 	RO,	default value: None
#define		REG_DATA_CH3_ECG_L_ADDR		(0x3F)		//Channel 3 ECG Data milddle byte, 	RO,	default value: None

#define		REG_REVID_ADDR				(0x40)		//Revision ID, 	RO,	default value: 0x01
#define		REG_DATA_LOOP_ADDR			(0x50)		//Loop Read Back Address, 	RO


extern	ECG_DataTypeDef		ADS1293_ECG_CH1;
extern	ECG_DataTypeDef		ADS1293_ECG_CH2;
extern	ECG_DataTypeDef		ADS1293_ECG_CH3;

extern	unsigned char		ADS1293_Error_State;			//0:default, no errors find. 1:find errors
extern	unsigned char		ADS1293_Error_Feedback_Flag;	//0:not feedback. 1:need to feedback errors


/*	ADS1293 Driver functions declaration */
void	ADS1293_ResetControl(unsigned char ResetState);
void	ADS1293_SPI_CS_Set(unsigned char cs_state);
unsigned char	ADS1293_RegWrite(unsigned char RegAddr, unsigned char RegValue);
unsigned char	ADS1293_RegRead(unsigned char RegAddr);
unsigned char	ADS1293_MultiRegRead(unsigned char RegAddr, unsigned char Quantity, unsigned char * ReadBuf_pt);
unsigned int	ADS1293_ECG_DataRead(unsigned char ECG_Channel);
unsigned int	ADS1293_Read_ChipRevID(void);
unsigned char	ADS1293_Init(void);
void	ADS1293_StartConversion(void);
void	ADS1293_StopConversion(void);
void	ADS1293_Handler(void);

#endif /* __ADS1293_DRIVER_H */
