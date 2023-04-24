/******************************************************************/
/* Author  : Team2                            */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Configuration file of Timer 0                        */
/******************************************************************/

/** INCLUDE DRIVER FILES **/
#include "KEYPAD_config.h"
#include "KEYPAD_interface.h"
#include "KEYPAD_private.h"

/** INCLUDE LIBRARIES **/
#include "KEYPAD_interface.h"

uint8_t Col_Arr[3] = {COL_1, COL_2, COL_3};
uint8_t Row_Arr[3] = {ROW_1, ROW_2, ROW_3};
uint8_t Button_Arr[3][3] =
    {
        // COLUMN 1
        {BUTTON1, BUTTON2, BUTTON3},
        // COLUMN 2
        {BUTTON4, BUTTON5, BUTTON6},
        // COLUMN 3
        {BUTTON7, BUTTON8, BUTTON9}};

void KEYPAD_init(void)
{
  /* Set Columns direction to Output */
  DIO_setpindir(DIO_PORTC, COL_1, DIO_PIN_INPUT);
  DIO_setpindir(DIO_PORTC, COL_2, DIO_PIN_INPUT);
  DIO_setpindir(DIO_PORTC, COL_3, DIO_PIN_INPUT);

  /* Set Rows direction to Input */
  DIO_setpindir(DIO_PORTC, ROW_1, DIO_PIN_OUTPUT);
  DIO_setpindir(DIO_PORTC, ROW_2, DIO_PIN_OUTPUT);
  DIO_setpindir(DIO_PORTC, ROW_3, DIO_PIN_OUTPUT);

  /*Set Column Initial Values to 1 */
  DIO_setpinvalue(DIO_PORTC, COL_1, DIO_PIN_HIGH);
  DIO_setpinvalue(DIO_PORTC, COL_2, DIO_PIN_HIGH);
  DIO_setpinvalue(DIO_PORTC, COL_3, DIO_PIN_HIGH);

  /* Enable Pull Up Resistors at Input Rows */
  DIO_setpinvalue(DIO_PORTC, ROW_1, DIO_PIN_HIGH);
  DIO_setpinvalue(DIO_PORTC, ROW_2, DIO_PIN_HIGH);
  DIO_setpinvalue(DIO_PORTC, ROW_3, DIO_PIN_HIGH);
}

uint8_t KEYPAD_getpressedkey(void)
{

  uint8_t colValue;

  // Scan all keypad columns
  for (uint8_t counter_row = 0; counter_row < KEYPADSIZE; counter_row++)
  {
    // activate current colmun
    DIO_setpinvalue(DIO_PORTC, Row_Arr[counter_row], DIO_PIN_LOW);

    for (uint8_t counter_col = 0; counter_col < KEYPADSIZE; counter_col++)
    {
      // check row value if it is 0 then this column and row is connected
      DIO_readpin(DIO_PORTC, Col_Arr[counter_col], &colValue);
      if (colValue == 0)
      {
        // Return pressed button value
        DIO_setpinvalue(DIO_PORTC, Row_Arr[counter_row], DIO_PIN_HIGH);
        return Button_Arr[counter_row][counter_col];
      }
    }
    // set current column pin HIGH again
    DIO_setpinvalue(DIO_PORTC, Row_Arr[counter_row], DIO_PIN_HIGH);
  }

  // Report no Button pressed
  return 0;
}
