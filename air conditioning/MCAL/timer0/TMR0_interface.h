/******************************************************************/
/* Author  : Mustafa Mohammed Abdou                               */
/* Date    : 16 , April 2023                                      */
/* Version : V01                                                  */
/* Hint    : Interface file of Timer 0                            */
/******************************************************************/

#ifndef TMR0_INTERFACE_H
#define TMR0_INTERFACE_H

/** DIFFERENT MACROS FOR TMR0 CONFIGURATION **/

#define F_CPU 1000000 /** DEFINE THE CLOCK SOURCE FREQUENCY **/

/** MACROS FOR THE CLOCK SOURCE  **/
#define INTERNAL_CLK_SRC 0
#define EXTERNAL_CLK_SRC 1

/** MACROS FOR EXTERNAL SOURCE OUNTING ACTION **/
#define FALLING_EDGE_CNT 0
#define RISING_EDGE_CNT 1

/** MACROS FOR DIFFERENT OPERATING MODES FOR TMR0 **/
#define TMR0_NORMAL_MODE 0
#define TMR0_FASTPWM_NON_INVERTED_MODE 1
#define TMR0_FASTPWM_INVERTED_MODE 2
#define TMR_PHASE_CORRECT_NON_INVERTED_MODE 3
#define TMR_PHASE_CORRECT_INVERTED_MODE 4
#define TMR0_CTC_MODE 5

/** MACROS FOR ACTION ON COMPARE  **/
#define SET_ON_COMPARE 0
#define CLEAR_ON_COMPARE 1
#define TOOGLE_ON_COMPARE 2

/** MACROS TO CONFIGURE TMR0 PRESCALLER **/
#define NO_PRESCALER 0
#define PRESCALER_8 1
#define PRESCALER_64 2
#define PRESCALER_256 3
#define PRESCALER_1024 4

/*Timer 0 initialization error*/
typedef enum TMR0_init_error
{
    VALID_INIT,
    NOT_VALID_INIT
} TMR0_init_error;

/****************************************************************/
/** Description : Initialize Timer 0 with some configurations   */
/** @param      VOID                                            */
/** @return     TMR0_init status                                */
/****************************************************************/
TMR0_init_error TMR0_init(void);

/*Timer 0 start error*/
typedef enum TMR0_start_error
{
    VALID_START,
    NOT_VALID_START
} TMR0_start_error;

/*******************************************************************************/
/** Description : Start Timer 0 with the assigned prescaller or clock source   */
/** @param      VOID                                                           */
/** @return     TMR0_start status                                              */
/*******************************************************************************/
TMR0_start_error TMR0_start(void);

/*Timer 0 stop error*/
typedef enum TMR0_stop_error
{
    VALID_STOP,
    NOT_VALID_STOP
} TMR0_stop_error;

/*******************************************************************************/
/** Description : Stop Timer 0                                                 */
/** @param      VOID                                                           */
/** @return     TMR0_stop status                                               */
/*******************************************************************************/
TMR0_stop_error TMR0_stop(void);

/*Timer 0 delay error*/
typedef enum TMR0_delay_error
{
    VALID_DELAY,
    NOT_VALID_DELAY
} TMR0_delay_error;


/*******************************************************************************/
/** Description : Sets delay using Timer 0                                     */
/** @param      delay_in_milliseconds                                          */
/** @return     TMR0_delay status                                              */
/*******************************************************************************/
TMR0_delay_error TMR0_delayms(uint32_t u32_a_delayms);

/*******************************************************************************/
/** Description : Sets delay using Timer 0                                     */
/** @param      delay_in_microseconds                                          */
/** @return     TMR0_delay status                                              */
/*******************************************************************************/
TMR0_delay_error TMR0_delaymicros(uint32_t u32_a_delaymicros);

#endif