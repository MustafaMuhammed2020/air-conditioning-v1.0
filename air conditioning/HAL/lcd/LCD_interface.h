/*
 * File: lcd_interface.h
 * Created Date: Monday, April 17th 2023, 1:21:36 am
 * Author: Mohab Ahmed
 * -----
 */

#ifndef _INTERFACE_H_
#define _INTERFACE_H_


//#include <avr/delay.h>
#include "LCD_private.h"
#include "LCD_config.h"
#include "../../MCAL/timer0/TMR0_interface.h"
#include "../../SERVICE/standard_types.h"
#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/registers.h"

uint8_t Bell[8];


uint8_t LCD_8_bit_init(void);

uint8_t LCD_8_bit_sendCommand(uint8_t u8_a_command);

uint8_t LCD_8_bit_sendChar(uint8_t u8_a_char);

uint8_t LCD_8_bit_sendstring(uint8_t *str);

uint8_t LCD_4_bit_init(void);

uint8_t LCD_4_bit_sendCommand(uint8_t u8_a_command);

uint8_t LCD_4_bit_sendChar(uint8_t u8_a_char);

uint8_t LCD_4_bit_sendstring(uint8_t *str);

uint8_t LCD_create_custome_characters(uint8_t *pattern, uint8_t location);


#endif /*_INTERFACE_H_ */