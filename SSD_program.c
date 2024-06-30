#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"




u8 SSD_arr[10]= {0b00111111,   /* 0 */
		0b00000110,   /* 1 */
		0b01011011,   /* 2 */
		0b01001111,   /* 3 */
		0b01100110,   /* 4 */
		0b01101101,   /* 5 */
		0b01111101,   /* 6 */
		0b00000111,   /* 7 */
		0b01111111,   /* 8 */
		0b01101111    /* 9 */
};


void SSD_voidEnable(SSD_t segment)
{
	if(segment.activestate==COMMON_CATHODE)
	{
		DIO_voidSetPinVal(segment.ctrlport,segment.ctrlpin,PIN_VAL_LOW);
	}
	else if (segment.activestate==COMMON_ANODE)
	{
		DIO_voidSetPinVal(segment.ctrlport,segment.ctrlpin,PIN_VAL_HIGH);
	}
}
void SSD_voidDisable(SSD_t segment)
{
	if(segment.activestate==COMMON_CATHODE)
	{
		DIO_voidSetPinVal(segment.ctrlport,segment.ctrlpin,PIN_VAL_HIGH);
	}
	else if (segment.activestate==COMMON_ANODE)
	{
		DIO_voidSetPinVal(segment.ctrlport,segment.ctrlpin,PIN_VAL_LOW);
	}
}

void SSD_voidSendNum(SSD_t segment,u8 Copy_u8Num)
{
	if(segment.activestate==COMMON_CATHODE)
	{
		DIO_voidSetPortVal(segment.dataport,SSD_arr[Copy_u8Num]);
	}
	else if(segment.activestate==COMMON_ANODE)
	{
		DIO_voidSetPortVal(segment.dataport,~(SSD_arr[Copy_u8Num]));
	}
}


