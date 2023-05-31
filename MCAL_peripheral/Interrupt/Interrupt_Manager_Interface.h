/* 
 * File:   Interrupt_Manager_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 14, 2022, 2:15 PM
 */

#ifndef INTERRUPT_MANAGER_INTERFACE_H
#define	INTERRUPT_MANAGER_INTERFACE_H

/********************************* Includes *********************************/
#include "Interrupt_General_Interface.h"
#include "Interrupt_Internal_Interface.h"
#include "Interrupt_External_Interface.h"
/********************************* Macro Definitions ************************/

/********************************* Macro Functions  *************************/

/********************************* User-Defined Data Types ******************/

/********************************* Functions Declaration ********************/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8 RB4_Source);
void RB5_ISR(uint8 RB5_Source);
void RB6_ISR(uint8 RB6_Source);
void RB7_ISR(uint8 RB7_Source);

void ADC_ISR(void);

void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);

void UART_TX_ISR(void);
void UART_RX_ISR(void);
#endif	/* INTERRUPT_MANAGER_INTERFACE_H */

