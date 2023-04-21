/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Configuration file of Timer 0                        */
/******************************************************************/



#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#include "../../SERVICE/standard_types.h"
#include "../../SERVICE/registers.h"
#include "../../SERVICE/common_macros.h"

#include "ADC_config.h"
#include "ADC_private.h"



void ADC_init(void);

void ADC_start(float *sensorValue);



#endif /* ADC_INTERFACE_H_ */