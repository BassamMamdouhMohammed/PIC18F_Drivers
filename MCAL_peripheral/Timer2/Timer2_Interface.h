/* 
 * File:   Timer2_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:30 PM
 */

#ifndef TIMER2_INTERFACE_H
#define	TIMER2_INTERFACE_H

/********************************* Includes *********************************/
#include "../GPIO/GPIO_Interface.h"
#include "../Interrupt/Interrupt_Internal_Interface.h"
/********************************* Macro Definitions ************************/
#define TMR2_PRESCALER_DIVIDED_BY_1     0
#define TMR2_PRESCALER_DIVIDED_BY_4     1
#define TMR2_PRESCALER_DIVIDED_BY_16    2

#define TMR2_POSTSCALER_DIVIDED_BY_1    0
#define TMR2_POSTSCALER_DIVIDED_BY_2    1
#define TMR2_POSTSCALER_DIVIDED_BY_3    2
#define TMR2_POSTSCALER_DIVIDED_BY_4    3
#define TMR2_POSTSCALER_DIVIDED_BY_5    4
#define TMR2_POSTSCALER_DIVIDED_BY_6    5
#define TMR2_POSTSCALER_DIVIDED_BY_7    6
#define TMR2_POSTSCALER_DIVIDED_BY_8    7
#define TMR2_POSTSCALER_DIVIDED_BY_9    8
#define TMR2_POSTSCALER_DIVIDED_BY_10   9
#define TMR2_POSTSCALER_DIVIDED_BY_11   10
#define TMR2_POSTSCALER_DIVIDED_BY_12   11
#define TMR2_POSTSCALER_DIVIDED_BY_13   12
#define TMR2_POSTSCALER_DIVIDED_BY_14   13
#define TMR2_POSTSCALER_DIVIDED_BY_15   14
#define TMR2_POSTSCALER_DIVIDED_BY_16   15
/********************************* Macro Functions  *************************/
/* T2CON: TIMER2 CONTROL REGISTER */
/* bit 1-0 T2CKPS1:T2CKPS0: Timer2 Clock Prescaler Select bits */
#define TIMER2_SET_PRESCALER_VALUE(_VALUE)  (T2CONbits.T2CKPS = _VALUE)
/* bit 2 TMR2ON: Timer2 On bit */
#define TIMER2_ENABLE()                     (T2CONbits.TMR2ON = 1)
#define TIMER2_STOP()                       (T2CONbits.TMR2ON = 0)
/* bit 6-3 T2OUTPS3:T2OUTPS0: Timer2 Output Postscaler Select bits */
#define TIMER2_SET_POSTSCALER_VALUE(_VALUE) (T2CONbits.TOUTPS = _VALUE)
/********************************* User-Defined Data Types ******************/
typedef struct{
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* TMR2_InterruptHandler)(void);
    Priority_t TMR2_Priority;
#endif
    uint8 Preloaded_Value;
    uint8 Prescaler_Value : 2;
    uint8 Postscaler_Value : 4;
    uint8 Reserved : 2;
}TIMER2_t;
/********************************* Functions Declaration ********************/
STD_RETURN_t MCAL_TIMER2_Initialize(const TIMER2_t *_TMR);
STD_RETURN_t MCAL_TIMER2_DeInitialize(const TIMER2_t *_TMR);
STD_RETURN_t MCAL_TIMER2_Write_Value(const TIMER2_t *_TMR, uint8 _Value);
STD_RETURN_t MCAL_TIMER2_Read_Value(const TIMER2_t *_TMR, uint8 *_Value);
#endif	/* TIMER2_INTERFACE_H */

