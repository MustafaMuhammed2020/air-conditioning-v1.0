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

#include "../MCAL/tmer1/timer1_interface.h"
#include "../MCAL/tmer1/timer1_config.h"

void APP_init()
{
	TMR1_init();
	
	LCD_init();
	
	LCD_sendcmd(LCD_CLEAR);
	
	LCD_goto(1 , 1);
	
	LCD_writestr("Allah Akbar");
	
}


void APP_start()
{
	
	
	
}
