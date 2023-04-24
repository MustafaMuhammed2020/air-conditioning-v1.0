/*
 * File: app.c
 * Created Date: Friday, April 21st 2023, 3:47:08 pm
 * Author: Omar Taha
 * -----
 * Copyright (c) 2023 Omar Taha <<https://github.com/OmarAshrafTaha>>
 */

#include "app.h"

uint8_t u8_g_barCount;
uint8_t u8_g_requiredTemp;
uint16_t u16_gs_currentCount;

uint8_t u8_g_bell_center[8] = {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};
uint8_t u8_g_bell_midRight[8] = {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x02, 0x00};
uint8_t u8_g_bell_topRight[8] = {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x01, 0x00, 0x08};
uint8_t u8_g_bell_midLeft[8] = {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x08, 0x00};
uint8_t u8_g_bell_topLeft[8] = {0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x10, 0x00, 0x08};

/***************************************************************************/
/** @brief Initializes all application modules and sets global variables   */
/** @param void                                                            */
/** @return APP_initSuccess                                                */
/** @return APP_initFail                                                   */
/***************************************************************************/
APP_initError APP_init(void)
{
    /*Initialize global variables*/
    u8_g_barCount = 0;
    u8_g_requiredTemp = 20;
    u16_gs_currentCount = 0;
    TMR0_init();
    /*All modules intializations*/
    LCD_init();
    KEYPAD_init();
    ADC_init();

    /*Timer 2 Initialization*/

	SREG |= (1 << 7);                              // enable global interrupt
	TIMSK |= (1 << 6);                             // enable timer 2 interrupt
    TIMER2_normalMode();                           // Set timer 2 to normal mode
    set_TIMER2_OVF_callBack(get_current_overflow); /*Set the timer 2 callback function*/

    APP_printString(0, 4, "Welcome");               /*Welcome Screen*/
    LCD_createCustomCharacter(u8_g_bell_center, 0); /*Adding custom characters to CGRAM*/
    TMR0_delaymicros(1000000);
    LCD_sendCommand(Clear_Screen);

    /*Print the default temprature*/
    APP_printString(0, 0, "Default Temp 20");
    TMR0_delaymicros(1000000);

    /*Call the set temprature function*/
    APP_setTemp();

    return APP_initSuccess;
}

/***************************************************************************/
/** @brief Prints a string to the LCD                                      */
/** @param u8_a_row row to print into                                      */
/** @param u8_a_column column to print into                                */
/** @param u8_a_str string to be printed in the passed coordinates         */
/** @return void                                                           */
/***************************************************************************/
void APP_printString(uint8_t u8_a_row, uint8_t u8_a_column, uint8_t *u8_a_str)
{
    LCD_goTo(u8_a_row, u8_a_column); /*Sets the cursor position to the passed row and column number*/
    LCD_sendString(u8_a_str);        /*Sends the passed string to the LCD*/
}

/***************************************************************************/
/** @brief Prints a character to the LCD                                   */
/** @param u8_a_row row to print into                                      */
/** @param u8_a_column column to print into                                */
/** @param u8_a_char character to be printed in the passed coordinates     */
/** @return void                                                           */
/***************************************************************************/
void APP_printChar(uint8_t u8_a_row, uint8_t u8_a_column, uint8_t u8_a_char)
{
    LCD_goTo(u8_a_row, u8_a_column); /*Sets the cursos position to the passed row and column number*/
    LCD_sendChar(u8_a_char);         /*Sends the passed character to the LCD*/
}

/***************************************************************************/
/** @brief Prints an integer to the LCD                                    */
/** @param u8_a_row row to print into                                      */
/** @param u8_a_column column to print into                                */
/** @param u8_a_integer integer to be printed in the passed coordinates    */
/** @return void                                                           */
/***************************************************************************/
void APP_printInteger(uint8_t u8_a_row, uint8_t u8_a_column, uint16_t u16_a_integer)
{
    LCD_goTo(u8_a_row, u8_a_column); /*Sets the cursos position to the passed row and column number*/
    LCD_sendInteger(u16_a_integer);  /*Sends the passed integer to the LCD*/
}

/***************************************************************************/
/** @brief Increments the bar resembling the temprature value              */
/** @param void                                                            */
/** @return void                                                           */
/***************************************************************************/
void APP_incrementBar()
{
    APP_printChar(1, u8_g_barCount, '|'); /*Prints '|' which resembles the temprature value*/

    u8_g_barCount++;        /*increments the u8_g_barCount which the next empty space available to write in*/
    u8_g_requiredTemp++; /*increments the required temprature*/

    APP_printInteger(0, 7, u8_g_requiredTemp); /*update the temprature on the LCD*/

    if (u8_g_barCount > 16) /*Check if the cursor is incrementing outside the LCD range*/
    {
        u8_g_barCount = 16;
    }
}

/***************************************************************************/
/** @brief Decrements the bar resembling the temprature value              */
/** @param void                                                            */
/** @return void                                                           */
/***************************************************************************/
void APP_decrementBar()
{
    u8_g_barCount--;        /*decrements the u8_g_barCount to set the cursor on the last printed value to be able to clear it*/
    u8_g_requiredTemp--; /*decrements the required temprature*/

    if (u8_g_barCount < 0) /*Check if the cursor is decrementing outside of the LCD range*/
    {
        u8_g_barCount = 0;
    }

    APP_printChar(1, u8_g_barCount, ' ');         /*prints ' ' which clears the last printed value*/
    APP_printInteger(0, 7, u8_g_requiredTemp); /*update the required temprature*/
}

