/* 
 * File:   CCP_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 28, 2022, 12:22 PM
 */
#include <pic18f4620.h>
#include "CCP_Interface.h"

#if (CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)
static void(*CCP1_InterruptHandler)(void) = NULL;
#endif

#if (CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)
static void(*CCP2_InterruptHandler)(void) = NULL;
#endif

/*----------------------------- static helper function prototype ------------------------*/
static STD_RETURN_t CCP_SelectCapureSubMode(const CCP_t *ccp);
static STD_RETURN_t CCP_SelectCompareSubMode(const CCP_t *ccp);
static STD_RETURN_t CCP_SelectPWMSubMode(const CCP_t *ccp);
static void CCP_InterruptConfig(const CCP_t *ccp);
static STD_RETURN_t CCP_Disable(const CCP_t *ccp);
static STD_RETURN_t CCP_Enable(const CCP_t *ccp);
static void CCP_CC_TimerSelect(const CCP_t *ccp);

STD_RETURN_t MCAL_CCP_Init(const CCP_t *ccp)
{
    STD_RETURN_t retval = STD_OK;
    
    if(NULL != ccp)
    {
        retval = CCP_Disable(ccp);
#if CCP_MODE_SELECT==CCP_CAPTURE_MODE_ENABLE
        if(CCP_CAPTURE_MODE_ENABLE == ccp->Mode)
        {
            CCP_SelectCapureSubMode(ccp);
        }
#elif CCP_MODE_SELECT==CCP_COMPARE_MODE_ENABLE
        if(CCP_COMPARE_MODE_ENABLE == ccp->Mode)
        {
            CCP_SelectCompareSubMode(ccp);
        }
#elif CCP_MODE_SELECT==CCP_PWM_MODE_ENABLE
        if(CCP_PWM_MODE_ENABLE == ccp->Mode)
        {
            CCP_SelectPWMSubMode(ccp);
            PR2 = (uint8)((_XTAL_FREQ / (ccp->PWM_FREQ * 4.0 
                    * ccp->TMR2_Prescaler * ccp->TMR2_Postscaler)) - 1);
        }
#else
        retval = INVALID_MODE;
#endif

        MCAL_GPIO_Pin_Initialize(&(ccp->CCP_Pin));
        CCP_InterruptConfig(ccp);
        CCP_Enable(ccp);
    }
    else
    {
        retval = STD_NOT_OK;
    }
    return retval;
}
STD_RETURN_t MCAL_CCP_DeInit(const CCP_t *ccp)
{
    STD_RETURN_t retval = STD_OK;
    if(NULL != ccp){
        if(CCP1_instance == ccp->CCPx_Select)
        {
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
            #if CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                CCP1_INTERRUPT_DISABLE();
            #endif   
        }
        else if(CCP2_instance == ccp->CCPx_Select)
        {
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
            #if CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
                CCP2_INTERRUPT_DISABLE();
            #endif   
        }
        else
        {
           retval = INVALID_MODE;
        }
    }
    else
    {
        retval = STD_NOT_OK;
    }
    return retval;
}
#if (CCP_MODE_SELECT == CCP_CAPTURE_MODE_ENABLE)
STD_RETURN_t MCAL_CCP_CAPUTER_DataReady(uint8 *capture_status)
{
    STD_RETURN_t retval = STD_OK;
    if(NULL != capture_status) 
    {
        if(CCP_CATURE_READY == PIR1bits.CCP1IF)
        {
            *capture_status = CCP_CATURE_READY;
            CCP1_INTERRUPT_CLEAR_FLAG();
        }
        else
        {
            *capture_status = CCP_CATURE_NOT_READY;
        }

    }
    else{retval = STD_NOT_OK;}
    return retval;
}
STD_RETURN_t MCAL_CCP_CAPUTER_ReadData(uint16 *data)
{
    STD_RETURN_t retval = STD_OK;
    CCPR_t temp = {.ccpr_low = 0, .ccpr_high = 0};
    
    if(NULL != data) 
    {
        temp.ccpr_low = CCPR1L;
        temp.ccpr_high = CCPR1H;
        *data = temp.ccpr_16Bit;
    }
    else{retval = STD_NOT_OK;}
    return retval;
}
#endif

