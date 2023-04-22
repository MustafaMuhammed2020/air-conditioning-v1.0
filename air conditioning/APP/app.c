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

#include "app.h"

uint8_t u8_g_bell[8] =  { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00}; /** BELL SHAPE PATTERN **/
	
uint8_t u8_g_empty[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  /** EMPTY PATTERN **/

sint8_t bar = 0 ,  u8_a_defaulttemp = 20 , u8_readjuststatus = 0 ;

void APP_init()
{

    bar = 0 ;
  
	ADC_init();  /** INITIALIZE ADC **/
	
 	TMR0_init();  /** INITIALIZE TMR0 **/
	
	LCD_init();   /** INITIALIZE LCD **/
	
	TMR0_delayms(50); /** DELAY FOR 20 ms FOR LCD TO BE STABLE BEFORE OPERATE */
		
	KEYPAD_init(); /** INITIALIZE KEYPAD **/
	
	LCD_writecustomchar(u8_g_bell , 0); /** STORE THE BELL SHAPE IN CGRAM OF LCD **/
	 
	LCD_writecustomchar(u8_g_empty , 1); /** STORE EMPTY SHAPE IN CGRAM OF LCD **/
	
	BUZZ_init();  /** INITIALIZE THE BUZZER **/
	
	BUZZ_off();   /** BUZZER IS OFF **/
	
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
	
}


void APP_start()
{
	KEYPAD_readError returnstatus = KEYPAD_readFail ;  
	
	uint8_t u8_a_pressedunm = 0 , u32_a_temp = 0 , u8_a_displayedtemp = 0   , pattern = 0; /** VARIABLE TO HOLD THE PRESSED NUMBER IN THE KEYPAD **/


	returnstatus = KEYPAD_read(&u8_a_pressedunm);
	
	LCD_goto(0 , 0 );
	LCD_writestr("Min:18");
	
	LCD_goto(0 , 7);
	LCD_writeint(u8_a_defaulttemp); /** DISPLAY THE ROOM READ TEMPERATURE **/
	
	LCD_goto(0 , 10);
	LCD_writestr("Max:35");
	
	if(returnstatus == KEYPAD_readSuccess)
	{
		if (u8_a_pressedunm == 1)
		{	
		   	
			u8_a_defaulttemp++ ;
				
			LCD_goto(0 , 7);
			LCD_writeint(u8_a_defaulttemp); /** DISPLAY THE ROOM READ TEMPERATURE **/
				
			LCD_goto(1 ,bar++);
			LCD_writechar('|');
				
			TMR0_delayms(200);
			
		}
		
		else if(u8_a_pressedunm == 2)
		{
			bar-- ; 
	
			u8_a_defaulttemp--;
			
			LCD_goto(0 , 7);
			LCD_writeint(u8_a_defaulttemp); /** DISPLAY THE ROOM READ TEMPERATURE **/
			
			LCD_goto(1 , bar+1);
			LCD_writechar(1);
			TMR0_delayms(200);

		}
		
		else if(u8_a_pressedunm == 3)
		{
			u8_a_pressedunm = 0 ;
			
			LCD_sendcmd(LCD_CLEAR);
			TMR0_delayms(20);
			
			while (u8_a_pressedunm != 4 && u8_a_pressedunm != 5)
			{	
				u32_a_temp = ADC_read();  /** READ THE VALUE FROM ADC CHANNEL **/
				
				u8_a_displayedtemp = u32_a_temp * 0.20 ; /** REFACTOR THE ADC READ TO BE DISPLAYED OVER THE LCD **/
				
				LCD_goto(0,0);
				LCD_writestr("Nedded Temp:");
				LCD_writeint(u8_a_defaulttemp);
				
				LCD_goto(1,0);
				LCD_writestr("Current Temp :");
				LCD_writeint(u8_a_displayedtemp);
				
				KEYPAD_read(&u8_a_pressedunm);
			}
			
			if (u8_a_pressedunm == 4)
			{
				u8_readjuststatus = 1 ; /** MEANS THAT WE WILL READJUST TEMPERATURE **/
				
				LCD_sendcmd(LCD_CLEAR);
				TMR0_delayms(20);
				
				LCD_goto(0,0);
				LCD_writestr("Readjust temp");
				TMR0_delayms(2000);
				
				LCD_sendcmd(LCD_CLEAR);
				TMR0_delayms(20);
				
				LCD_goto(1,0);
				
				pattern = bar ; 
				
				while (pattern != 0 )
				{
					LCD_writechar('|');
					pattern = pattern - 1 ;
				}
			}
			
			else if(u8_a_pressedunm == 5)
			{
				u8_a_defaulttemp = 20 ;
				
				LCD_sendcmd(LCD_CLEAR);
				TMR0_delayms(20);
				
				LCD_goto(0,0);
				LCD_writestr("System reboot ");
				
				TMR0_delayms(2000);
				APP_start();
				
				LCD_sendcmd(LCD_CLEAR);
				TMR0_delayms(20);
			}
			
		}
		
		
	}
	
	
	
	
}

