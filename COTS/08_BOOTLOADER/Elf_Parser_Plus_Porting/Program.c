#include "stdint.h"
#include "stdio.h"
#include "math.h"
#include "ElF_Parser.h"
#include "COM_PORT.h"

typedef struct
{
	uint8_t* Program;
	uint32_t EnteryPoint;
	
}flash_t;

typedef struct {
	uint32_t ValidationKey;
	uint32_t AppNumber;
	uint32_t StartAddress;
	uint32_t NumberOfSectors;
	uint32_t EntryPoint;
}FlashNewAppCmd_t;

#define FileName			"Our_Blinky.elf"

#define PROGRAM_SHIFT		0x3800
#define FLASH_INIT_ADDRESS	0x08000000

#define START_ADDRESS		(FLASH_INIT_ADDRESS+PROGRAM_SHIFT)
#define VALIDATION_KEY		0x11
#define APP_NUMBER			0x01
#define SECTOR_SIZE			1024
#define ACK_SIZE			0x01

#define ACK					((uint8_t)0x1)
#define NACK				((uint8_t)0x2)
#define END_OF_FRAME_ACK	((uint8_t)0x3)

uint8_t * Program = NULL;
uint8_t   AckBuffer[ACK_SIZE] = {0};
uint32_t  SizeReturn;
uint32_t  EntryPoint;
uint32_t  StartAddress;
FlashNewAppCmd_t FlashNewAppCmd ;

void main(void)
{
	uint32_t SectorCount = 0;
	uint32_t index = 0;
	
	//calling the functions realted to the elf parser
	Program =  ELF_ParsingFile(FileName, PROGRAM_SHIFT, &SizeReturn, &EntryPoint, &StartAddress);
	
	printf("SizeReturn(Hex)   : %X \n",SizeReturn);
	printf("EntryPoint(Hex)   : %X \n",EntryPoint);
	printf("StartAddress(Hex) : %X \n",StartAddress);
	
	for (index = 0 ; index < SizeReturn ; index++)
	{
		printf("Program[%X]: %02X \n", index , Program[index]);
	}
	
	//calling the functions realted to the COM_PORT
	
	/* inializing the output/input port */
	PORT_Init();
	
	SectorCount = ceil((float)SizeReturn/SECTOR_SIZE);
	
	
	/* Sending flashnew APP Command*/
	FlashNewAppCmd.ValidationKey	= VALIDATION_KEY;
	FlashNewAppCmd.AppNumber		= APP_NUMBER;
	FlashNewAppCmd.StartAddress	    = START_ADDRESS;
	FlashNewAppCmd.NumberOfSectors	= SectorCount;
	FlashNewAppCmd.EntryPoint		= EntryPoint;
	
	PORT_SendData((uint8_t*)&FlashNewAppCmd, sizeof(FlashNewAppCmd));
	
	/* Receiving Header ACK */
	PORT_ReceiveData(AckBuffer, ACK_SIZE);
	
	if (AckBuffer[0] == ACK)
	{	
		/* ACK received of Sector Transmission */
		printf("Header ACK Transmitted Successfully \n");
		
		for (index = 0 ; index < SectorCount ; index++)
		{
			/* Sending Sector Data */
			PORT_SendData((uint8_t*)&Program[(index*SECTOR_SIZE)], SECTOR_SIZE);
			/* Receiving ACK of Transmitted Sector Data */
			PORT_ReceiveData(AckBuffer, ACK_SIZE);
			if (AckBuffer[0] != ACK)
			{
				if (AckBuffer[0] == END_OF_FRAME_ACK)
				{
					/* End of Frame received */
					printf("Application Transmitted and Flashed Successfully \n");
				}
				else
				{
					/* NACK received of Sector Transmission */
					printf("ERROR!!!   Sector flashing error \n");
					break;
				}
			}
			else
			{
				/* ACK received of Sector Transmission */
				printf("Sector ACK Transmitted Successfully \n");
			}
		}
	}
	else
	{
		/* NACK received of header frame */
		printf("ERROR!!!   Header Transmission Failed \n");
	}
}