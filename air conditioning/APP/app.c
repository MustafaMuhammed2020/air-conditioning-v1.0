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

#include "../MCAL/dio/DIO_interface.h"
#include "../MCAL/dio/DIO_private.h"
#include "../MCAL/timer0/TMR0_interface.h"
#include "../MCAL/timer0/TMR0_config.h"
#include "../MCAL/adc/ADC_interface.h"



uint8_t u8_g_bell[8] =   { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};
	
uint8_t u8_g_nobell[8] =   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uint32_t u32_a_temp = 0 ;

void APP_init()
{

	ADC_init();
	
	TMR0_init();
	
	LCD_init();
	
	TMR0_delayms(20);
		
	LCD_writecustomchar(u8_g_bell , 0);
	
	LCD_writecustomchar(u8_g_nobell , 1);
	
	DIO_setpindir(DIO_PORTA , DIO_PIN3 , DIO_PIN_OUTPUT);  /** BUZZER **/
	
	DIO_setpinvalue(DIO_PORTA , DIO_PIN3 , DIO_PIN_LOW); /** BUZZER IS OFF **/
	
}


void APP_start()
{
		
	u32_a_temp = ADC_read();
	
	LCD_goto(1,11);
	LCD_writeint(u32_a_temp);
	
	if (u32_a_temp > 500)
	{
		LCD_goto(1,2);
		
		LCD_writestr("Temp = ");
		
		DIO_setpinvalue(DIO_PORTA , DIO_PIN3 , DIO_PIN_HIGH);
		
		LCD_goto(0,8);
		LCD_writechar(0);
	}
	
	else
	{
		
		LCD_goto(1,2);
		
		LCD_writestr("Temp = ");
		
		DIO_setpinvalue(DIO_PORTA , DIO_PIN3 , DIO_PIN_LOW);
		
		LCD_goto(0,8);
		LCD_writechar(1);
	}
	
//  	LCD_goto(0,8);
//  	LCD_writechar(0);
//  	TMR0_delayms(90);
// 	 
// 	TMR0_delayms(2000);
// 	
// 	LCD_sendcmd(LCD_CLEAR);
// 	
// 	TMR0_delayms(20);
	
//  	LCD_goto(0,8);
//  	LCD_writechar(1);
//  	TMR0_delayms(90);
//  	
// 	 LCD_goto(0,8);
// 	 LCD_writechar(2);
// 	 TMR0_delayms(90);
//  	
// 	 LCD_goto(0,8);
// 	 LCD_writechar(1);
// 	 TMR0_delayms(90);
//  	
// 	 LCD_goto(0,8);
// 	 LCD_writechar(0);
// 	 TMR0_delayms(90);
// 	 
// 	 LCD_goto(0,8);
// 	 LCD_writechar(3);
// 	 TMR0_delayms(90);
//  	
// 	 LCD_goto(0,8);
// 	 LCD_writechar(4);
// 	 TMR0_delayms(90);
//  	
// 	 LCD_goto(0,8);
// 	 LCD_writechar(3);
// 	 TMR0_delayms(90);
	 	
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
// 	 
// 	 LCD_sendcmd(LCD_CLEAR);
// 	 
// 	 TMR0_delayms(20);
	
}
