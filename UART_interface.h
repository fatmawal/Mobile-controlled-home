#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void USART_voidInit(void);
void USART_voidSend(u8 Copy_u8Data);
u8  USART_u8Recive(void);
void USART_voidSendString(u8 * string);
void USART_voidReciveString(u8 * string);
void receiveStringFromUART(char *buffer);


#endif
