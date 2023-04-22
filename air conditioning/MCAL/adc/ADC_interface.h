/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : APIs of ADC module                                   */
/******************************************************************/

/** INCLUDE LIBRARIES **/
#include "../../SERVICE/common_macros.h"
#include "../../SERVICE/standard_types.h"


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/** VOLTAGE REFERENCE OF ADC **/
#define  AREF_SOURCE      0
#define  AVCC_SOURCE      1
#define  INTERNAL_SOURCE  2

/** DIFFERENT ADC CHANNELS **/
#define CHANNEL0            0
#define CHANNEL1            1
#define CHANNEL2            2
#define CHANNEL3            3
#define CHANNEL4            4
#define CHANNEL5            5
#define CHANNEL6            6
#define CHANNEL7            7

/** OPERATING MODE OF ADC **/
#define AUTO_RUNNING_MODE   0
#define EXTERNAL_INT0       1

/** DIGITAL VALUE REPRESENTATION **/
#define  RIGHT_ADJUST       0
#define  LEFT_ADJUST        1

/** INTERRUPT CONTROL OF ADC **/
#define ADC_INT_ENABLED     0
#define ADC_INT_DISABLED    1

/** PRESCALLER VALUES **/
#define PRESCALER2          0
#define PRESCALER4          1
#define PRESCALER8          2
#define PRESCALER16         3
#define PRESCALER128        4


typedef enum { VALID_ADC_INIT , NOT_VALID_ADC_INIT } ADC_initstatus ;
/***********************************************************/
/** FUNCTION TO INITIALIZE ADC                             */
/** AGUMENTS  : VOID                                       */
/** RETURNS   : ERROR STATUS                               */
/***********************************************************/
ADC_initstatus ADC_init(void);


/***********************************************************/
/** FUNCTION TO READ THE VALUE OF ADC                      */
/** AGUMENTS  : VOID                                       */
/** RETURNS   : uint16_t (ANALOG VALUE)                    */
/***********************************************************/
uint32_t ADC_read(void);





#endif /* ADC_INTERFACE_H_ */