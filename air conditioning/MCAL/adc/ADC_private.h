/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : private file of DC                                   */
/******************************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/*************** ADC Registers ********************/

#define SFIOR    (* (volatile uint8_t *) (0x50))
#define ADCSRA   (* (volatile uint8_t *) (0x26))
#define ADMUX    (* (volatile uint8_t *) (0x27))
#define ADCH     (* (volatile uint8_t *) (0x25))
#define ADCL     (* (volatile uint8_t *) (0x24))
#define ADC_VAL  (* (volatile uint16_t*) (0x24))



#endif /* ADC_PRIVATE_H_ */