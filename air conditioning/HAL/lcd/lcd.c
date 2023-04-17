/*
 * File: lcd.c
 * Created Date: Monday, April 17th 2023, 1:21:26 am
 * Author: Omar Taha
 * -----
 * Copyright (c) 2023 Omar Taha <<https://github.com/OmarAshrafTaha>>
 */

#include "lcd_interface.h"
#include "../../MCAL/timer0/TMR0_interface.h"

/*                              8 bit mode                                 */

/***************************************************************************/
/** @brief  LCD 8 bit mode initialization function                         */
/** @param  void                                                           */
/** @return init_OK                                                        */
/***************************************************************************/
LCD_init_error LCD_8_bit_init(void)
{
    set_bit(LCD_Command_Dir,RS);
    set_bit(LCD_Command_Dir,RW);
    set_bit(LCD_Command_Dir,EN);

    Set_mask(0xFF, LCD_Data_Dir);              /*LCD_Data_Port takes a whole port since 8 bit mode.*/
    TMR0_delayms(20);                          /*LCD power on delay is always >15 milliseconds*/
    LCD_8_bit_sendCommand(LCD_8_Bit_Mode);     /*Initialization of 16x2 LCD in 8 bit mode*/
    LCD_8_bit_sendCommand(Cursor_Off);      /*Display ON cursor OFF*/
    //LCD_8_bit_sendCommand(Cursor_Blinking);    /*Display ON cursor Blinking*/
    LCD_8_bit_sendCommand(Cursor_Shift_Right); /*Auto increment cursor*/
    LCD_8_bit_sendCommand(Clear_Screen);       /*Clear display*/
    LCD_8_bit_sendCommand(Cursor_Reset_Line1); /*Cursor at home position*/

    #if LCD_Bit_Mode == 4
        return init_NOT_OK;
    #elif LCD_Bit_Mode == 8
        return init_OK;
    #endif
}

/***************************************************************************/
/** @brief    Sends Commands to 8 bit mode LCD                             */
/** @param    u8_a_command   command to be sent to the LCD                 */
/** @return   cmnd_send_OK                                                 */
/***************************************************************************/
LCD_sendCommand_error LCD_8_bit_sendCommand(uint8_t u8_a_command)
{
    LCD_Data_Port = u8_a_command;    /*Add command value to data port*/
    clear_bit(LCD_Command_Port,RS); /*RS = 0, Choose Command Register*/
    clear_bit(LCD_Command_Port,RW); /*RW = 0, Choose to write*/

    /*Generate a high to low pulse to the enable pin for a minimum of 450 nanoseconds*/
    set_bit(LCD_Command_Port,EN);
    TMR0_delayms(0.001);
    clear_bit(LCD_Command_Port,EN);
    TMR0_delayms(0.003);

    return cmnd_send_OK;
}

/***************************************************************************/
/** @brief    Sends Characters to 8 bit mode LCD                           */
/** @param    u8_a_char                                                    */
/** @return   char_send_OK                                                 */
/***************************************************************************/
LCD_sendChar_error LCD_8_bit_sendChar(uint8_t u8_a_char)
{
    LCD_Data_Port = u8_a_char;
    set_bit(LCD_Command_Port,RS);   /*RS = 1, Choose Data Register*/
    clear_bit(LCD_Command_Port,RW); /*RW = 0, Choose to Write*/

    /*Generate a high to low pulse to the enable pin for a minimum of 450 nanoseconds*/
    set_bit(LCD_Command_Port,EN);
    TMR0_delayms(0.001);
    clear_bit(LCD_Command_Port,EN);
    TMR0_delayms(0.003);
    return char_send_OK;
}

/*                              4 bit mode                                 */

/***************************************************************************/
/** @brief  LCD 4 bit mode initialization function                         */
/** @param  void                                                           */
/** @return init_OK                                                        */
/***************************************************************************/
LCD_init_error LCD_4_bit_init(void)
{
    set_bit(LCD_Command_Dir,RS);
    set_bit(LCD_Command_Dir,RW);
    set_bit(LCD_Command_Dir,EN);

    #if LCD_Data_Port_Nibble == 'U'
        Set_mask(0xF0, LCD_Data_Dir); /*Upper nibble of the port as output.*/
    #elif LCD_Data_Port_Nibble == 'L'
        Set_mask(0x0F, LCD_Data_Dir); /*Lower nibble of the port as output.*/
    #endif

    TMR0_delayms(20);                          /*LCD power on delay is always >15 milliseconds*/
    LCD_4_bit_sendCommand(LCD_4_Bit_Mode);     /*Initialization of 16x2 LCD in 8 bit mode*/
    LCD_4_bit_sendCommand(LCD_4_Bit_Mode_5x7); /*2 line 5x7 matrix in 4 bit mode*/
    // LCD_4_bit_sendCommand(Cursor_Off);      /*Display ON cursor OFF*/
    LCD_4_bit_sendCommand(Cursor_Blinking);    /*Display ON cursor Blinking*/
    LCD_4_bit_sendCommand(Cursor_Shift_Right); /*Auto increment cursor*/
    LCD_4_bit_sendCommand(Clear_Screen);       /*Clear display*/
    LCD_4_bit_sendCommand(Cursor_Reset_Line1); /*Cursor at home position*/

    #if LCD_Bit_Mode == 8
        return init_NOT_OK;
    #elif LCD_Bit_Mode == 4
        return init_OK;
    #endif
}

