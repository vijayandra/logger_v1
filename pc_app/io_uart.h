#ifndef __IO_UART_H
#define __IO_UART_H

int UARTDriverXmit(void *pBuffer, unsigned short Length, unsigned long Timeout );
unsigned short UARTDriverRecv(void *pBuffer,unsigned long Timeout);

#endif
