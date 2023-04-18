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


void APP_init()
{
	TMR0_init();
	
	LCD_init();
	
		TMR0_delayms(20);
		
	
}


void APP_start()
{
	
	LCD_goto(0 , 0);
	
	LCD_writestr("MUSTAFA MOHAMMED");
	
	LCD_goto(1 , 1);
		
	LCD_writestr("HAWARY Sloiman");
	
 	TMR0_delayms(2000);
 	
 	LCD_sendcmd(LCD_CLEAR);
	 
	 TMR0_delayms(20);
	
 	LCD_writestr("Welcome !");
		
 	TMR0_delayms(2000);	
	
}
