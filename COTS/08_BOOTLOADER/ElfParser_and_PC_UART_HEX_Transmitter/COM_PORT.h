#ifndef COM_PORT_H
#define COM_PORT_H

void PORT_Init(void);
void PORT_SendData(uint8_t *DataBuffer, uint32_t SizeOfData);
void PORT_ReceiveData(uint8_t *DataReceived, uint32_t SizeOfData);

#endif /* COM_PORT_H */