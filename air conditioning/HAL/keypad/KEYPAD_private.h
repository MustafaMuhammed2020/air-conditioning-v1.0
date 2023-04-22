/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Configuration file of Timer 0                        */
/******************************************************************/

#ifndef KEYPAD_PRIVATE_H_
#define KEYPAD_PRIVATE_H_

#define NULL (void *) 0x00
#define KEYPADSIZE 3
uint8_t Col_Arr[3] = {COL_1, COL_2, COL_3};
uint8_t Row_Arr[3] = {ROW_1, ROW_2, ROW_3};
uint8_t Button_Arr[3][3]=
{   
    //COLUMN 1
    {BUTTON1, BUTTON4, BUTTON7},
    //COLUMN 2
    {BUTTON2, BUTTON5, BUTTON8},
    //COLUMN 3
    {BUTTON3, BUTTON6, BUTTON9}
};





#endif /* ADC_PRIVATE_H_ */
