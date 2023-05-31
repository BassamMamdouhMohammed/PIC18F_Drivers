/* 
 * File:   Timer0_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:23 PM
 */

#ifndef TIMER0_INTERFACE_H
#define	TIMER0_INTERFACE_H

/********************************* Includes *********************************/
#include "../GPIO/GPIO_Interface.h"
#include "../Interrupt/Interrupt_Internal_Interface.h"
/********************************* Macro Definitions ************************/
#define TMR0_TIMER_MODE_ENABLE   0
#define TMR0_COUNTER_MODE_ENABLE 1
#define TMR0_PRESCALER_ENABLE    0
#define TMR0_PRESCALER_DISABLE   1
#define TMR0_16BIT_CONTROL_REG   0
#define TMR0_8BIT_CONTROL_REG    1
#define TMR0_FALLING_EDGE_SOURCE 1
#define TMR0_RISING_EDGE_SOURCE  0
/********************************* Macro Functions  *************************/

/* bit 2-0 T0PS2:T0PS0: Timer0 Prescaler Select bits <T0CON> */
#define TIMER0_SET_PRESCALER_VALUE(_VALUE) (T0CONbits.T0PS = _VALUE)
/* bit 3 PSA: Timer0 Prescaler Assignment bit <T0CON> */
#define TIMER0_PRESCALER_DISABLE()         (T0CONbits.PSA = 1)
#define TIMER0_PRESCALER_ENABLE()          (T0CONbits.PSA = 0)
/* bit 4 T0SE: Timer0 Source Edge Select bit <T0CON> */
#define TIMER0_COUNTER_FALLING_EDGE()      (T0CONbits.T0SE = 1)
#define TIMER0_COUNTER_RISING_EDGE()       (T0CONbits.T0SE = 0)
/* bit 5 T0CS: Timer0 Clock Source Select bit <T0CON> */
#define TIMER0_COUNTER_MODE()              (T0CONbits.T0CS = 1)
#define TIMER0_TIMER_MODE()                (T0CONbits.T0CS = 0)
/* bit 6 T08BIT: Timer0 8-Bit/16-Bit Control bit <T0CON> */
#define TIMER0_8BIT_TIMER_COUNTER()        (T0CONbits.T08BIT = 1)
#define TIMER0_16BIT_TIMER_COUNTER()       (T0CONbits.T08BIT = 0)
/* bit 7 TMR0ON: Timer0 On/Off Control bit <T0CON> */
#define TIMER0_ENABLE()                    (T0CONbits.TMR0ON = 1)
#define TIMER0_STOP()                      (T0CONbits.TMR0ON = 0)
/********************************* User-Defined Data Types ******************/
typedef enum{
    Prescaler_Divided_By_2 = 0,
    Prescaler_Divided_By_4,
    Prescaler_Divided_By_8,
    Prescaler_Divided_By_16,
    Prescaler_Divided_By_32,
    Prescaler_Divided_By_64,
    Prescaler_Divided_By_128, 
    Prescaler_Divided_By_256        
}Prescaler_t;

typedef struct{
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* TMR0_InterruptHandler)(void);
    Priority_t TMR0_Priority;
#endif
    uint16 Preloaded_Value;
    Prescaler_t Prescaler_Value;
    uint8 Mode : 1;
    uint8 Prescaler_Enable : 1;
    uint8 Edge_Source : 1;
    uint8 Register_Size : 1;
    uint8 Reserved : 4;
}TIMER0_t;

/********************************* Functions Declaration ********************/

STD_RETURN_t MCAL_TIMER0_Initialize(const TIMER0_t *_TMR);
STD_RETURN_t MCAL_TIMER0_DeInitialize(const TIMER0_t *_TMR);
STD_RETURN_t MCAL_TIMER0_Write_Value(const TIMER0_t *_TMR, uint16 _Value);
STD_RETURN_t MCAL_TIMER0_Read_Value(const TIMER0_t *_TMR, uint16 *_Value);

#endif	/* TIMER0_INTERFACE_H */