#if (CCP_MODE_SELECT == CCP_COMPARE_MODE_ENABLE)
STD_RETURN_t MCAL_CCP_IsCompareComplete(uint8 *compare_status)
{
    STD_RETURN_t retval = STD_OK;
    if(NULL != compare_status) 
    {
        if(CCP_COMPARE_READY == PIR1bits.CCP1IF)
        {
            *compare_status = CCP_COMPARE_READY;
            CCP1_INTERRUPT_CLEAR_FLAG();
        }
        else
        {
            *compare_status = CCP_COMPARE_NOT_READY;
        }

    }
    else{retval = STD_NOT_OK;}
    return retval;
}
STD_RETURN_t MCAL_CCP_CompareWriteValue(uint16 value)
{
    STD_RETURN_t retval = STD_OK;
    CCPR_t temp = {.ccpr_low = 0, .ccpr_high = 0};
    temp.ccpr_16Bit = value;
    CCPR1L = temp.ccpr_low;
    CCPR1H = temp.ccpr_high;
    return retval;
}
#endif
#if (CCP_MODE_SELECT == CCP_PWM_MODE_ENABLE)
STD_RETURN_t MCAL_CCP_PWM_START(const CCP_t *ccp)
{
    STD_RETURN_t retval = STD_OK;
    if(NULL != ccp) 
    {
        if(CCP1_instance == ccp->CCPx_Select)
        {
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        }
        else if(CCP2_instance == ccp->CCPx_Select)
        {
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        }
        else
        {
            retval = INVALID_MODE;
        }
    }
    else
    {
        retval = STD_NOT_OK;
    }
    return retval;
}
STD_RETURN_t MCAL_CCP_PWM_STOP(const CCP_t *ccp)
{
    STD_RETURN_t retval = STD_OK;
    if(NULL != ccp) 
    {
        if(CCP1_instance == ccp->CCPx_Select)
        {
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        }
        else if(CCP2_instance == ccp->CCPx_Select)
        {
            CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
        }
        else
        {
            retval = INVALID_MODE;
        }
    }
    else
    {
        retval = STD_NOT_OK;
    }
    return retval;
}
STD_RETURN_t MCAL_CCP_PWM_SetDuty(const CCP_t *ccp, const uint8 duty)
{
    STD_RETURN_t retval = STD_OK;
    if(NULL != ccp) 
    {
        uint16 lduty = (uint16)(4 * (PR2 + 1)* (duty/100.0));
        if(CCP1_instance == ccp->CCPx_Select)
        {
            CCP1CONbits.DC1B = (uint8)(lduty & 0x0003);
            CCPR1L = (uint8)(lduty >> 2);
        }
        else if(CCP2_instance == ccp->CCPx_Select)
        {
            CCP2CONbits.DC2B = (uint8)(lduty & 0x0003);
            CCPR2L = (uint8)(lduty >> 2);
        }
        else
        {
            retval = INVALID_MODE;
        }
    }
    else
    {
        retval = STD_NOT_OK;
    }
    return retval;
}
#endif

