/*
 * File: lcd_config.h
 * Created Date: Monday, April 17th 2023, 2:15:31 am
 * Author: Omar Taha
 * -----
 * Copyright (c) 2023 Omar Taha <<https://github.com/OmarAshrafTaha>>
 */

#ifndef _LCD_CONFIG_H_
#define _LCD_CONFIG_H_


#define LCD_Command_Dir DDRC
#define LCD_Data_Dir DDRB

#define LCD_Command_Port PORTC
#define LCD_Data_Port PORTB
/*----------------------------------------------------------------------------------------------------------------------------------*/
/*                                                  LCD mode                                                                        */
/*----------------------------------------------------------------------------------------------------------------------------------*/
#define LCD_Bit_Mode          8  /*Choose from 8 or 4 to run LCD on 8 bit mode or 4 bit mode                                        */
/*----------------------------------------------------------------------------------------------------------------------------------*/


                                                                                                     
#define EN                    0
#define RW                    1
#define RS                    2

#define upper_nibble 'u'
#define lower_nibble 'l'


#define LCD_4_bit_nibble upper_nibble


#endif /* _LCD_CONFIG_H_ */
