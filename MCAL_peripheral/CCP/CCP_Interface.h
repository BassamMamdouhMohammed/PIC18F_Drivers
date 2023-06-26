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
#define CCP_PWM_MODE_ENABLE     0X02
#define CCP_CAPTURE_MODE_ENABLE 0x01
#define CCP_COMPARE_MODE_ENABLE 0x00
#define CCP_MODE_SELECT CCP_CAPTURE_MODE_ENABLE

#define INVALID_MODE                        ((uint8)0x03)
#define INVALID_SUBMODE                     ((uint8)0x04)
#define INVALID_MODULE                      ((uint8)0x05)
#define CCP_CAPTURE_TMR1                    ((uint8)0x00)
#define CCP_CAPTURE_TMR1_TMR3               ((uint8)0x01)
#define CCP_CAPTURE_TMR3                    ((uint8)0x02)

/* CCPx Module Mode Select bits */
#define CCP_MODULE_DISABLE                  ((uint8)0x00)
#define CCP_MODULE_ENABLE                   ((uint8)0x01) ///////

#define CCP_CAPTURE_EVERY_FALLING_EDGE      ((uint8)0x04)
#define CCP_CAPTURE_EVERY_RISING_EDGE       ((uint8)0x05)
#define CCP_CAPTURE_EVERY_4th_RISING_EDGE   ((uint8)0x06)
#define CCP_CAPTURE_EVERY_16th_RISING_EDGE  ((uint8)0x07)

#define CCP_COMPARE_INITIALIZE_PIN_LOW      ((uint8)0x08)
#define CCP_COMPARE_INITIALIZE_PIN_HIGH     ((uint8)0x09)
#define CCP_COMPARE_GENERATE_SW_INTERRUPT   ((uint8)0x0A)
#define CCP_COMPARE_GENERATE_SPECIAL_EVENT  ((uint8)0x0B)
#define CCP_COMPARE_TOGGLE_OUTPUT           ((uint8)0x02)

#define CCP_PWM_MODE                        ((uint8)0x0C)
/* CCP Capture Mode status */
#define CCP_CATURE_READY                    ((uint8)0x01)
#define CCP_CATURE_NOT_READY                ((uint8)0x00)

/* CCP Compare Mode status */
#define CCP_COMPARE_READY                    ((uint8)0x01)
#define CCP_COMPARE_NOT_READY                ((uint8)0x00)

#define CCP_TIM2_POSTSCALER_DIV_BY_1       1
#define CCP_TIM2_POSTSCALER_DIV_BY_2       2
#define CCP_TIM2_POSTSCALER_DIV_BY_3       3
#define CCP_TIM2_POSTSCALER_DIV_BY_4       4
#define CCP_TIM2_POSTSCALER_DIV_BY_5       5
#define CCP_TIM2_POSTSCALER_DIV_BY_6       6
#define CCP_TIM2_POSTSCALER_DIV_BY_7       7
#define CCP_TIM2_POSTSCALER_DIV_BY_8       8
#define CCP_TIM2_POSTSCALER_DIV_BY_9       9
#define CCP_TIM2_POSTSCALER_DIV_BY_10      10
#define CCP_TIM2_POSTSCALER_DIV_BY_11      11
#define CCP_TIM2_POSTSCALER_DIV_BY_12      12
#define CCP_TIM2_POSTSCALER_DIV_BY_13      13
#define CCP_TIM2_POSTSCALER_DIV_BY_14      14
#define CCP_TIM2_POSTSCALER_DIV_BY_15      15
#define CCP_TIM2_POSTSCALER_DIV_BY_16      16

#define CCP_TIM2_PRESCALER_DIVIDED_BY_1     ((uint8)0x01)
#define CCP_TIM2_PRESCALER_DIVIDED_BY_4     ((uint8)0x04)
#define CCP_TIM2_PRESCALER_DIVIDED_BY_16    ((uint8)0x10)

#define CCP_CAPTURE_TIM3                    ((uint8)0x00)
#define CCP_CAPTURE_TIM1_TIM3               ((uint8)0x01)
#define CCP_CAPTURE_TIM1                    ((uint8)0x02)
/********************************* Macro Functions  *************************/

/********************************* User-Defined Data Types ******************/
typedef enum{
    CCP1_instance,
    CCP2_instance        
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

typedef struct
{
#if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE  
    void(* CCP1_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
    Priority_t CCP1_Priority;
#endif
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE  
    void(* CCP2_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
    Priority_t CCP2_Priority;
#endif
#endif
    
    CCP_Module_t CCPx_Select;
    uint8 Mode :2;
    uint8 SubMode :4;
    PIN_t CCP_Pin;
    uint8 Capture_TIM_Select;
#if CCP_MODE_SELECT==CCP_PWM_MODE_ENABLE
    uint32 PWM_FREQ;
    uint8 TMR2_Prescaler : 2;
    uint8 TMR2_Postscaler : 4;
#endif
}CCP_t;
/********************************* Functions Declaration ********************/

STD_RETURN_t MCAL_CCP_Init(const CCP_t *ccp);
STD_RETURN_t MCAL_CCP_DeInit(const CCP_t *ccp);

#if (CCP_MODE_SELECT == CCP_CAPTURE_MODE_ENABLE)
STD_RETURN_t MCAL_CCP_CAPUTER_DataReady(uint8 *capture_status);
STD_RETURN_t MCAL_CCP_CAPUTER_ReadData(uint16 *data);

#elif (CCP_MODE_SELECT == CCP_COMPARE_MODE_ENABLE)
STD_RETURN_t MCAL_CCP_IsCompareComplete(uint8 *compare_status);
STD_RETURN_t MCAL_CCP_CompareWriteValue(uint16 value);

#elif (CCP_MODE_SELECT == CCP_PWM_MODE_ENABLE)
STD_RETURN_t MCAL_CCP_PWM_START(const CCP_t *ccp);
STD_RETURN_t MCAL_CCP_PWM_STOP(const CCP_t *ccp);
STD_RETURN_t MCAL_CCP_PWM_SetDuty(const CCP_t *ccp, const uint8 duty);
#endif

#endif	/* CCP_INTERFACE_H */

