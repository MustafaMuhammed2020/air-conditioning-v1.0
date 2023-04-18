/******************************************************************/
/* Author  : Team2                                                */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Configuration file of Timer 0                        */
/******************************************************************/



#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

/** TYPEDEF TO RETURN THE STATUS OF FUNCTIONS **/
typedef enum {
    VALID_KEYPAD_INIT,
    NOT_VALID_KEYPAD_INIT
}KEYPAD_status;

/****************************************************************/
/** FUNCTION TO INITIALIZE KEY PAD */
/** ARGUMENTS : VOID */
/** RETURN : ERROR STATUS */
/****************************************************************/
KEYPAD_status KEYPAD_init(void) ;


/****************************************************************/
/** FUNCTION TO GET THE PRESSED KEY KEY PAD */
/** ARGUMENTS : VOID */
/** RETURN : uint8_t */
/****************************************************************/
uint8_t KEYPAD_getpressedkey(void) ;


#endif /* ADC_INTERFACE_H_ */
