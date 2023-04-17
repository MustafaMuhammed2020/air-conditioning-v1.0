/***********************************************************************************/
/* Author    : Mustafa Mohammed Abdou                                              */
/* Date      : 16 April, 2023                                                      */
/* Version   : V01                                                                 */
/* Hint      : APP layer                                                           */
/***********************************************************************************/

#include "HAL/lcd/lcd_interface.h"
#include "MCAL/timer0/TMR0_interface.h"
int main(void)
{
    /* Replace with your application code */
    uint8_t val[] = "Hi! Omar";
    uint8_t val2[]= "Hello!";
	TMR0_init();
   // LCD_4_bit_init();
    LCD_8_bit_init();
    LCD_sendString(val2);
   // LCD_4_bit_sendCommand(Cursor_Reset_Line2);
   // LCD_8_bit_sendCommand(Cursor_Reset_Line2);
    //LCD_sendString(val2);

    while (1) 
    {
    }
}

