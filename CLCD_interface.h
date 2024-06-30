

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendCleerCommond(void);

void CLCD_voidInit(void);

void CLCD_voidSendString(char * Copy_pvString);

void CLCD_voidSendNum(u16 Copy_u16Num);

void CLCD_voidSendPos(u8 Copy_u8X,u8 Copy_u8Y);
void CLCD_voidWriteSpecialCharacter(u8*Copy_pattern,u8 Copy_u8Loc,u8 Copy_u8X,u8 Copy_u8Y);

#endif
