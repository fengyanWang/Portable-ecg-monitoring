#ifndef __SPI_USERDRIVER_H
#define __SPI_USERDRIVER_H


#include "sys.h"
#include "stm32f10x_spi.h"


typedef enum {FALSE = 0, TRUE = !FALSE} bool;




/*	CS state defination	*/
#define		CS_LOW					(0)
#define		CS_HIGH					(1)

/*	SPI1 Pin defination	*/
#define		SPI_CS						(GPIO_Pin_6)	//PC.6
#define		SPI_SCK						(GPIO_Pin_13)	//PB.13
#define		SPI_MISO					(GPIO_Pin_14)	//PB.14
#define		SPI_MOSI					(GPIO_Pin_15)	//PB.15

#define		DummyByte				(0xFF)	//use it to generate spi clk signal, meanless.

void	SPI2_CS_Set(unsigned char cs_state);
unsigned char	SPI2_SendAndGet_Byte(unsigned char Byte);
unsigned char	SPI2_SingleByteRead(unsigned char Addr);
unsigned char	SPI2_MultiByteRead(unsigned char StartAddr,unsigned char ReadNum, unsigned char * ReadBuf_pt);
unsigned char	SPI2_SingleByteWrite(unsigned char Addr, unsigned char Value);


#endif /* __SPI_USERDRIVER_H */

