/***************************************************************************/
/** @brief Sets the required temprature by incrementing and decrementing   */
/** @param void                                                            */
/** @return void                                                           */
/***************************************************************************/
void APP_setTemp()
{
    uint16_t u16_l_ovf;  /*number of overflows needed to reach a certain time*/
    uint8_t keypadValue; /*value read from the keypad*/

    /*Asking the user to set the required temprature*/
    LCD_sendCommand(Clear_Screen);
    APP_printString(0, 0, "Set Temp");
    TMR0_delaymicros(500000);
    LCD_sendCommand(Clear_Screen);

    /*Display the min and max values for the temprature*/
    APP_printString(0, 0, "Min=18");
    APP_printInteger(0, 7, u8_g_requiredTemp);
    APP_printString(0, 10, "Max=35");

    /*Setting the loading bar to match the required temp*/
    while (u8_g_barCount < (u8_g_requiredTemp - 18))
    {
        LCD_goTo(1, u8_g_barCount);
        LCD_sendChar('|');
        u8_g_barCount++;
    }

    u16_l_ovf = TIMER2_getInitialValue(3000); // gets the number of overflows needed to reach 3 secs on timer2
    TIMER2_perscalerMode(PRESCALER_MODE);     // sets the prescaler and starts timer2

    /*Check if the user is incrementing or decrementing the required temprature and if the user did not increment or decrement for 3 seconds, automatically set the value to its current state*/
    while ((keypadValue != '3') && (u16_gs_currentCount < u16_l_ovf)) /*Check if the user manually sets the temp or it timed out*/
    {
        keypadValue = KEYPAD_getpressedkey(); /*read the keypad input*/

        if (keypadValue == '1' && u8_g_barCount < 16) /*Check if the user is incrementing and reset overflow u8_g_barCounter to restart the time again for the user*/
        {
            u16_gs_currentCount = 0; /*reset the overflow u8_g_barCounter to 0 if user increments*/
            APP_incrementBar();
            TMR0_delaymicros(200000);
        }

        else if (keypadValue == '2' && u8_g_barCount != 0) /*Check if the user is decrementing and reset overflow u8_g_barCounter to restart the time again for the user*/
        {
            u16_gs_currentCount = 0; /*reset the overflow u8_g_barCounter to 0 if user decrements*/
            APP_decrementBar();
            TMR0_delaymicros(200000);
        }
    }
    TIMER2_perscalerMode(TIMER_OFF_); // close the timer
    TCNT2 = 0;                        // set the timer u8_g_barCounter register value to 0
    u16_gs_currentCount = 0;          // reset the u8_g_barCounter

    APP_printString(0, 0, "Temp set to >  "); /*Print the set value to the user*/
    APP_printInteger(0, 14, (u8_g_requiredTemp));
    TMR0_delaymicros(1000000);
    LCD_sendCommand(Clear_Screen);
}

/********************************************************************************************************************************************************/
/** @brief Shows the current and required temprature on the LCD while checking if the user wants to readjust the temp or reset it to its default value  */
/** @param void                                                                                                                                         */
/** @return void                                                                                                                                        */
/********************************************************************************************************************************************************/
void APP_defaultView(void)
{
    float adc_value;     /*variable to store the read adc value in*/
    uint8_t keypadValue; /*value read from the keypad*/

    adc_value = ADC_read(); /*get the sensor's reading*/
    adc_value += 18;         /*if the sensor reads 0 then this translates to 18 degrees celsius*/
    APP_printString(0, 0, "Current  T :");

    /*Approximate the adc value to floor or ceiling*/
    if (((int)(adc_value * 10) % 10) >= 5) /*Checks if the value after the decimal point is equal to 5 or higher*/
    {
        adc_value = ceil(adc_value);
    }
    else
    {
        adc_value = floor(adc_value);
    }

    /*Print the sensor value and the user's required temp*/
    APP_printInteger(0, 13, adc_value);
    APP_printString(1, 0, "Required T :");
    APP_printInteger(1, 13, u8_g_requiredTemp);

    /*Show buzzer if the sensor's reading is higher than the user required temp*/
    if ((int)adc_value > u8_g_requiredTemp)
    {
        APP_printChar(0, 15, 0); /*Show the bell custom character*/
    }
    else if ((int)adc_value <= u8_g_requiredTemp)
    {
        APP_printChar(0, 15, ' '); /*Clear the bell*/
    }

    /*Check if the user wants to readjust the required temprature or reset it to its default value*/
    keypadValue = KEYPAD_getpressedkey();
    if (((keypadValue >= 48) && (keypadValue < 58)) || (keypadValue == '*') || (keypadValue == '#')) /*Checks only for valid inputs from the keypad and ignore any unwanted data*/
    {
        LCD_sendCommand(Clear_Screen);
        if (keypadValue == '4') /*checks if the user wants to readjust*/
        {
            APP_printString(0, 0, " Readjust mode");
            u8_g_barCount = 0;
            TMR0_delaymicros(1000000);
            APP_setTemp();
        }

        else if (keypadValue == '5') /*checks if the user wants to reset*/
        {
            APP_printString(0, 0, "Temp reset to 20");
            u8_g_requiredTemp = 20;
            u8_g_barCount = 0;
            TMR0_delaymicros(1000000);
        }

        else /*any other input other than '4' or '5' is an invalid operation*/
        {
            APP_printString(0, 0, "Operation not");
            APP_printString(1, 0, "allowed");
            TMR0_delaymicros(1000000);
        }
        LCD_sendCommand(Clear_Screen);
    }
}

/**********************************************************************************/
/** @brief Callback function for timer 2 ISR which increments with every overflow */
/** @param  void                                                                  */
/** @return void                                                                  */
/**********************************************************************************/
void get_current_overflow(void)
{
    u16_gs_currentCount++;
}