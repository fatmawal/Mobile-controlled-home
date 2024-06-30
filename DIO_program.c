#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_private.h"
#include "DIO_config.h"
#include "DIO_interface.h"

void DIO_voidSetPortDir(u8 Copy_u8Port,u8 Copy_u8Dir)
{
	switch(Copy_u8Port)
	{
	case PORTA_REG :DDRA=Copy_u8Dir;break;
	case PORTB_REG :DDRB=Copy_u8Dir;break;
	case PORTC_REG :DDRC=Copy_u8Dir;break;
	case PORTD_REG :DDRD=Copy_u8Dir;break;
	}
}
void DIO_voidSetPinDir(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Dir)
{
	if(Copy_u8Pin<=7)
	{
		if(Copy_u8Dir==PIN_DIR_OUT)
		{
			switch(Copy_u8Port)
			{
			case PORTA_REG :SET_BIT(DDRA,Copy_u8Pin);break;
			case PORTB_REG :SET_BIT(DDRB,Copy_u8Pin);break;
			case PORTC_REG :SET_BIT(DDRC,Copy_u8Pin);break;
			case PORTD_REG :SET_BIT(DDRD,Copy_u8Pin);break;
			}
		}
		else if(Copy_u8Dir==PIN_DIR_IN)
		{
			switch(Copy_u8Port)
			{
			case PORTA_REG :CLR_BIT(DDRA,Copy_u8Pin);break;
			case PORTB_REG :CLR_BIT(DDRB,Copy_u8Pin);break;
			case PORTC_REG :CLR_BIT(DDRC,Copy_u8Pin);break;
			case PORTD_REG :CLR_BIT(DDRD,Copy_u8Pin);break;
			}
		}
	}
}
void DIO_voidSetPortVal(u8 Copy_u8Port,u8 Copy_u8Val)
{
	switch(Copy_u8Port)
	{
	case PORTA_REG :PORTA=Copy_u8Val;break;
	case PORTB_REG :PORTB=Copy_u8Val;break;
	case PORTC_REG :PORTC=Copy_u8Val;break;
	case PORTD_REG :PORTD=Copy_u8Val;break;
	}
}
void DIO_voidSetPinVal(u8 Copy_u8Port,u8 Copy_u8Pin,u8 Copy_u8Val)
{
	if(Copy_u8Pin<=7)
	{
		if(Copy_u8Val==PIN_VAL_HIGH)
		{
			switch(Copy_u8Port)
			{
			case PORTA_REG :SET_BIT(PORTA,Copy_u8Pin);break;
			case PORTB_REG :SET_BIT(PORTB,Copy_u8Pin);break;
			case PORTC_REG :SET_BIT(PORTC,Copy_u8Pin);break;
			case PORTD_REG :SET_BIT(PORTD,Copy_u8Pin);break;
			}
		}
		else if(Copy_u8Val==PIN_VAL_LOW)
		{
			switch(Copy_u8Port)
			{
			case PORTA_REG :CLR_BIT(PORTA,Copy_u8Pin);break;
			case PORTB_REG :CLR_BIT(PORTB,Copy_u8Pin);break;
			case PORTC_REG :CLR_BIT(PORTC,Copy_u8Pin);break;
			case PORTD_REG :CLR_BIT(PORTD,Copy_u8Pin);break;
			}
		}
	}
}
u8 DIO_u8GetPinVal(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	u8 Local_u8Reading=0;
	if(Copy_u8Pin<=7)
	{
		switch(Copy_u8Port)
		{
		case PORTA_REG:Local_u8Reading=GET_BIT(PINA,Copy_u8Pin);break;
		case PORTB_REG:Local_u8Reading=GET_BIT(PINB,Copy_u8Pin);break;
		case PORTC_REG:Local_u8Reading=GET_BIT(PINC,Copy_u8Pin);break;
		case PORTD_REG:Local_u8Reading=GET_BIT(PIND,Copy_u8Pin);break;
		}
	}
		return Local_u8Reading;
	}

