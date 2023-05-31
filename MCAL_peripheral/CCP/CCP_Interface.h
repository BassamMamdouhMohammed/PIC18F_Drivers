/* 
 * File:   CCP_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 28, 2022, 12:22 PM
 */

#ifndef CCP_INTERFACE_H
#define	CCP_INTERFACE_H

/********************************* Includes *********************************/
#include "../GPIO/GPIO_Interface.h"
#include "../Interrupt/Interrupt_Internal_Interface.h"
/********************************* Macro Definitions ************************/
#define _CCP_PWM_MODE_ENABLE     0X02
#define _CCP_CAPTURE_MODE_ENABLE 0x01
#define _CCP_COMPARE_MODE_ENABLE 0x00
#define _CCP_MODE_SELECT _CCP_PWM_MODE_ENABLE
#define _CCP_CAPTURE_TMR1      0
#define _CCP_CAPTURE_TMR1_TMR3 1
#define _CCP_CAPTURE_TMR3      2

#define _CCP_MODULE_DISABLE                  ((uint8)0x00)
#define _CCP_COMPARE_TOGGLE_OUTPUT           ((uint8)0x02)
#define _CCP_CAPTURE_EVERY_FALLING_EDGE      ((uint8)0x04)
#define _CCP_CAPTURE_EVERY_RISING_EDGE       ((uint8)0x05)
#define _CCP_CAPTURE_EVERY_4th_RISING_EDGE   ((uint8)0x06)
#define _CCP_CAPTURE_EVERY_16th_RISING_EDGE  ((uint8)0x07)
#define _CCP_COMPARE_INITIALIZE_PIN_LOW      ((uint8)0x08)
#define _CCP_COMPARE_INITIALIZE_PIN_HIGH     ((uint8)0x09)
#define _CCP_COMPARE_GENERATE_SW_INTERRUPT   ((uint8)0x0A)
#define _CCP_COMPARE_GENERATE_EVENT          ((uint8)0x0B)
#define _CCP_PWM_MODE                        ((uint8)0x0C)

#define _CCP_CAPTURE_OCCURED     1
#define _CCP_CAPTURE_NOT_OCCURED 0

#define _CCP_COMPARE_OCCURED     1
#define _CCP_COMPARE_NOT_OCCURED 0

#define _CCP_TMR2_PRESCALER_DIVIDED_BY_1  1
#define _CCP_TMR2_PRESCALER_DIVIDED_BY_4  4
#define _CCP_TMR2_PRESCALER_DIVIDED_BY_16 16
/********************************* Macro Functions  *************************/
#define CCP1_MODULE_SELECT_MODE(_Mode) (CCP1CONbits.CCP1M = _Mode)
#define CCP2_MODULE_SELECT_MODE(_Mode) (CCP2CONbits.CCP2M = _Mode)
/********************************* User-Defined Data Types ******************/
typedef enum{
    CCP1_inst =0,
    CCP2_inst        
}CCP_Module_t;
typedef union{
    struct{
        uint8 ccpr_low;    /* CCPR1 low register  */
        uint8 ccpr_high;   /* CCPR1 high register */
    };
    struct{
        uint16 ccpr_16Bit; /* Read CCPR1 as a 16 Bit value */
    };
}CCPR_t;
typedef struct{
#if CCP_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE  
    void(* CCP_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
    Priority_t CCP_Priority;
#endif
#endif
    CCP_Module_t CCP_Select;
    uint8 Mode :4;
    uint32 Preload;
    uint8 CCP_TMR_PSA;
    PIN_t CCP_Pin;
    uint8 Capture_TMR_Select;
#if _CCP_MODE_SELECT==_CCP_PWM_MODE_ENABLE
    uint32 PWM_FREQ;
    uint8 TMR2_Prescaler;
    uint8 TMR2_Postscaler;
#endif
}CCP_t;
/********************************* Functions Declaration ********************/
STD_RETURN_t MCAL_CCP_Initialize(const CCP_t *_CCP);
STD_RETURN_t MCAL_CCP_DeInitialize(const CCP_t *_CCP);


#endif	/* CCP_INTERFACE_H */

