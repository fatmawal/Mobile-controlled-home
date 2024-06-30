#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#define UDR *((volatile u8*)0x2C)

#define UCSRA *((volatile u8*)0x2B)

#define UCSRA_RXC   7
#define UCSRA_TXC   6
#define UCSRA_UDRE   5
#define UCSRA_U2X   1

#define UCSRB   *((volatile u8*)0x2A)
#define UCSRB_RXEN   4
#define UCSRB_TXEN     3
#define UCSRB_UCSZ2    2

#define UCSRC   *((volatile u8*)0x40)
#define UCSRC_URSEL  7
#define UCSRC_UMSEL  6
#define UCSRC_USBS    3
#define UCSRC_UCSZ1    2
#define UCSRC_UCSZ0    1


#define UBRRL *((volatile u8*)0x29)



#endif