/***************************************************************************/
/** @brief    Sends Commands to 4 bit mode LCD                             */
/** @param    u8_a_command   command to be sent to the LCD                 */
/** @return   cmnd_send_OK                                                 */
/***************************************************************************/
LCD_sendCommand_error LCD_4_bit_sendCommand(uint8_t u8_a_command)
{
    #if LCD_Data_Port_Nibble == 'U'
        LCD_Data_Port = (LCD_Data_Port & 0x0F) | ((u8_a_command & 0xF0)); /*Add command value to data port, sending upper nibble*/
    #elif LCD_Data_Port_Nibble == 'L'
        LCD_Data_Port = (LCD_Data_Port & 0xF0) | ((u8_a_command & 0xF0) >> 4);
    #endif

    clear_bit(LCD_Command_Port,RS); /*RS = 0, Choose Command Register*/
    clear_bit(LCD_Command_Port,RW); /*RW = 0, Choose to write*/

    /*Generate a high to low pulse to the enable pin for a minimum of 450 nanoseconds*/
    set_bit(LCD_Command_Port,EN);
    TMR0_delayms(0.001);
    clear_bit(LCD_Command_Port,EN);
    TMR0_delayms(0.2);

    #if LCD_Data_Port_Nibble == 'U'
        LCD_Data_Port = (LCD_Data_Port & 0x0F) | ((u8_a_command & 0x0F) << 4); /*Add command value to data port, sending lower nibble*/
    #elif LCD_Data_Port_Nibble == 'L'
        LCD_Data_Port = (LCD_Data_Port & 0xF0) | ((u8_a_command & 0x0F));
    #endif

    /*Generate a high to low pulse to the enable pin for a minimum of 450 nanoseconds*/
    set_bit(LCD_Command_Port,EN);
    TMR0_delayms(0.001);
    clear_bit(LCD_Command_Port,EN);
    TMR0_delayms(2);

    return cmnd_send_OK;
}

/***************************************************************************/
/** @brief    Sends Characters to 4 bit mode LCD                           */
/** @param    u8_a_char                                                    */
/** @return   char_send_OK                                                 */
/***************************************************************************/
LCD_sendChar_error LCD_4_bit_sendChar(uint8_t u8_a_char)
{
    #if LCD_Data_Port_Nibble == 'U'
        LCD_Data_Port = (LCD_Data_Port & 0x0F) | ((u8_a_char & 0xF0));      /*Add data value to data port, sending upper nibble*/
    #elif LCD_Data_Port_Nibble == 'L'
        LCD_Data_Port = (LCD_Data_Port & 0xF0) | ((u8_a_char & 0xF0) >> 4);
    #endif

    set_bit(LCD_Command_Port,RS);   /*RS = 1, Choose Data Register*/
    clear_bit(LCD_Command_Port,RW); /*RW = 0, Choose to write*/

    /*Generate a high to low pulse to the enable pin for a minimum of 450 nanoseconds*/
    set_bit(LCD_Command_Port,EN);
    TMR0_delayms(0.001);
    clear_bit(LCD_Command_Port,EN);
    TMR0_delayms(0.2);
    #if LCD_Data_Port_Nibble == 'U'
        LCD_Data_Port = (LCD_Data_Port & 0x0F) | ((u8_a_char & 0x0F) << 4);/*Add data value to data port, sending lower nibble*/
    #elif LCD_Data_Port_Nibble == 'L'
        LCD_Data_Port = (LCD_Data_Port & 0xF0) | ((u8_a_char & 0x0F));
    #endif

    /*Generate a high to low pulse to the enable pin for a minimum of 450 nanoseconds*/
    set_bit(LCD_Command_Port,EN);
    TMR0_delayms(0.001);
    clear_bit(LCD_Command_Port,EN);
    TMR0_delayms(2);

    return char_send_OK;
}

/*                              Common                                     */

/***************************************************************************/
/** @brief    Sends string to 8 bit mode LCD                               */
/** @param    *u8_a_string                                                 */
/** @return   string_send_OK                                               */
/***************************************************************************/
LCD_sendString_error LCD_sendString(uint8_t *u8_a_string)
{
    uint16_t u16_l_charCount;
    for (u16_l_charCount = 0; u8_a_string[u16_l_charCount] != 0; u16_l_charCount++)
    {
        #if LCD_Bit_Mode == 8
            LCD_8_bit_sendChar(u8_a_string[u16_l_charCount]);

        #elif LCD_Bit_Mode == 4
            LCD_4_bit_sendChar(u8_a_string[u16_l_charCount]);
        #endif
    }
    return string_send_OK;
}