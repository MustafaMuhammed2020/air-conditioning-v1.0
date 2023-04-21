/***********************************************************************************/
/* Author    : Mustafa Mohammed Abdou                                              */
/* Date      : 16 April, 2023                                                      */
/* Version   : V01                                                                 */
/* Hint      : APP layer                                                           */
/***********************************************************************************/

#include "HAL/lcd/lcd_interface.h"
#include "MCAL/timer0/TMR0_interface.h"
#include <math.h>
int main(void)
{
	float value;
	TMR0_init();
    TMR0_delayms(100);
    LCD_4_bit_init();
	TMR0_delayms(100);
	LCD_4_bit_sendstring("Hello world");
	ADC_init();
    while (1) 
    {
		ADC_init();
		ADC_start(&value);
		int i,temp1,temp2;
		char str[6];
		temp1= (int)(value *100);
		for(i=0;i<5;i++)
		{
			temp2 = temp1%((int)(pow(10,5-i)));
			str[i] = (int)(temp2/(int)(pow(10,4-i)));
		}
		for(i=0;i<6;i++)
		{
			if(i<3)
			{
				LCD_4_bit_sendChar((str[i]+'0'));
			}
			else if(i==3)
			{
				LCD_4_bit_sendChar('.');
			}
			else
			{
				LCD_4_bit_sendChar((str[i-1]+'0'));
			}
			
		}
    }
}

