/*
 * File: lcd.c
 * Created Date: Monday, April 17th 2023, 1:21:26 am
 * Author: Omar Taha
 * -----
 * Copyright (c) 2023 Omar Taha <<https://github.com/OmarAshrafTaha>>
 */

#include "lcd_interface.h"

extern uint8_t Bell[8] = {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};


uint8_t LCD_8_bit_init(void)
{
	set_bit(LCD_Command_Dir,EN);
	set_bit(LCD_Command_Dir,RW);
	set_bit(LCD_Command_Dir,RS);
    LCD_Data_Dir = 0xFF;
	TMR0_delayms(20);
	LCD_8_bit_sendCommand(LCD_8_Bit_Mode);
	LCD_8_bit_sendCommand(Cursor_Off);
	LCD_8_bit_sendCommand(Cursor_Shift_Right);
	LCD_8_bit_sendCommand(Clear_Screen);
	LCD_8_bit_sendCommand(Cursor_Reset_Line1);
}


uint8_t LCD_8_bit_sendCommand(uint8_t u8_a_command)
{
    LCD_Data_Port = u8_a_command;
	clear_bit(LCD_Command_Port,RS);
	clear_bit(LCD_Command_Port,RW);
	set_bit(LCD_Command_Port,EN);
	TMR0_delaymicros(1);
	clear_bit(LCD_Command_Port,EN);
	TMR0_delayms(3);
}


uint8_t LCD_8_bit_sendChar(uint8_t u8_a_char)
{
    LCD_Data_Port = u8_a_char;
	set_bit(LCD_Command_Port,RS);
	clear_bit(LCD_Command_Port,RW);
	set_bit(LCD_Command_Port,EN);
	TMR0_delaymicros(1);
	clear_bit(LCD_Command_Port,EN);
	TMR0_delayms(1);
}

uint8_t LCD_8_bit_sendstring(uint8_t *str)
{
	uint16_t i;
	for(i=0;str[i]!=0;i++)
	{
		LCD_8_bit_sendChar(str[i]);
	}
}


uint8_t LCD_4_bit_init(void)
{
	uint8_t nibble = LCD_4_bit_nibble;
	set_bit(LCD_Command_Dir,EN);
	set_bit(LCD_Command_Dir,RW);
	set_bit(LCD_Command_Dir,RS);
	if(nibble == upper_nibble)
	{
		LCD_Data_Dir = 0xFF;
	}
	else if(nibble == lower_nibble)
	{
		LCD_Data_Dir = 0xFF;
	}
	TMR0_delayms(200);
	
	LCD_8_bit_sendCommand(Cursor_Off);
	LCD_8_bit_sendCommand(Cursor_Shift_Right);
	LCD_8_bit_sendCommand(Clear_Screen);
	LCD_8_bit_sendCommand(Cursor_Reset_Line1);
	LCD_8_bit_sendCommand(LCD_4_Bit_Mode_5x7);
}

uint8_t LCD_4_bit_sendCommand(uint8_t u8_a_command)
{
	uint8_t nibble = LCD_4_bit_nibble;
	if(nibble == upper_nibble)
	{
		LCD_Data_Port = ((LCD_Data_Port & 0x0F) | (u8_a_command & 0xF0));
	}
	else if(nibble == lower_nibble)
	{
		LCD_Data_Port = (LCD_Data_Port & 0xF0) | (u8_a_command & 0x0F);
	}
	clear_bit(LCD_Command_Port,RS);
	clear_bit(LCD_Command_Port,RW);
	set_bit(LCD_Command_Port,EN);
	TMR0_delaymicros(1000);
	clear_bit(LCD_Command_Port,EN);
	TMR0_delaymicros(2000);
	if(nibble == upper_nibble)
	{
		LCD_Data_Port = ((LCD_Data_Port & 0x0F) | (u8_a_command << 4));
	}
	else if(nibble == lower_nibble)
	{
		LCD_Data_Port = (LCD_Data_Port & 0xF0) | (u8_a_command >> 4);
	}
	set_bit(LCD_Command_Port,EN);
	TMR0_delaymicros(1000);
	clear_bit(LCD_Command_Port,EN);
	TMR0_delayms(200);
}

uint8_t LCD_4_bit_sendChar(uint8_t u8_a_char)
{
	uint8_t nibble = LCD_4_bit_nibble;
	if(nibble == upper_nibble)
	{
		LCD_Data_Port = ((LCD_Data_Port & 0x0F) | (u8_a_char & 0xF0));
	}
	else if(nibble == lower_nibble)
	{
		LCD_Data_Port = (LCD_Data_Port & 0xF0) | (u8_a_char & 0x0F);
	}
	set_bit(LCD_Command_Port,RS);
	clear_bit(LCD_Command_Port,RW);
	set_bit(LCD_Command_Port,EN);
	TMR0_delaymicros(1000);
	clear_bit(LCD_Command_Port,EN);
	TMR0_delaymicros(2000);
	if(nibble == upper_nibble)
	{
		LCD_Data_Port = ((LCD_Data_Port & 0x0F) | (u8_a_char << 4));
	}
	else if(nibble == lower_nibble)
	{
		LCD_Data_Port = (LCD_Data_Port & 0xF0) | (u8_a_char >> 4);
	}
	set_bit(LCD_Command_Port,EN);
	TMR0_delaymicros(1000);
	clear_bit(LCD_Command_Port,EN);
	TMR0_delayms(200);
}

uint8_t LCD_4_bit_sendstring(uint8_t *str)
{
	uint32_t i;
	for(i=0;str[i]!=0;i++)
	{
		LCD_4_bit_sendChar(str[i]);
	}
}

uint8_t LCD_create_custome_characters(uint8_t *pattern, uint8_t location)
{
	uint8_t i=0;
	LCD_8_bit_sendCommand( 0x40 + (location*8) );
	for(i=0;i<8;i++)
	{
		LCD_8_bit_sendChar( pattern[i] );
	}
}
