/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Configuration file of Timer 0                        */
/******************************************************************/



#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_


#define ADC_PORT_DIR DDRA

#define ADC_PIN 0

#define Vref 5

#define ADC_step Vref/1024.0

#define SENSOR_RESOLUTION (float)0.3


#endif /* ADC_CONFIG_H_ */