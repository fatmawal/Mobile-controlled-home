# Mobile-controlled-home


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "UART_interface.h"
#include "SSD_interface.h"

#include<util/delay.h>

u8 recieved_password[4];

//creating struct
typedef struct {
	u8 * username;
	u8 * password;
} users;

//array of 10 structs(10 users)
users array[10] = { { "fatma", "1111" }, { "waleed", "2222" },
		{ "nagwa", "3333" }, { "soka", "4444" }, { "fatma waleed", "5555" }, {
				"roba", "6666" }, { "reham", "7777" }, { "aaaa", "8888" }, {
				"mama", "9999" }, { "baba", "1010" } };

SSD_t seven = { PORTB_REG, PORTB_REG, PIN7, COMMON_CATHODE };

//func to compare 2 strings
u8 compare_strings(u8 *string1, u8 *string2, u32 length1, u32 length2) {
	if (length1 != length2) {
		return 0;
	} else {
		for (u32 i = 0; i < length1; i++) {
			if (string1[i] != string2[i]) {
				return 0;
			}
		}
		return 1;
	}
}
//func to know length of user name
u8 string_length(u8*string) {
	u32 i = 0;
	while (string[i] != '\0') {
		i++;
	}
	return i;
}

//ckeck password function
u8 check_password(u8 index) {
	//x is index of struct of entered username
	u8 test = compare_strings(recieved_password, array[index].password,
			string_length(recieved_password),
			string_length(array[index].password));
	if (1 == test) {
		//CLCD_voidSendString("correct password");
		//led on or open door
		return 1;
	} else {
		return 0;
	}
}

