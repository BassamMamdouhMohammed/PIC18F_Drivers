/* 
 * File:   Timer3_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:32 PM
 */

#ifndef TIMER3_INTERFACE_H
#define	TIMER3_INTERFACE_H

/********************************* Includes *********************************/
#include "../GPIO/GPIO_Interface.h"
#include "../Interrupt/Interrupt_Internal_Interface.h"
/********************************* Macro Definitions ************************/
#define TMR3_TIMER_MODE_ENABLE    0
#define TMR3_COUNTER_MODE_ENABLE  1
#define TMR3_16BIT_RW_REG         1
#define TMR3_8BIT_RW_REG          0
#define TMR3_PSA_DIVIDED_BY_1     0
#define TMR3_PSA_DIVIDED_BY_2     1
#define TMR3_PSA_DIVIDED_BY_4     2
#define TMR3_PSA_DIVIDED_BY_8     3
#define TMR3_COUNTER_ASYNCHRONOUS 1
#define TMR3_COUNTER_SYNCHRONOUS  0
/********************************* Macro Functions  *************************/
/* T3CON: TIMER3 CONTROL REGISTER */
/* bit 0 TMR3ON: Timer3 On bit */
#define TIMER3_ENABLE()                    (T3CONbits.TMR3ON = 1)
#define TIMER3_STOP()                      (T3CONbits.TMR3ON = 0)
/* bit 1 TMR3CS: Timer3 Clock Source Select bit */
#define TIMER3_COUNTER_MODE()              (T3CONbits.TMR3CS = 1)
#define TIMER3_TIMER_MODE()                (T3CONbits.TMR3CS = 0)
/* bit 2 T3SYNC: Timer3 External Clock Input Synchronization Control bit */
#define TIMER3_COUNTER_ASYNCHRONOUS()      (T3CONbits.T3SYNC = 1)
#define TIMER3_COUNTER_SYNCHRONOUS()       (T3CONbits.T3SYNC = 0)
/* bit 5-4 T3CKPS1:T3CKPS0: Timer3 Input Clock Prescale Select bits */
#define TIMER3_SET_PRESCALER_VALUE(_VALUE) (T3CONbits.T3CKPS = _VALUE)
/* bit 7 RD16: 16-Bit Read/Write Mode Enable bit */
#define TIMER3_8BIT_TIMER_COUNTER()        (T3CONbits.RD16 = 0)
#define TIMER3_16BIT_TIMER_COUNTER()       (T3CONbits.RD16 = 1)
/********************************* User-Defined Data Types ******************/
typedef struct{
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* TMR3_InterruptHandler)(void);
    Priority_t TMR3_Priority;
#endif
    uint16 Preloaded_Value;
    uint8 Prescaler_Value : 2;
    uint8 Mode : 1;
    uint8 Clock_Mode :1;
    uint8 RW_Register_Size : 1;
    uint8 Reserved : 3;
}TIMER3_t;
/********************************* Functions Declaration ********************/
STD_RETURN_t MCAL_TIMER3_Initialize(const TIMER3_t *_TMR);
STD_RETURN_t MCAL_TIMER3_DeInitialize(const TIMER3_t *_TMR);
STD_RETURN_t MCAL_TIMER3_Write_Value(const TIMER3_t *_TMR, uint16 _Value);
STD_RETURN_t MCAL_TIMER3_Read_Value(const TIMER3_t *_TMR, uint16 *_Value);

#endif	/* TIMER3_INTERFACE_H */

