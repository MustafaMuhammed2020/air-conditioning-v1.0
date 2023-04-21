/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Configuration file of Timer 0                        */
/******************************************************************/
#include "ADC_interface.h"


void ADC_init(void)
{
	clear_bit(ADC_PORT_DIR,ADC_PIN); //use ADC Pin as input
	ADMUX=0;
	set_bit(ADMUX,6); //use AVCC ref.
	ADCSRA=0;
	set_bit(ADCSRA,7); //Enable the ADC
}

void ADC_start(float *sensorValue)
{
	uint16_t digitalVoltageValue=0;
	float analogVoltageValue=0.0;
	
	ADMUX |= (ADC_Ch_0 & 0x0f); //Choose channel to read
	
	set_bit(ADCSRA,6); //start conversion
	
	while((ADCSRA & (1<<4))==0); //wait for the conversion
	
	digitalVoltageValue = ADCL + (ADCH & 1) * 256 + ((ADCH&(1<<1))>>1)*512;
	
	analogVoltageValue = digitalVoltageValue * ADC_step;
	
	*sensorValue = analogVoltageValue / SENSOR_RESOLUTION; 
	
}