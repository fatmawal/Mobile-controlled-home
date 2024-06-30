/***************************  Layer: HAL****************************/
/****************************Author: Yousef Ahmad****************/
/****************************Version:01*********/
/****************************Date: 22/8/2023 ******************/
/****************************Component:SSD*************/
/*******************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define COMMON_ANODE     1
#define COMMON_CATHODE   0

typedef struct
{
	u8 dataport;
	u8 ctrlport;
	u8 ctrlpin;
	u8 activestate;
}SSD_t;


void SSD_voidEnable(SSD_t segment);
void SSD_voidSendNum(SSD_t segment,u8 Copy_u8Num);


#endif