static STD_RETURN_t CCP_SelectCapureSubMode(const CCP_t *ccp)
{
    STD_RETURN_t retval = STD_OK;
    if(CCP1_instance == ccp->CCPx_Select)
    {
        switch(ccp->SubMode)
        {
        case CCP_CAPTURE_EVERY_FALLING_EDGE:
            CCP1CONbits.CCP1M = CCP_CAPTURE_EVERY_FALLING_EDGE;
        break;
        case CCP_CAPTURE_EVERY_RISING_EDGE:
            CCP1CONbits.CCP1M = CCP_CAPTURE_EVERY_RISING_EDGE;
        break;
        case CCP_CAPTURE_EVERY_4th_RISING_EDGE:
            CCP1CONbits.CCP1M = CCP_CAPTURE_EVERY_4th_RISING_EDGE;
        break;
        case CCP_CAPTURE_EVERY_16th_RISING_EDGE:
            CCP1CONbits.CCP1M = CCP_CAPTURE_EVERY_16th_RISING_EDGE;
        break;
        default: retval = STD_NOT_OK;
        }
    }
    else if(CCP2_instance == ccp->CCPx_Select)
    {
        switch(ccp->SubMode)
        {
        case CCP_CAPTURE_EVERY_FALLING_EDGE:
            CCP2CONbits.CCP2M = CCP_CAPTURE_EVERY_FALLING_EDGE;
        break;
        case CCP_CAPTURE_EVERY_RISING_EDGE:
            CCP2CONbits.CCP2M = CCP_CAPTURE_EVERY_RISING_EDGE;
        break;
        case CCP_CAPTURE_EVERY_4th_RISING_EDGE:
            CCP2CONbits.CCP2M = CCP_CAPTURE_EVERY_4th_RISING_EDGE;
        break;
        case CCP_CAPTURE_EVERY_16th_RISING_EDGE:
            CCP2CONbits.CCP2M = CCP_CAPTURE_EVERY_16th_RISING_EDGE;
        break;
        default: retval = STD_NOT_OK;
        }
    }
    CCP_CC_TimerSelect(ccp);
    return retval;
}

static STD_RETURN_t CCP_SelectCompareSubMode(const CCP_t *ccp)
{
    STD_RETURN_t retval = STD_OK;
    if(CCP1_instance == ccp->CCPx_Select)
    {
        switch(ccp->SubMode)
        {
            case CCP_COMPARE_TOGGLE_OUTPUT:
                CCP1CONbits.CCP1M = CCP_COMPARE_TOGGLE_OUTPUT;
            break;
            case CCP_COMPARE_INITIALIZE_PIN_LOW:
                CCP1CONbits.CCP1M = CCP_COMPARE_INITIALIZE_PIN_LOW;
            break;
            case CCP_COMPARE_INITIALIZE_PIN_HIGH:
                CCP1CONbits.CCP1M = CCP_COMPARE_INITIALIZE_PIN_HIGH;
            break;
            case CCP_COMPARE_GENERATE_SW_INTERRUPT:
                CCP1CONbits.CCP1M = CCP_COMPARE_GENERATE_SW_INTERRUPT;
            break;
            case CCP_COMPARE_GENERATE_SPECIAL_EVENT:
                CCP1CONbits.CCP1M = CCP_COMPARE_GENERATE_SPECIAL_EVENT;
            break;
            default: 
                retval = INVALID_SUBMODE;
        }
    }
    else if(CCP2_instance == ccp->CCPx_Select)
    {
        switch(ccp->SubMode)
        {
            case CCP_COMPARE_TOGGLE_OUTPUT:
                CCP2CONbits.CCP2M = CCP_COMPARE_TOGGLE_OUTPUT;
            break;
            case CCP_COMPARE_INITIALIZE_PIN_LOW:
                CCP2CONbits.CCP2M = CCP_COMPARE_INITIALIZE_PIN_LOW;
            break;
            case CCP_COMPARE_INITIALIZE_PIN_HIGH:
                CCP2CONbits.CCP2M = CCP_COMPARE_INITIALIZE_PIN_HIGH;
            break;
            case CCP_COMPARE_GENERATE_SW_INTERRUPT:
                CCP2CONbits.CCP2M = CCP_COMPARE_GENERATE_SW_INTERRUPT;
            break;
            case CCP_COMPARE_GENERATE_SPECIAL_EVENT:
                CCP2CONbits.CCP2M = CCP_COMPARE_GENERATE_SPECIAL_EVENT;
            break;
            default: 
                retval = INVALID_SUBMODE;
        }
    }
    else
    {
        retval = INVALID_MODULE;
    }
    CCP_CC_TimerSelect(ccp);
    return retval;
}

