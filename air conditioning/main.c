/***********************************************************************************/
/* Author    : Mustafa Mohammed Abdou                                              */
/* Date      : 16 April, 2023                                                      */
/* Version   : V01                                                                 */
/* Hint      : APP layer                                                           */
/***********************************************************************************/

#include "HAL/lcd/lcd_interface.h"
#include "MCAL/timer0/TMR0_interface.h"
uint8_t u8_g_bell_Center[8] =   { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};
uint8_t u8_g_bell_midRight[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x02, 0x00};
uint8_t u8_g_bell_topRight[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x01, 0x00, 0x08};
uint8_t u8_g_bell_midLeft[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x08, 0x00};
uint8_t u8_g_bell_topLeft[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x10, 0x00, 0x08};
int main(void)
{
	/* Replace with your application code */
	//uint8_t val[] = "Hi! Omar";
	TMR0_init();
	LCD_init();
	TMR0_delayms(100);
	LCD_createCustomCharacter(u8_g_bell_Center,0);
	LCD_createCustomCharacter(u8_g_bell_midRight,1);
	LCD_createCustomCharacter(u8_g_bell_topRight,2);
	LCD_createCustomCharacter(u8_g_bell_midLeft,3);
	LCD_createCustomCharacter(u8_g_bell_topLeft,4);
	TMR0_delayms(100);
	//LCD_sendCommand(Clear_Screen);
	
	while(1)
	{  
		LCD_goTo(0,8);
		LCD_sendChar(0);
		TMR0_delayms(50);
		LCD_goTo(0,8);
		LCD_sendChar(1);
		TMR0_delayms(50);
		LCD_goTo(0,8);
		LCD_sendChar(2);
		TMR0_delayms(50);
		LCD_goTo(0,8);
		LCD_sendChar(1);
		TMR0_delayms(50);
		LCD_goTo(0,8);
		LCD_sendChar(0);
		TMR0_delayms(50);
		LCD_goTo(0,8);
		LCD_sendChar(3);
		TMR0_delayms(50);
		LCD_goTo(0,8);
		LCD_sendChar(4);
		TMR0_delayms(50);
		LCD_goTo(0,8);
		LCD_sendChar(3);
		TMR0_delayms(50);
	}

}