void main() {
	DIO_voidSetPortDir(PORTA_REG, PORT_DIR_OUT);  //CLCD
	DIO_voidSetPortDir(PORTC_REG, PORT_DIR_OUT); //CLCD  and motor

	DIO_voidSetPinDir(PORTC_REG, PIN7, PIN_DIR_OUT); //BUZZER
	DIO_voidSetPinDir(PORTD_REG, PIN5, PIN_DIR_OUT); //room 2
	DIO_voidSetPinDir(PORTD_REG, PIN7, PIN_DIR_OUT); //room1

	DIO_voidSetPinDir(PORTD_REG, PIN0, PIN_DIR_IN);       //RX
	DIO_voidSetPinDir(PORTD_REG, PIN1, PIN_DIR_OUT);     //TX
	DIO_voidSetPortDir(PORTB_REG, PORT_DIR_OUT);  //7 segment
	USART_voidInit();
	CLCD_voidInit();
	u8 name[20];
	u8 password_status;
	u8 check;
	u8 name2[20];
	while (1) {
		CLCD_voidSendCleerCommond();
		CLCD_voidSendString("welcome to mobile");
		CLCD_voidSendPos(1, 1);
		CLCD_voidSendString("controlled home");
		USART_voidSendString(" welcome to mobile controlled home:");
		_delay_ms(2000);
		USART_voidSendString("\r\n");
		CLCD_voidSendCleerCommond();
		CLCD_voidSendString("enter your name:");
		USART_voidSendString("enter your name:");
		receiveStringFromUART(name);

		for (u8 i = 0; i < 10; i++) {
			//name throw bluetoth and uart
			//name= what i enter from mobile
			//receiveStringFromUART(name);
			//u8 length1=string_length(name);

			check = compare_strings(name, array[i].username,
					string_length(name), string_length(array[i].username));
			if (check == 1) {
				CLCD_voidSendCleerCommond();
				CLCD_voidSendString("correct name,");
				CLCD_voidSendPos(1, 2);
				CLCD_voidSendString("enter password:");
				USART_voidSendString(
						" correct name, enter your password:");
				USART_voidSendString("\r\n");
				for (u8 j = 0; j < 3; j++) {
					receiveStringFromUART(recieved_password);
					password_status = check_password(i);
					if (1 == password_status) {
						CLCD_voidSendCleerCommond();
						CLCD_voidSendString("correct password");
						USART_voidSendString("correct password");
						USART_voidSendString("\r\n");
						_delay_ms(1500);
						CLCD_voidSendCleerCommond();
						CLCD_voidSendString(" choose options: ");
						USART_voidSendString(" choose options: ");
						USART_voidSendString("\r\n");
						USART_voidSendString("1-room1 on \\ 2-room2 on ");
						USART_voidSendString("\r\n");
						USART_voidSendString(
								"3-open door \\ 4-close door ");
						USART_voidSendString("\r\n");
						USART_voidSendString("5-room1 off \\ 6-room2 off ");
						USART_voidSendString("\r\n");
						USART_voidSendString(
								"7-room1&2 off \\ 8-logging out");
						USART_voidSendString("\r\n");
						u8 command = 0;
						while (command != '8') {
							command = USART_u8Recive();
							switch (command) {
							case '1':
								//room 1 led open
								DIO_voidSetPinVal(PORTD_REG, PIN7,
								PIN_VAL_HIGH);
								break;
							case '2':
								//room 2 led open
								DIO_voidSetPinVal(PORTD_REG, PIN5,
								PIN_VAL_HIGH);
								break;
							case '3':
								//open door
								DIO_voidSetPinVal(PORTC_REG, PIN3,
								PIN_VAL_HIGH);
								DIO_voidSetPinVal(PORTC_REG, PIN4,
								PIN_VAL_HIGH);
								_delay_ms(500);
								DIO_voidSetPinVal(PORTC_REG, PIN3,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN4,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN5,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN6,
								PIN_VAL_LOW);

								break;
							case '4':
								//close door
								DIO_voidSetPinVal(PORTC_REG, PIN5,
								PIN_VAL_HIGH);
								DIO_voidSetPinVal(PORTC_REG, PIN6,
								PIN_VAL_HIGH);
								_delay_ms(500);
								DIO_voidSetPinVal(PORTC_REG, PIN3,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN4,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN5,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN6,
								PIN_VAL_LOW);
								break;
							case '5':
								//room 1 led close
								DIO_voidSetPinVal(PORTD_REG, PIN7, PIN_VAL_LOW);
								break;
							case '6':
								//room 2 led close
								DIO_voidSetPinVal(PORTD_REG, PIN5, PIN_VAL_LOW);
								break;
							case '7':
								// room 1& 2 led close together
								DIO_voidSetPinVal(PORTD_REG, PIN7, PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTD_REG, PIN5, PIN_VAL_LOW);
								break;
							case '8':
								CLCD_voidSendCleerCommond();
								CLCD_voidSendString("Logging out");
								USART_voidSendString("Logging out ");
								USART_voidSendString("\r\n");
								_delay_ms(3000);
								CLCD_voidSendCleerCommond();
								break;
							}
						}
						break;
					}

					else if (password_status == 0 && j == 2) {
						SSD_voidEnable(seven);
						DIO_voidSetPinVal(PORTC_REG, PIN7, PIN_VAL_HIGH);//buzzer on
						CLCD_voidSendCleerCommond();
						CLCD_voidSendString("Not Safe...");
						USART_voidSendString("Not Safe...");
						for (u8 num = 9; num > 0; num--) {
							SSD_voidSendNum(seven, num);
							_delay_ms(1000);
						}
						SSD_voidDisable(seven);
						DIO_voidSetPinVal(PORTC_REG, PIN7, PIN_VAL_LOW);
						CLCD_voidSendCleerCommond();

					} else {
						CLCD_voidSendCleerCommond();
						CLCD_voidSendString("wrong password, ");
						CLCD_voidSendPos(1, 2);
						CLCD_voidSendString("try again");
						USART_voidSendString("wrong password,try again ");
						USART_voidSendString("\r\n");
					}

				}
				break;
			}

			//last ittration and check=0
			else if (i == 9 && check == 0)
			{
				for (u8 k = 0; k < 2; k++) {
					CLCD_voidSendCleerCommond();
					CLCD_voidSendString("wrong name,");
 					CLCD_voidSendPos(1, 2);
					CLCD_voidSendString("try again");
					USART_voidSendString(" wrong name , try again ");
					USART_voidSendString("\r\n");
					receiveStringFromUART(name2);
//same again
					for (u8 i2 = 0; i2 < 10; i2++) {

						u8 check2 = compare_strings(name2, array[i2].username,
								string_length(name2),
								string_length(array[i2].username));
						if (k == 1 && check2 == 0 && i2 == 9) {//here user enter name 3 times wrong
							SSD_voidEnable(seven);
							DIO_voidSetPinVal(PORTC_REG, PIN7, PIN_VAL_HIGH);//buzzer on
							CLCD_voidSendCleerCommond();
							CLCD_voidSendString("Not Safe...");
							USART_voidSendString("Not Safe...");
							USART_voidSendString("\r\n");
							for (u8 num = 9; num > 0; num--) {
								SSD_voidSendNum(seven, num);
								_delay_ms(1000);
							}
							//SSD_voidDisable(seven);
							DIO_voidSetPortVal(PORTB_REG, PORT_VAL_LOW);
							DIO_voidSetPinVal(PORTC_REG, PIN7, PIN_VAL_LOW);
							CLCD_voidSendCleerCommond();
							break;

						} else if (check2 == 1) {
							CLCD_voidSendCleerCommond();
							CLCD_voidSendString("correct name,");
							CLCD_voidSendPos(1, 2);
							CLCD_voidSendString("enter password:");
							USART_voidSendString(
									" correct name, enter your password:");
							USART_voidSendString("\r\n");
							for (u8 j = 0; j < 3; j++) {
								receiveStringFromUART(recieved_password);
								password_status = check_password(i2);
								if (1 == password_status) {
									CLCD_voidSendCleerCommond();
									CLCD_voidSendString("correct password");
									USART_voidSendString(
											"correct password");
									USART_voidSendString("\r\n");
									_delay_ms(1500);
									CLCD_voidSendCleerCommond();
									CLCD_voidSendString(" choose options: ");
									USART_voidSendString(
											" choose options: ");
									USART_voidSendString("\r\n");
									USART_voidSendString(
											"1-room1 on \\ 2-room2 on ");
									USART_voidSendString("\r\n");
									USART_voidSendString(
											"3-open door \\ 4-close door ");
									USART_voidSendString("\r\n");
									USART_voidSendString(
											"5-room1 off \\ 6-room2 off ");
									USART_voidSendString("\r\n");
									USART_voidSendString(
											"7-room1&2 off \\ 8-logging out ");
									USART_voidSendString("\r\n");
									u8 command = 0;
									while (command != '8') {
										command = USART_u8Recive();
										switch (command) {
										case '1':
											//room 1 led open
											DIO_voidSetPinVal(PORTD_REG, PIN7,
											PIN_VAL_HIGH);
											break;
										case '2':
											//room 2 led open
											DIO_voidSetPinVal(PORTD_REG, PIN5,
											PIN_VAL_HIGH);
											break;
										case '3':
								//open door
								DIO_voidSetPinVal(PORTC_REG, PIN3,
								PIN_VAL_HIGH);
								DIO_voidSetPinVal(PORTC_REG, PIN4,
								PIN_VAL_HIGH);
								_delay_ms(500);
								DIO_voidSetPinVal(PORTC_REG, PIN3,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN4,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN5,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN6,
								PIN_VAL_LOW);

								break;
							case '4':
								//close door
								DIO_voidSetPinVal(PORTC_REG, PIN5,
								PIN_VAL_HIGH);
								DIO_voidSetPinVal(PORTC_REG, PIN6,
								PIN_VAL_HIGH);
								_delay_ms(500);
								DIO_voidSetPinVal(PORTC_REG, PIN3,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN4,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN5,
								PIN_VAL_LOW);
								DIO_voidSetPinVal(PORTC_REG, PIN6,
								PIN_VAL_LOW);
								break;
									 	case '5':
								 			//room 1 led close
											DIO_voidSetPinVal(PORTD_REG, PIN7,
											PIN_VAL_LOW);
											break;
										case '6':
											//room 2 led close
											DIO_voidSetPinVal(PORTD_REG, PIN5,
											PIN_VAL_LOW);
											break;
										case '7':
											// room 1& 2 led close together
											DIO_voidSetPinVal(PORTD_REG, PIN7,
											PIN_VAL_LOW);
											DIO_voidSetPinVal(PORTD_REG, PIN5,
											PIN_VAL_LOW);
											break;
										case '8':
											CLCD_voidSendCleerCommond();
											CLCD_voidSendString("Logging out");
											USART_voidSendString(
													"Logging out ");
											USART_voidSendString("\r\n");
											_delay_ms(2000);
											CLCD_voidSendCleerCommond();
											 k=2;
											break;
										}//switch

									}//while
									break;
								} //if
								else if (0 == password_status && j == 2) {
									SSD_voidEnable(seven);
									DIO_voidSetPinVal(PORTC_REG, PIN7,
									PIN_VAL_HIGH);			//buzzer on
									CLCD_voidSendCleerCommond();
									CLCD_voidSendString("Not Safe...");
									USART_voidSendString("Not Safe...");
									USART_voidSendString("\r\n");
									for (u8 num = 9; num > 0; num--) {
										SSD_voidSendNum(seven, num);
										_delay_ms(1000);
									}
									SSD_voidDisable(seven);
									DIO_voidSetPinVal(PORTC_REG, PIN7,
									PIN_VAL_LOW);
									CLCD_voidSendCleerCommond();

								} else {
									CLCD_voidSendCleerCommond();
									CLCD_voidSendString("wrong password, ");
									CLCD_voidSendPos(1, 2);
									CLCD_voidSendString("try again");
									USART_voidSendString(
											"wrong password,try again ");
									USART_voidSendString("\r\n");

								}
								//break;
							}// for of password
							break;
						}//else of correct name
					}//for of i (whitch user)

				}//for 2 trials of name

			}//last else if(name is wrong first time)
		}//first for
	}	//while 1
}	//main
