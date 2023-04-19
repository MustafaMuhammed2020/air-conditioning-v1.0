/***********************************************************************************/
/* Author    : Mustafa Mohammed Abdou                                              */
/* Date      : 16 April, 2023                                                      */
/* Version   : V01                                                                 */
/* Hint      : APP layer                                                           */
/***********************************************************************************/

/** INCLUDE LIBRARIES **/
#include "../SERVICE/common_macros.h"
#include "../SERVICE/standard_types.h"

/** INCLUDE INTERFACE FILES OF LOWER LAYERS **/
#include "../HAL/lcd/LCD_interface.h"
#include "../HAL/lcd/LCD_config.h"

#include "../MCAL/dio/DIO_interface.h"
#include "../MCAL/dio/DIO_private.h"

#include "../MCAL/timer0/TMR0_interface.h"
#include "../MCAL/timer0/TMR0_config.h"

#include "../MCAL/adc/ADC_interface.h"

#include "../HAL/buzzer/buzzer_interface.h"

uint8_t u8_g_bell[8] =   { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00}; /** BELL SHAPE PATTERN **/
	
uint8_t u8_g_nobell[8] =   { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; /** EMPTY PATTERN **/

uint32_t u32_a_temp = 0 ; /** GLOBAL VARIABLE FOR TEMPERATURE **/

void APP_init()
{

	ADC_init();  /** INITIALIZE ADC **/
	
	TMR0_init();  /** INITIALIZE TMR0 **/
	
	LCD_init();   /** INITIALIZE LCD **/
	
	TMR0_delayms(20); /** DELAY FOR 20 ms FOR LCD TO BE STABLE BEFORE OPERATE */
		
	LCD_writecustomchar(u8_g_bell , 0); /** STORE THE BELL SHAPE IN CGRAM OF LCD **/
	 
	LCD_writecustomchar(u8_g_nobell , 1); /** STORE EMPTY SHAPE IN CGRAM OF LCD **/
	
	BUZZ_init();  /** INITIALIZE THE BUZZER **/
	
	BUZZ_off();   /** BUZZER IS OFF **/
	
}


void APP_start()
{
		
	u32_a_temp = ADC_read();  /** READ THE VALUE FROM ADC CHANNEL **/
	
	LCD_goto(1,11); /** DISPLAY THE ADC READ ON LCD **/
	LCD_writeint(u32_a_temp);
	
	if (u32_a_temp > 500) /** IF ADC READ BIGGER THN 500 **/
	{
		LCD_goto(1,2); 
		LCD_writestr("Temp = ");
		
		BUZZ_on(); /** START THE BUZZER INDICATOR **/
		
		LCD_goto(0,8); /** DRAW BELL SHAPE **/
		LCD_writechar(0);
	}
	
	else /** ADC READ LES THAN 500 **/
	{
		
		LCD_goto(1,2);
		LCD_writestr("Temp = ");
		
		BUZZ_off();  /** STOP THE BUZZER **/
		
		LCD_goto(0,8); /** REMOVE BELL SHAPE **/
		LCD_writechar(1);
	}
	

	
}
