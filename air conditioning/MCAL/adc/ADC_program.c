/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Configuration file of Timer 0                        */
/******************************************************************/

/** INCLUDE LIBRARIES **/
#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"

#include "../dio/DIO_interface.h"

/** INCLUDE DRIVER FILES **/
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

/***********************************************************/
/** FUNCTION TO INITIALIZE ADC                             */
/** AGUMENTS  : VOID                                       */
/** RETURNS   : ERROR STATUS                               */
/***********************************************************/
ADC_initstatus ADC_init(void)
{
	/** SET THE VOLTAGE REFERENCE AS IT'S CONFIGURED **/
 	#if   ADC_VOLTAGE_REFRENCE   ==      AVCC_SOURCE
 	set_bit(ADMUX , 6);
 	clear_bit(ADMUX , 7);
	
	#elif  ADC_VOLTAGE_REFRENCE  ==     INTERNAL_SOURCE
	set_bit(ADMUX , 6);
	set_bit(ADMUX , 7);
	
	#elif  ADC_VOLTAGE_REFRENCE  ==     AREF_SOURCE
	clear_bit(ADMUX , 6);
	clear_bit(ADMUX , 7);
	
	#endif
	
	
	#if   ADC_CHANNEL           ==     CHANNEL1
	set_bit(ADMUX , 0);
	DIO_setpindir(DIO_PORTA , DIO_PIN1 , DIO_PIN_INPUT); /** SET THE DIRECION OF PIN CHANNEL AS INPUT **/
	
	#elif   ADC_CHANNEL           ==     CHANNEL0
	DIO_setpindir(DIO_PORTA , DIO_PIN0 , DIO_PIN_INPUT); /** SET THE DIRECION OF PIN CHANNEL AS INPUT **/
	
	#elif   ADC_CHANNEL           ==     CHANNEL2
	set_bit(ADMUX , 1);
	DIO_setpindir(DIO_PORTA , DIO_PIN2 , DIO_PIN_INPUT); /** SET THE DIRECION OF PIN CHANNEL AS INPUT **/
	
	#elif   ADC_CHANNEL           ==     CHANNEL3
	set_bit(ADMUX , 0);
	set_bit(ADMUX , 1);
	DIO_setpindir(DIO_PORTA , DIO_PIN3 , DIO_PIN_INPUT); /** SET THE DIRECION OF PIN CHANNEL AS INPUT **/
	
	#elif   ADC_CHANNEL           ==     CHANNEL4
	set_bit(ADMUX , 2);
	DIO_setpindir(DIO_PORTA , DIO_PIN4 , DIO_PIN_INPUT); /** SET THE DIRECION OF PIN CHANNEL AS INPUT **/
	
	#elif   ADC_CHANNEL           ==     CHANNEL5
	set_bit(ADMUX , 0);
	set_bit(ADMUX , 2);
	DIO_setpindir(DIO_PORTA , DIO_PIN5 , DIO_PIN_INPUT); /** SET THE DIRECION OF PIN CHANNEL AS INPUT **/
	
	#elif   ADC_CHANNEL           ==     CHANNEL6
	set_bit(ADMUX , 1);
	set_bit(ADMUX , 2);
	DIO_setpindir(DIO_PORTA , DIO_PIN6 , DIO_PIN_INPUT); /** SET THE DIRECION OF PIN CHANNEL AS INPUT **/
	
	#elif   ADC_CHANNEL           ==     CHANNEL7
	set_bit(ADMUX , 0);
	set_bit(ADMUX , 1);
	set_bit(ADMUX , 2);
	DIO_setpindir(DIO_PORTA , DIO_PIN7 , DIO_PIN_INPUT); /** SET THE DIRECION OF PIN CHANNEL AS INPUT **/
	
	#endif
	
	 	/** SET THE PRESCALLER VALUE **/
	#if  ADC_PRESCALER          ==      PRESCALER128
		set_bit(ADCSRA , 0);
		set_bit(ADCSRA , 1);
		set_bit(ADCSRA , 2);
		
	#elif  ADC_PRESCALER          ==      PRESCALER16
		 set_bit(ADCSRA , 2);
		
	#elif  ADC_PRESCALER          ==      PRESCALER8
		 set_bit(ADCSRA , 0);
		 set_bit(ADCSRA , 1);
		
	#elif  ADC_PRESCALER          ==      PRESCALER4
		 set_bit(ADCSRA , 1);
			 
	#elif  ADC_PRESCALER          ==      PRESCALER2
	     set_bit(ADCSRA , 0);
	     
	#endif
	
	/** SET THE ADJUSTING MODE OF ADC VALUE  **/
	#if    ADC_ADjUST            ==     RIGHT_ADJUST
	clear_bit(ADMUX , 5);
	
	#elif    ADC_ADjUST          ==     LEFT_ADJUST
	set_bit(ADMUX , 5);
	
	#endif
		
	/** SET THE OPERATING MODE OF ADC **/
	#if  ADC_CONVERSION_TRIGGER  ==    AUTO_RUNNING_MODE
	set_bit(ADCSRA , 5);
	
 	#elif  ADC_CONVERSION_TRIGGER  ==    EXTERNAL_INT0
 	set_bit(SFIOR , 6);
 	#endif
 	
	 
	/** ADC INTERRUPT STATUS **/
	#if  ADC_INTERRUPT_STATUS   ==     ADC_INT_DISABLED
	
	clear_bit(ADCSRA , 3);
	
 	#elif  ADC_INTERRUPT_STATUS   ==     ADC_INT_ENABLED
 	
 	set_bit(SREG , 7);
 	set_bit(ADCSRA , 3);
	#endif
	
	/** Enable  ADC **/
	set_bit(ADCSRA , 7);
}


/***********************************************************/
/** FUNCTION TO READ THE VALUE OF ADC                      */
/** AGUMENTS  : VOID                                       */
/** RETURNS   : uint16_t (ANALOG VALUE)                    */
/***********************************************************/
uint32_t ADC_read(void)
{
	uint32_t u16_a_analogvalue = 0;
		
	set_bit(ADCSRA , 6); /** SATRT CONVERSION **/
	
	while( (ADCSRA & (1 << 4)) == 0); /** WAIT UNTILL CONVERSION ENDS **/
	
	u16_a_analogvalue = ADC_VAL ; /** GET THE VALUE FORM ADC VALUE REGISTER **/
	 
	return u16_a_analogvalue; /** RETURN THE ANALOG VALUE **/ 
}