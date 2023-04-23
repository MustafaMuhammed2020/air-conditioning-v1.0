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

#include "../HAL/keypad/KEYPAD_interface.h"
#include "../HAL/keypad/KEYPAD_config.h"

/** INCLUDE LAYER FILES **/
#include "app.h"

uint8_t u8_g_bell[8] =  { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00}; /** BELL SHAPE PATTERN **/
	
uint8_t u8_g_empty[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  /** EMPTY PATTERN **/

uint8_t bar ,  u8_a_defaulttemp = 20 ;

void APP_init()
{

    bar = 2 ;  /** INITIAL VALUE OF BAR **/
  
	ADC_init();  /** INITIALIZE ADC **/
	
 	TMR0_init();  /** INITIALIZE TMR0 **/
	
	LCD_init();   /** INITIALIZE LCD **/
	
	TMR0_delayms(50); /** DELAY FOR 20 ms FOR LCD TO BE STABLE BEFORE OPERATE */
		
	KEYPAD_init(); /** INITIALIZE KEYPAD **/
	
	LCD_writecustomchar(u8_g_bell , 0); /** STORE THE BELL SHAPE IN CGRAM OF LCD **/
	 
	LCD_writecustomchar(u8_g_empty , 1); /** STORE EMPTY SHAPE IN CGRAM OF LCD **/
	
	BUZZ_init();  /** INITIALIZE THE BUZZER **/
	
	BUZZ_off();   /** BUZZER IS OFF **/
	
	LCD_sendcmd(LCD_CLEAR); /** CLEAR THE LCD BEFORE WRITING ANYTHING **/
	TMR0_delayms(20);
	
	LCD_goto(0 , 1);
	LCD_writestr("   Welcome   ");  /** DISPLAY WELCOME MESSAGE FOR 0.5 SEC **/
	TMR0_delayms(1000);
	
	LCD_sendcmd(LCD_CLEAR);  /** CLEAR THE LCD **/
	TMR0_delayms(20);
	
	LCD_goto(0 , 0);
	LCD_writestr("Default temp =20"); /** DISPLAY THE DEFAULT TEMP OF AC **/
	TMR0_delayms(2000);

    LCD_sendcmd(LCD_CLEAR);  /** CLEAR THE LCD **/
    TMR0_delayms(20);
    
	LCD_goto(0 , 0);
	LCD_writestr("SET TEMPERATURE"); /** DISPLAY THE DEFAULT TEMP OF AC **/
	TMR0_delayms(2000);
	
	LCD_sendcmd(LCD_CLEAR);  /** CLEAR THE LCD **/
	TMR0_delayms(20);
	
	LCD_goto(0 , 0 );
	LCD_writestr("Min:18");
	
	LCD_goto(0 , 7);
	LCD_writeint(u8_a_defaulttemp); /** DISPLAY THE ROOM READ TEMPERATURE **/
	
	LCD_goto(0 , 10);
	LCD_writestr("Max:35");
	
	LCD_goto(1 , 0);
	LCD_writestr("||");  /** INITIAL PATTERN **/
	
	
}


void APP_start()
{
	KEYPAD_readError returnstatus = KEYPAD_readFail ;  /** AVRIABLE TO HOLD THE RETURN STATUS OF KEYPAD **/
	
	uint8_t u8_a_pressedunm = 0 , u32_a_temp = 0 , u8_a_currenttemp = 0   , u8_a_pattern = 0 ;

	returnstatus = KEYPAD_read(&u8_a_pressedunm); /** READ THE PRESSED BUTTON **/
	
	if(returnstatus == KEYPAD_readSuccess) /** HOLD HERE UNTILL A BUTTON PRESSED **/
	{
		if (u8_a_pressedunm == INCREASE_TEMP) /** IF 1 PRESSED **/
		{	
			u8_a_defaulttemp++ ;  /** INCREASE THE TEMPERATURE BY 1 **/
			
			if (u8_a_defaulttemp > MAX_TEMP) /** IF TEMPERATURE EXCEEDED THE MAX LIMIT **/
			{
				u8_a_defaulttemp = MAX_TEMP ; /* SET TEMPERATURE TO THE MAX LIMIT **/
			}
			
			else  /** TEMPERATURE VALUE IS VALID **/
			{
				LCD_goto(0 , 7);  
				LCD_writeint(u8_a_defaulttemp);  /** DISPLAY THE TEMPERATURE INCREASED BY THE USER **/
				
				LCD_goto(1 ,bar++); /** UPDATE THE BAR COUNTER **/
				LCD_writechar('|');
				TMR0_delayms(200);
			}	
		}
		
		else if(u8_a_pressedunm == DECREASE_TEMP)  /** IF 2 PRESSED **/
		{    
			u8_a_defaulttemp--; /** DECREASE THE TEMPERATURE BY 1 **/
			
			if (u8_a_defaulttemp < MIN_TEMP) /** IF TEMPERATURE WENT BELOW  THE MIN LIMIT **/
			{
				u8_a_defaulttemp = MIN_TEMP ; /* SET TEMPERATURE TO THE MIN LIMIT **/
			}
			
			LCD_goto(0 , 7);
			LCD_writeint(u8_a_defaulttemp); /** DISPLAY THE TEMPERATURE DECREASED BY THE USER **/
			
			LCD_goto(1 , --bar);
			LCD_writechar(1);    /** UPDATE THE BAR COUNTER **/
			TMR0_delayms(200);

		}
		
		else if(u8_a_pressedunm == SET_TEMP) /** IF 3 PRESSED **/
		{
			u8_a_pressedunm = 0 ; /** REINITIALIZE THE PRESSED NUMBER to 0 **/
			
			LCD_sendcmd(LCD_CLEAR); /** CLEAR THE LCD **/
			TMR0_delayms(20);
			
			while (u8_a_pressedunm != READJUST_TEMP && u8_a_pressedunm != REBOOT_SYSTEM)  /** WHILE USER DOESN'T NEED TO READJUST OR REBOOT THE SYSTEM **/
			{	
				u32_a_temp = ADC_read();  /** READ THE VALUE FROM ADC CHANNEL **/
				
				u8_a_currenttemp = u32_a_temp * 0.20 ; /** REFACTOR THE ADC READ TO BE DISPLAYED OVER THE LCD **/
				
				LCD_goto(0,0);
				LCD_writestr("Needed Temp :"); /** SET THE USER TEMPERATURE **/
				LCD_writeint(u8_a_defaulttemp);
				
				LCD_goto(1,0);
				LCD_writestr("Current Temp :");  /** DISPLAY THE ROOM TEMPERATURE **/
				LCD_writeint(u8_a_currenttemp);
				
				if (u8_a_currenttemp  > u8_a_defaulttemp) /** IF ROOM IS HOTTER THAN USER NEED **/
				{
					LCD_goto(0 , 15);
					LCD_writechar(0);  /** DISPLAY BELL SHAPE **/
					BUZZ_on();   /** BUZZER IS ON **/
				}
				
				else
				{
					LCD_goto(0 , 15);
					LCD_writechar(1);  /** REMOVE BELL SHAPE **/
					BUZZ_off();   /** BUZZER IS OFF **/
				}
				
				KEYPAD_read(&u8_a_pressedunm); /** ACCEPT NUMBER FROM USER 4 TO READJUST THE TEMP AND 5 TO REBOOT THE SYSTEM **/
			}
			
			if (u8_a_pressedunm == READJUST_TEMP) /** IF 4 PRESSED **/
			{	
				LCD_goto(0 , 15);
				LCD_writechar(1);  /** REMOVE BELL SHAPE **/
				BUZZ_off();   /** BUZZER IS OFF **/
					
				LCD_sendcmd(LCD_CLEAR); /** CLEAR THE LCD **/
				TMR0_delayms(20);
				
				LCD_goto(0,0);
				LCD_writestr("Readjust temp"); /** TELL USER ABOUT THE NEXT STEP **/
				TMR0_delayms(2000);
				
				LCD_sendcmd(LCD_CLEAR);
				TMR0_delayms(20);
				
				LCD_goto(0 , 0 );
				LCD_writestr("Min:18");
				
				LCD_goto(0 , 7);
				LCD_writeint(u8_a_defaulttemp); /** DISPLAY THE DEFAULT TEMPERATURE **/
				
				LCD_goto(0 , 10);
				LCD_writestr("Max:35");
				
				LCD_goto(1,0);
				
				u8_a_pattern = bar; 
				
				while (u8_a_pattern != 0 ) /** DRAW THE LAST STATUS OF BAR **/
				{
					LCD_writechar('|');
					u8_a_pattern = u8_a_pattern - 1 ;
				}
			}
			
			else if(u8_a_pressedunm == REBOOT_SYSTEM) /** IF 5 PRESSED **/
			{
				u8_a_defaulttemp = 20 ;  /** RESET THE DEFAULT VALUE **/
				
				LCD_sendcmd(LCD_CLEAR);
				TMR0_delayms(20);
				
				LCD_goto(0,0);
				LCD_writestr("System reboot ");
				TMR0_delayms(2000);
				
				APP_init(); /** START THE SYSTEM AGAIN **/
				APP_start();
				
			}	
		}
	}
}

