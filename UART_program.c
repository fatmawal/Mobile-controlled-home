#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include "UART_config.h"
#include "UART_interface.h"
#include "UART_private.h"

#define MAX_STRING_LENGTH 100

void USART_voidInit(void)
{
	u8 data=0 ;//=ucsrc
	//SIZE OF DATA
	SET_BIT(data,UCSRC_URSEL);//TO BE UCSRC
	SET_BIT(data,UCSRC_UCSZ1);
	SET_BIT(data,UCSRC_UCSZ0);
	CLR_BIT(UCSRB,UCSRB_UCSZ2);
	//1 BIT STOP
	CLR_BIT(data,UCSRC_USBS);
	//NO INTERUPT BY DEFALT
	//no parity by defalt
	//baud rate:
	UBRRL=51;
	//eneble trans and recive:
	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);
	UCSRC=data;

}
void USART_voidSend(u8 Copy_u8Data)
{
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);
	UDR=Copy_u8Data;


}
u8  USART_u8Recive(void)
{
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
}

void USART_voidSendString(u8 * string)
{
	u32 i=0;
	while (string[i] != '\0')
	{
		USART_voidSend(string[i]);
		i++;
	}
}

/*void USART_voidReciveString(u8 * string)
{
	u32 i=0;
	string[i]=USART_u8Recive();
	while (string[i] != '\0')
	{
		i++;
		string[i]=USART_u8Recive();
	}
	string[i]= '\0';
}
*/


// Function to receive a string from UART
void receiveStringFromUART(char *buffer)
{
    char c;
    int i = 0;

 // Read characters from UART until a newline character is encountered or maximum length is reached
    while ((c =USART_u8Recive() ) != '.' && i < MAX_STRING_LENGTH - 1)
    {
        buffer[i++] = c;
    }

    // Null-terminate the string
    buffer[i] = '\0';
}
