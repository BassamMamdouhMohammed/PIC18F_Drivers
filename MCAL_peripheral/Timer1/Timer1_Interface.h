/* 
 * File:   Timer1_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:28 PM
 */

#ifndef TIMER1_INTERFACE_H
#define	TIMER1_INTERFACE_H

/********************************* Includes *********************************/
#include "../GPIO/GPIO_Interface.h"
#include "../Interrupt/Interrupt_Internal_Interface.h"
/********************************* Macro Definitions ************************/
#define TMR1_TIMER_MODE_ENABLE    0
#define TMR1_COUNTER_MODE_ENABLE  1
#define TMR1_16BIT_RW_REG         1
#define TMR1_8BIT_RW_REG          0
#define TMR1_PSA_DIVIDED_BY_1     0
#define TMR1_PSA_DIVIDED_BY_2     1
#define TMR1_PSA_DIVIDED_BY_4     2
#define TMR1_PSA_DIVIDED_BY_8     3
#define TMR1_COUNTER_ASYNCHRONOUS 1
#define TMR1_COUNTER_SYNCHRONOUS  0
#define TMR1_OSC_ENABLE           1
#define TMR1_OSC_SHUT_OFF         0
/********************************* Macro Functions  *************************/
/* T1CON: TIMER1 CONTROL REGISTER */
/* bit 0 TMR1ON: Timer1 On bit */
#define TIMER1_ENABLE()                    (T1CONbits.TMR1ON = 1)
#define TIMER1_STOP()                      (T1CONbits.TMR1ON = 0)
/* bit 1 TMR1CS: Timer1 Clock Source Select bit */
#define TIMER1_COUNTER_MODE()              (T1CONbits.TMR1CS = 1)
#define TIMER1_TIMER_MODE()                (T1CONbits.TMR1CS = 0)
/* bit 2 T1SYNC: Timer1 External Clock Input Synchronization Select bit */
#define TIMER1_COUNTER_ASYNCHRONOUS()      (T1CONbits.T1SYNC = 1)
#define TIMER1_COUNTER_SYNCHRONOUS()       (T1CONbits.T1SYNC = 0)
/* bit 3 T1OSCEN: Timer1 Oscillator Enable bit */
#define TIMER1_OSCILLATOR_SHUT_OFF()       (T1CONbits.T1OSCEN = 0)
#define TIMER1_OSCILLATOR_ENABLE()         (T1CONbits.T1OSCEN = 1)
/* bit 5-4 T1CKPS1:T1CKPS0: Timer1 Input Clock Prescale Select bits */
#define TIMER1_SET_PRESCALER_VALUE(_VALUE) (T1CONbits.T1CKPS = _VALUE)
/* bit 7 RD16: 16-Bit Read/Write Mode Enable bit */
#define TIMER1_8BIT_TIMER_COUNTER()        (T1CONbits.RD16 = 0)
#define TIMER1_16BIT_TIMER_COUNTER()       (T1CONbits.RD16 = 1)
/********************************* User-Defined Data Types ******************/
typedef struct{
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* TMR1_InterruptHandler)(void);
    Priority_t TMR1_Priority;
#endif
    uint16 Preloaded_Value;
    uint8 Prescaler_Value : 2;
    uint8 Mode : 1;
    uint8 Clock_Mode :1;
    uint8 RW_Register_Size : 1;
    uint8 Oscillator : 1;
    uint8 Reserved : 2;
}TIMER1_t;
/********************************* Functions Declaration ********************/
STD_RETURN_t MCAL_TIMER1_Initialize(const TIMER1_t *_TMR);
STD_RETURN_t MCAL_TIMER1_DeInitialize(const TIMER1_t *_TMR);
STD_RETURN_t MCAL_TIMER1_Write_Value(const TIMER1_t *_TMR, uint16 _Value);
STD_RETURN_t MCAL_TIMER1_Read_Value(const TIMER1_t *_TMR, uint16 *_Value);

#endif	/* TIMER1_INTERFACE_H */

