/***********************************************************************************/
/* Author    : Mustafa Mohammed Abdou                                              */
/* Date      : 16 April, 2023                                                      */
/* Version   : V01                                                                 */
/* Hint      : APP layer                                                           */
/***********************************************************************************/


#ifndef APP_H_
#define APP_H_

#include "../SERVICE/standard_types.h"


/*** SOME MACROS DESCRIBES USER INPUT FROM KEYPAD **/
#define INCREASE_TEMP      1
#define DECREASE_TEMP      2
#define SET_TEMP           3
#define READJUST_TEMP      4
#define REBOOT_SYSTEM      5


/** MACROS FOR TEMPERATURE LIMITS **/
#define MAX_TEMP           35
#define MIN_TEMP           18

/** APLICATION APIs **/
void APP_init();
void APP_start();



#endif /* APP_H_ */