static STD_RETURN_t CCP_SelectPWMSubMode(const CCP_t *ccp)
{
    STD_RETURN_t retval = STD_OK;
    if(CCP1_instance == ccp->CCPx_Select)
    {
        if(CCP_PWM_MODE == ccp->SubMode)
        {
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        }
        else
        {
            retval = INVALID_SUBMODE;
        }
       
    }
    else if(CCP2_instance == ccp->CCPx_Select)
    {
        if(CCP_PWM_MODE == ccp->SubMode)
        {
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        }
        else
        {
            retval = INVALID_SUBMODE;
        }
    }
    else
    {
        retval = INVALID_MODULE;
    }
    return retval;
}

static void CCP_InterruptConfig(const CCP_t *ccp)
{
    
#if (CCP1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)
      CCP1_INTERRUPT_DISABLE();
      CCP1_INTERRUPT_CLEAR_FLAG();
      CCP1_InterruptHandler = ccp->CCP1_InterruptHandler;
#if (INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE)
      INTERRUPT_PRIORITY_LEVELS_ENABLE();
      if(INTERRUPT_PRIORITY_HIGH == ccp->CCP1_Priority)
      {
          INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
          CCP1_INTERRUPT_HIGH_PRIORITY();
      } 
      else
      {
         INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
         CCP1_INTERRUPT_LOW_PRIORITY(); 
      } 
#else
      INTERRUPT_GLOBAL_ENABLE();
      INTERRUPT_PERIPHERAL_ENABLE();
#endif
#endif
      
#if (CCP2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE)
      CCP2_INTERRUPT_DISABLE();
      CCP2_INTERRUPT_CLEAR_FLAG();
      CCP2_InterruptHandler = ccp->CCP2_InterruptHandler;
#if (INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE)
      INTERRUPT_PRIORITY_LEVELS_ENABLE();
      if(INTERRUPT_PRIORITY_HIGH == ccp->CCP2_Priority)
      {
          INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
          CCP2_INTERRUPT_HIGH_PRIORITY();
      } 
      else
      {
         INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
         CCP2_INTERRUPT_LOW_PRIORITY(); 
      } 
#else
      INTERRUPT_GLOBAL_ENABLE();
      INTERRUPT_PERIPHERAL_ENABLE();
#endif
#endif
}

static STD_RETURN_t CCP_Disable(const CCP_t *ccp)
{
    STD_RETURN_t retval = STD_OK;
    if(CCP1_instance == ccp->CCPx_Select)
    {
        CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
    }
    else if(CCP2_instance == ccp->CCPx_Select)
    {
        CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
    }
    else
    {
        retval = INVALID_MODULE;
    }
    return retval;
}

static STD_RETURN_t CCP_Enable(const CCP_t *ccp)
{
    STD_RETURN_t retval = STD_OK;
    if(CCP1_instance == ccp->CCPx_Select)
    {
        CCP1CONbits.CCP1M = CCP_MODULE_ENABLE;
    }
    else if(CCP2_instance == ccp->CCPx_Select)
    {
        CCP2CONbits.CCP2M = CCP_MODULE_ENABLE;
    }
    else
    {
        retval = INVALID_MODULE;
    }
    return retval;
}
static void CCP_CC_TimerSelect(const CCP_t *ccp)
{
    if(CCP_CAPTURE_TIM3 == ccp->Capture_TIM_Select)
    {
        T3CONbits.T3CCP1 = 0; 
        T3CONbits.T3CCP2 = 1;
    }
    else if(CCP_CAPTURE_TIM1 == ccp->Capture_TIM_Select)
    {
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    }
    else if(CCP_CAPTURE_TIM1_TIM3 == ccp->Capture_TIM_Select)
    {
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    }
    else{}
}
void CCP1_ISR(void){
    CCP1_INTERRUPT_CLEAR_FLAG();
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
    else{ /* Nothing */ }
}

void CCP2_ISR(void){
    CCP2_INTERRUPT_CLEAR_FLAG();
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
    else{ /* Nothing */ }
}