/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Configuration file ADC                               */
/******************************************************************/

#ifndef ADC_CONFIG_H
#define ADC_CONFIG_H

/***************************************************************/
/** CONFIGURE VOLTAGE REFERENCE                               **/
/**       CHOICES  :    1 - AREF_SOURCE                       **/  
/**                     2 - AVCC_SOURCE                       **/
/**                     3 - INTERNAL_SOURCE                   **/
/***************************************************************/                   
#define   ADC_VOLTAGE_REFRENCE         AVCC_SOURCE

/***************************************************************/
/** CONFIGURE DIGITAL VALUE REPRESENTATION                    **/
/**       CHOICES  :    1 - RIGHT_ADJUST                      **/
/**                     2 - LEFT_ADJUST                       **/
/***************************************************************/
#define   ADC_ADjUST                   RIGHT_ADJUST

/***************************************************************/
/** CONFIGURE ADC CHANNEL                                     **/
/**       CHOICES  :    1 - CHANNEL0                          **/
/**                     2 - CHANNEL1                          **/
/**                     3 - CHANNEL2                          **/
/**                     4 - CHANNEL3                          **/
/**                     5 - CHANNEL4                          **/
/**                     6 - CHANNEL5                          **/
/**                     7 - CHANNEL6                          **/
/**                     8 - CHANNEL7                          **/
/***************************************************************/
#define   ADC_CHANNEL                  CHANNEL0

/***************************************************************/
/** CONFIGURE ADC PRESCALLER                                  **/
/**       CHOICES  :    1 - PRESCALER2                        **/
/**                     2 - PRESCALER4                        **/
/**                     3 - PRESCALER8                        **/
/**                     4 - PRESCALER16                       **/
/**                     5 - PRESCALER128                      **/
/***************************************************************/
#define   ADC_PRESCALER                PRESCALER4

/***************************************************************/
/** CONFIGURE ADC INTERRUPT STATUS                            **/
/**       CHOICES  :    1 - ADC_INT_DISABLED                  **/
/**                     2 - ADC_INT_ENABLED                   **/
/***************************************************************/
#define   ADC_INTERRUPT_STATUS         ADC_INT_DISABLED

/***************************************************************/
/** CONFIGURE ADC OPERATING MODE                              **/
/**       CHOICES  :    1 - AUTO_RUNNING_MODE                 **/
/**                     2 - EXTERNAL_INT0                     **/
/***************************************************************/
#define   ADC_CONVERSION_TRIGGER       AUTO_RUNNING_MODE




#endif /* ADC_CONFIG_H */
