#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"


void CLCD_voidSendData(u8 Copy_u8Data)
{
	//RS -> 1 SEND DATA
	DIO_voidSetPinVal(CTRL_PORT,RS,PIN_VAL_HIGH);
	//RW -> 0 SEND COMMAND
	DIO_voidSetPinVal(CTRL_PORT,RW,PIN_VAL_LOW);
	//SET DATA TO DATA PORT
	DIO_voidSetPortVal(DATA_PORT,Copy_u8Data);
	DIO_voidSetPinVal(CTRL_PORT,E,PIN_VAL_HIGH);
	_delay_ms(1);
	DIO_voidSetPinVal(CTRL_PORT,E,PIN_VAL_LOW);
}

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	//RS -> 0 SEND DATA
	DIO_voidSetPinVal(CTRL_PORT,RS,PIN_VAL_LOW);
	//RW -> 0 SEND COMMAND
	DIO_voidSetPinVal(CTRL_PORT,RW,PIN_VAL_LOW);
	//SET COMMAND TO DATA PORT
	DIO_voidSetPortVal(DATA_PORT,Copy_u8Command);

	DIO_voidSetPinVal(CTRL_PORT,E,PIN_VAL_HIGH);
	_delay_ms(1);
	DIO_voidSetPinVal(CTRL_PORT,E,PIN_VAL_LOW);
}

void CLCD_voidSendCleerCommond(void)
{
	CLCD_voidSendCommand(0b00000001);
	_delay_ms(30);
}
void CLCD_voidInit(void)
{
	_delay_ms(40);
	CLCD_voidSendCommand(0b00111000);
	_delay_ms(1);
	CLCD_voidSendCommand(0b00001100);
	_delay_ms(1);
	CLCD_voidSendCommand(0b00000001);
	_delay_ms(2);
}
void CLCD_voidSendString(char*Copy_pvString)
{
	u8 i=0;
	while(Copy_pvString[i]!='\0')
	{
		CLCD_voidSendData(Copy_pvString[i]);
		i++;
	}
}
void CLCD_voidSendNum(u16 Copy_u16Num)
{
	u8 arr[10];
	u8 i=0;
	u8 j;
	do
	{
		arr[i]=Copy_u16Num%10+'0';
		Copy_u16Num/=10;
		i++;
	}while(Copy_u16Num);
	for(j=i;j>0;j--)
	{
		CLCD_voidSendData(arr[j-1]);
	}
}

void CLCD_voidSendPos(u8 Copy_u8X,u8 Copy_u8Y)
{
	u8 Local_u8Pos;
	if(Copy_u8X==0)
	{
		Local_u8Pos=Copy_u8Y;
	}
	else if(Copy_u8X==1)
	{
		Local_u8Pos=0x40+Copy_u8Y;
	}
	CLCD_voidSendCommand(Local_u8Pos+128);

}
void CLCD_voidWriteSpecialCharacter(u8*Copy_pattern,u8 Copy_u8Loc,u8 Copy_u8X,u8 Copy_u8Y)
{
	u8 Local_u8CGRAMAdress,Local_u8Iterator=0;
	//CALCULATE CGRAMADDRESS
	Local_u8CGRAMAdress=Copy_u8Loc*8;
	//SET CGRAM ADDRESS
	CLCD_voidSendCommand(Local_u8CGRAMAdress+64);
	//SEND THE PATTERN BYTE BY BYTE
	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		CLCD_voidSendData(Copy_pattern[Local_u8Iterator]);
	}
	CLCD_voidSendPos(Copy_u8X,Copy_u8Y);
	CLCD_voidSendData(Copy_u8Loc);
}
