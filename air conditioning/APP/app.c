/***********************************************************************************/
/* Author    : Mustafa Mohammed Abdou                                              */
/* Date      : 16 April, 2023                                                      */
/* Version   : V01                                                                 */
/* Hint      : APP layer                                                           */
/***********************************************************************************/

/** INCLUDE LIBRARIES **/
#include "../SERVICE/common_macros.h"
#include "../SERVICE/standard_types.h"

/** INCLUDE MODULES INTERFACE FILES **/
#include "../HAL/lcd/LCD_interface.h"
#include "../HAL/lcd/LCD_config.h"

#include "../MCAL/timer0/TMR0_interface.h"
#include "../MCAL/timer0/TMR0_config.h"

uint8_t u8_g_bell[8] =   { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};
uint8_t u8_g_bell_1[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x02, 0x00};
uint8_t u8_g_bell_2[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x01, 0x00, 0x08};
uint8_t u8_g_bell_3[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x08, 0x00};
uint8_t u8_g_bell_4[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x10, 0x00, 0x08};
	

void APP_init()
{
	TMR0_init();
	
	LCD_init();
	
	TMR0_delayms(20);
		
	LCD_writecustomchar(u8_g_bell , 0);
	
	LCD_writecustomchar(u8_g_bell_1 , 1);
	
	LCD_writecustomchar(u8_g_bell_2 , 2);
	
	LCD_writecustomchar(u8_g_bell_3 , 3);
	
	LCD_writecustomchar(u8_g_bell_4 , 4);
	
}


void APP_start()
{
	
 	LCD_goto(0,8);
 	LCD_writechar(0);
 	TMR0_delayms(90);
	 
 	LCD_goto(0,8);
 	LCD_writechar(1);
 	TMR0_delayms(90);
 	
	 LCD_goto(0,8);
	 LCD_writechar(2);
	 TMR0_delayms(90);
 	
	 LCD_goto(0,8);
	 LCD_writechar(1);
	 TMR0_delayms(90);
 	
	 LCD_goto(0,8);
	 LCD_writechar(0);
	 TMR0_delayms(90);
	 
	 LCD_goto(0,8);
	 LCD_writechar(3);
	 TMR0_delayms(90);
 	
	 LCD_goto(0,8);
	 LCD_writechar(4);
	 TMR0_delayms(90);
 	
	 LCD_goto(0,8);
	 LCD_writechar(3);
	 TMR0_delayms(90);
	 	
// 	LCD_writestr("MUSTAFA MOHAMMED");
// 	
// 	LCD_goto(1 , 1);
// 		
// 	LCD_writestr("HAWARY Sloiman");
// 	
//  	TMR0_delayms(2000);
//  	
//  	LCD_sendcmd(LCD_CLEAR);
// 	 
// 	 TMR0_delayms(20);
// 	
//  	LCD_writestr("Welcome !");
// 		
//  	TMR0_delayms(2000);	
	
}
