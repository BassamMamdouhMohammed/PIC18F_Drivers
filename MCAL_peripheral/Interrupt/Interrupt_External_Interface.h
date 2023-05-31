/* 
 * File:   Interrupt_External_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 14, 2022, 2:15 PM
 */

#ifndef INTERRUPT_EXTERNAL_INTERFACE_H
#define	INTERRUPT_EXTERNAL_INTERFACE_H

/********************************* Includes *********************************/
#include "Interrupt_General_Interface.h"
/********************************* Macro Definitions ************************/
typedef void(*InterruptHandler)(void);
#define INTx_RISING_EDGE  1
#define INTx_FALLING_EDGE 0
/********************************* Macro Functions  *************************/
#if EXTERNAL_INTERRUPT_EXTERNAL_ENABLE==INTERRUPT_FEATURE_ENABLE
/* bit 4 INT0IE: INT0 External Interrupt Enable bit (INTCON <4> )     */
#define INTERRUPT_INT0_ENABLE()       (INTCONbits.INT0IE = 1)
#define INTERRUPT_INT0_DISABLE()      (INTCONbits.INT0IE = 0)
/* bit 1 INT0IF: INT0 External Interrupt Flag bit   (INTCON <1> )     */
#define INTERRUPT_INT0_CLEAR_FLAG()   (INTCONbits.INT0IF = 0)
/* bit 6 INTEDG0: External Interrupt 0 Edge Select bit (INTCON2 <6> ) */
#define INTERRUPT_INT0_RISING_EDGE()  (INTCON2bits.INTEDG0 = 1)
#define INTERRUPT_INT0_FALLING_EDGE() (INTCON2bits.INTEDG0 = 0)

/* bit 3 INT1IE: INT1 External Interrupt Enable bit ( INTCON3<3> )    */
#define INTERRUPT_INT1_ENABLE()         (INTCON3bits.INT1IE = 1)
#define INTERRUPT_INT1_DISABLE()        (INTCON3bits.INT1IE = 0)
/* bit 5 INTEDG1: External Interrupt 1 Edge Select bit ( INTCON2<5> ) */
#define INTERRUPT_INT1_RISING_EDGE()    (INTCON2bits.INTEDG1 = 1)
#define INTERRUPT_INT1_FALLING_EDGE()   (INTCON2bits.INTEDG1 = 0)
/* bit 0 INT1IF: INT1 External Interrupt Flag bit  ( INTCON3<4> )     */
#define INTERRUPT_INT1_CLEAR_FLAG()     (INTCON3bits.INT1IF = 0)
/* bit 6 INT1IP: INT1 External Interrupt Priority bit  ( INTCON3<6> ) */
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_INT1_HIGH_PRIORITY()  (INTCON3bits.INT1IP = 1)
#define INTERRUPT_INT1_LOW_PRIORITY()   (INTCON3bits.INT1IP = 0)
#endif

/* bit 4 INT2IE: INT2 External Interrupt Enable bit ( INTCON3<4> )    */
#define INTERRUPT_INT2_ENABLE()         (INTCON3bits.INT2IE = 1)
#define INTERRUPT_INT2_DISABLE()        (INTCON3bits.INT2IE = 0)
/* bit 4 INTEDG2: External Interrupt 2 Edge Select bit ( INTCON2<4> ) */
#define INTERRUPT_INT2_RISING_EDGE()    (INTCON2bits.INTEDG2 = 1)
#define INTERRUPT_INT2_FALLING_EDGE()   (INTCON2bits.INTEDG2 = 0)
/* bit 1 INT2IF: INT2 External Interrupt Flag bit  ( INTCON3<1> )     */
#define INTERRUPT_INT2_CLEAR_FLAG()     (INTCON3bits.INT2IF = 0)
/* bit 6 INT1IP: INT1 External Interrupt Priority bit  ( INTCON3<7> ) */
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_INT2_HIGH_PRIORITY()  (INTCON3bits.INT2IP = 1)
#define INTERRUPT_INT2_LOW_PRIORITY()   (INTCON3bits.INT2IP = 0)
#endif

/* bit 3 RBIE: RB Port Change Interrupt Enable bit  (INTCON <3> )   */
#define INTERRUPT_RBx_ENABLE()       (INTCONbits.RBIE = 1)
#define INTERRUPT_RBx_DISABLE()      (INTCONbits.RBIE = 0)
/* bit 0 RBIF: RB Port Change Interrupt Flag bit    (INTCON <0> )   */
#define INTERRUPT_RBx_CLEAR_FLAG()   (INTCONbits.RBIF = 0)
/* bit 0 RBIP: RB Port Change Interrupt Priority bit (INTCON2 <0> ) */
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
#define INTERRUPT_RB_HIGH_PRIORITY() (INTCON2bits.RBIP = 1)
#define INTERRUPT_RB_LOW_PRIORITY()  (INTCON2bits.RBIP = 0)
#endif

#endif

/********************************* User-Defined Data Types ******************/
typedef enum{
    Falling_Edge = 0,
    Rising_Edge 
}Edge_t;

typedef enum{
    EXT_INT0 = 0,
    EXT_INT1,
    EXT_INT2
}INTx_Select;

typedef struct{
    void(*INTx_InterruptHandler)(void);
    PIN_t INTx_Pin;
    Edge_t INTx_Edge;
    INTx_Select INTx_Source;
    Priority_t INTx_Priority;
}INTx_t;

typedef struct{
    void(*RBx_InterruptHandler_High)(void);
    void(*RBx_InterruptHandler_Low)(void);
    PIN_t RBx_Pin;
    Priority_t RBx_Priority;
}RBx_t;
/********************************* Functions Declaration ********************/
STD_RETURN_t MCAL_Interrupt_INTx_Initialize(const INTx_t *_INTx);
STD_RETURN_t MCAL_Interrupt_INTx_DeInitialize(const INTx_t *_INTx);
STD_RETURN_t MCAL_Interrupt_RBx_Initialize(const RBx_t *_RBx);
STD_RETURN_t MCAL_Interrupt_RBx_DeInitialize(const RBx_t *_RBx);
#endif	/* INTERRUPT_EXTERNAL_INTERFACE_H */

