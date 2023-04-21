/*
 * File: lcd_private.h
 * Created Date: Monday, April 17th 2023, 2:47:14 am
 * Author: Omar Taha
 * -----
 * Copyright (c) 2023 Omar Taha <<https://github.com/OmarAshrafTaha>>
 */

#ifndef _LCD_PRIVATE_H_
#define _LCD_PRIVATE_H_





/*Macros for quick LCD Configurations*/
#define Cursor_Off         0x0C
#define Clear_Screen       0x01
#define LCD_4_Bit_Mode     0x02
#define LCD_8_Bit_Mode     0x38
#define Cursor_Blinking    0x0E
#define Cursor_Shift_Left  0x10
#define Cursor_Reset_Line1 0x80
#define Cursor_Reset_Line2 0xC0
#define Cursor_Shift_Right 0x06
#define LCD_4_Bit_Mode_5x7 0x28




#endif /*_LCD_PRIVATE_H_ */
