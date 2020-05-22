#include<windows.h>
#include <stdint.h>
#include<stdio.h>
#include "COM_PORT.h"

HANDLE hComm;
BOOL  Status;                          	// Status of the various operations 
DWORD dwEventMask;                     	// Event mask to trigger
char  TempChar;                        	// Temperory Character
char  SerialBuffer[256];               	// Buffer Containing Rxed Data
DWORD NoBytesRead;                     	// Bytes read by ReadFile()

 
unsigned char TxBuffer[256]; 

unsigned char RxBuffer[256];

	
/*
int main()
{

	unsigned char hamadaTx[] = {12, 45 , 67};
	
	PORT_Init();
	
	PORT_SendData(hamadaTx, 3);
	//PORT_ReceiveData(RxBuffer, 3);
	
	for(unsigned char btee5=0; btee5 < 3; btee5++)
		printf("Byte[%d]: %d\n", btee5, RxBuffer[btee5]);
	
	
	CloseHandle(hComm);
	
  return 0;
} */

void PORT_Init(void)
{
	hComm = CreateFile("COM3",                 		//port name
                    GENERIC_READ | GENERIC_WRITE, 	//Read/Write
                    0,                            	// No Sharing
                    NULL,                         	// No Security
                    OPEN_EXISTING,					// Open existing port only
                    0,            					// Non Overlapped I/O
                    NULL);       					// Null for Comm Devices

	if (hComm == INVALID_HANDLE_VALUE)
		printf("Error in opening serial port\n\n");
	else
		printf("opening serial port successful\n\n");
  
	/* Setting the configurations for TTL  */
	DCB dcbSerialParams = { 0 }; // Initializing DCB structure
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	dcbSerialParams.BaudRate = CBR_9600;  // Setting BaudRate = 9600
	dcbSerialParams.ByteSize = 8;         // Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;// Setting StopBits = 1
	dcbSerialParams.Parity   = NOPARITY;  // Setting Parity = None
	SetCommState(hComm, &dcbSerialParams);
}


void PORT_SendData(uint8_t *DataBuffer, uint32_t SizeOfData)
{
	/* Sending Bytes */

	DWORD dNoOFBytestoWrite;         	// No of bytes to write into the port
	DWORD dNoOfBytesWritten = 0;     	// No of bytes written to the port
	dNoOFBytestoWrite = SizeOfData;

	WriteFile(hComm,        			// Handle to the Serial port
			  DataBuffer,     			// Data to be written to the port
			  dNoOFBytestoWrite,  		//No of bytes to write
			  &dNoOfBytesWritten, 		//Bytes written
			  NULL);
}

void PORT_ReceiveData(uint8_t *DataReceived, uint32_t SizeOfData)
{
	int i = 0;
	/*------------------------------------ Setting Receive Mask ----------------------------------------------*/
	SetCommMask(hComm, EV_RXCHAR); //Configure Windows to Monitor the serial device for Character Reception
	
	/*------------------------------------ Setting WaitComm() Event   ----------------------------------------*/
	
	printf("\n\n    Waiting for Data Reception\n\n");
	WaitCommEvent(hComm, &dwEventMask, NULL); //Wait for the character to be received
	
	/*-------------------------- Program will Wait here till a Character is received ------------------------*/				
	printf("\n\n    Characters Received");	

	
	do
	{
		ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
		DataReceived[i] = TempChar;
		i++;
		printf("Data Received[%d]: %d\n", i-1 , DataReceived[i-1]);
		
	}
	while (i < SizeOfData);
}

