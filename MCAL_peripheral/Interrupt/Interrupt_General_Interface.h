/* 
 * File:   Interrupt_General_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 18, 2022, 3:53 PM
 */

#ifndef INTERRUPT_GENERAL_INTERFACE_H
#define	INTERRUPT_GENERAL_INTERFACE_H

/********************************* Includes *********************************/
#include "../GPIO/GPIO_Interface.h"
/********************************* Macro Definitions ************************/

/* Priority Interrupts Enable Feature for Internal Peripherals in MCU */
#define INTERRUPT_OCCURE         1U
#define INTERRUPT_ENABLE         1U
#define INTERRUPT_FEATURE_ENABLE 1U
//#define INTERRUPT_PRIORITY_ENABLE           INTERRUPT_FEATURE_ENABLE

#define EXTERNAL_INTERRUPT_EXTERNAL_ENABLE  INTERRUPT_FEATURE_ENABLE

#define ADC_INTERRUPT_FEATURE_ENABLE                INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_FEATURE_ENABLE             INTERRUPT_FEATURE_ENABLE

#define UART_TX_INTERRUPT_FEATURE_ENABLE            INTERRUPT_FEATURE_ENABLE
#define UART_RX_INTERRUPT_FEATURE_ENABLE            INTERRUPT_FEATURE_ENABLE

#define MSSP_I2C_INTERRUPT_FEATURE_ENABLE           INTERRUPT_FEATURE_ENABLE
#define MSSP_BUS_COLLISION_INTERRUPT_FEATURE_ENABLE           INTERRUPT_FEATURE_ENABLE

#define  CCP_INTERRUPT_FEATURE_ENABLE              INTERRUPT_FEATURE_ENABLE
/* INTCON: INTERRUPT CONTROL REGISTER */
/* bit 7 GIE/GIEH: Global Interrupt Enable bit */
#define INTERRUPT_GLOBAL_ENABLE()                (INTCONbits.GIE = 1)
#define INTERRUPT_GLOBAL_DISABLE()               (INTCONbits.GIE = 0)
#define INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE()  (INTCONbits.GIEH = 1)
#define INTERRUPT_GLOBAL_HIGH_PRIORITY_DISABLE() (INTCONbits.GIEH = 0)
/* bit 6 PEIE/GIEL: Peripheral Interrupt Enable bit */
#define INTERRUPT_PERIPHERAL_ENABLE()            (INTCONbits.PEIE = 1)
#define INTERRUPT_PERIPHERAL_DISABLE()           (INTCONbits.PEIE = 0)
#define INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE()   (INTCONbits.GIEL = 1)
#define INTERRUPT_GLOBAL_LOW_PRIORITY_DISABLE()  (INTCONbits.GIEL = 0)

/* RCON: RESET CONTROL REGISTER */
/* bit 7 IPEN: Interrupt Priority Enable bit */
#define INTERRUPT_PRIORITY_LEVELS_ENABLE()       (RCONbits.IPEN = 1)
#define INTERRUPT_PRIORITY_LEVELS_DISABLE()      (RCONbits.IPEN = 0)

/********************************* Macro Functions  *************************/

/********************************* User-Defined Data Types ******************/
typedef enum{
    Low_Priority = 0,
    High_Priority
}Priority_t;

/********************************* Functions Declaration ********************/

#endif	/* INTERRUPT_GENERAL_INTERFACE_H */

