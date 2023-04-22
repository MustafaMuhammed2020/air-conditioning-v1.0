/******************************************************************/
/* Author  : Team2                            */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Configuration file of Timer 0                        */
/******************************************************************/

/** INCLUDE DRIVER FILES **/
#include"KEYPAD_config.h"
#include"KEYPAD_interface.h"
#include"KEYPAD_private.h"

/** INCLUDE LIBRARIES **/
#include "KEYPAD_interface.h"


void KEYPAD_init(void){
/* Set Columns direction to Output */
DIO_setpindir(DIO_PORTA,COL_1,DIO_PIN_OUTPUT);
DIO_setpindir(DIO_PORTA,COL_2,DIO_PIN_OUTPUT);
DIO_setpindir(DIO_PORTA,COL_3,DIO_PIN_OUTPUT);
  
/* Set Rows direction to Input */
DIO_setpindir(DIO_PORTA,ROW_1,DIO_PIN_INPUT);
DIO_setpindir(DIO_PORTA,ROW_2,DIO_PIN_INPUT);
DIO_setpindir(DIO_PORTA,ROW_3,DIO_PIN_INPUT);  
  
/*Set Column Initial Values to 1 */
DIO_setpinvalue(DIO_PORTA,COL_1,DIO_PIN_HIGH);
DIO_setpinvalue(DIO_PORTA,COL_2,DIO_PIN_HIGH);
DIO_setpinvalue(DIO_PORTA,COL_3,DIO_PIN_HIGH) ;

/* Enable Pull Up Resistors at Input Rows */
DIO_setpinvalue(DIO_PORTA,ROW_1,DIO_PIN_HIGH);
DIO_setpinvalue(DIO_PORTA,ROW_2,DIO_PIN_HIGH);
DIO_setpinvalue(DIO_PORTA,ROW_3,DIO_PIN_HIGH);
  
}




uint8_t KEYPAD_getpressedkey(void){
  
	uint8_t rowValue;
  for (uint8_t counter_col = 0; counter_col < KEYPADSIZE; counter_col++)
    {
      //set pins in ColumnArray to HIGH
      DIO_setpinvalue(DIO_PORTA,Col_Arr[counter_col], DIO_PIN_HIGH);
     } 
  
    //Scan all keypad columns
    for (uint8_t counter_col = 0; counter_col < KEYPADSIZE; counter_col++)
        {
            //activate current colmun
           DIO_setpinvalue(DIO_PORTA,Col_Arr[counter_col], DIO_PIN_LOW);
            for (uint8_t counter_row = 0; counter_row < KEYPADSIZE; counter_row++)
            {
              //check row value if it is 0 then this column and row is connected
              DIO_readpin(DIO_PORTA, Row_Arr[counter_row],&rowValue);              
              if (rowValue == 0)
                {
                    //Return pressed button value
                      return Button_Arr[counter_col][counter_row];
                }       
           }
      //set current column pin HIGH again
	      DIO_setpinvalue(DIO_PORTA,Col_Arr[counter_col], DIO_PIN_HIGH);
}
  
  //Report no Button pressed
  return "?";

}
