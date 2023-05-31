/* 
 * File:   Timer3_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:32 PM
 */
#include "Timer3_Interface.h"

#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TIMER3_InterruptHandler)(void) = NULL;
#endif
uint16 TMR3_Preload = ZERO_Init;
static void TIMER3_SELECT_MODE(const TIMER3_t *_TMR);
STD_RETURN_t MCAL_TIMER3_Initialize(const TIMER3_t *_TMR){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TIMER3_STOP();
            TIMER3_SELECT_MODE(_TMR);
            TIMER3_SET_PRESCALER_VALUE(_TMR->Prescaler_Value);
            TMR3H = ((_TMR->Preloaded_Value) >> 8);
            TMR3L = (uint8)(_TMR->Preloaded_Value);
            TMR3_Preload = _TMR->Preloaded_Value;
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            TIMER3_INTERRUPT_ENABLE();
            TIMER3_INTERRUPT_CLEAR_FLAG();
            TIMER3_InterruptHandler = _TMR->TMR3_InterruptHandler;
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(Low_Priority == _TMR->TMR3_Priority){
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                TIMER3_INTERRUPT_LOW_PRIORITY();
            }
            else if(High_Priority == _TMR->TMR3_Priority){
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                TIMER3_INTERRUPT_HIGH_PRIORITY();
            }
            else{ /* if you are here then you don't select Priority Levels */}
    
#else
           INTERRUPT_GLOBAL_ENABLE();
           INTERRUPT_PERIPHERAL_ENABLE();
#endif           
#endif            
           TIMER3_ENABLE();
        }
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER3_DeInitialize(const TIMER3_t *_TMR){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TIMER3_STOP();
#if TIMER3_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            TIMER3_INTERRUPT_DISABLE();
#endif            
        }
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER3_Write_Value(const TIMER3_t *_TMR, uint16 _Value){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TMR3H = ((_Value) >> 8);
            TMR3L = (uint8)_Value;
        }
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER3_Read_Value(const TIMER3_t *_TMR, uint16 *_Value){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 L_TMR3L = ZERO_Init;
    uint8 L_TMR3H = ZERO_Init;
        if((NULL == _TMR) || (NULL == _Value)){
            Return_Status = STD_NOT_OK;
        }
        else{
            L_TMR3L = TMR3L;
            L_TMR3H = TMR3H;
            *_Value = (uint16)((L_TMR3H << 8) + L_TMR3L);
        }
    return Return_Status;
}
static void TIMER3_SELECT_MODE(const TIMER3_t *_TMR){
    if(TMR3_TIMER_MODE_ENABLE == _TMR->Mode){
        TIMER3_TIMER_MODE();
    }
    else if(TMR3_COUNTER_MODE_ENABLE == _TMR->Mode){
        TIMER3_COUNTER_MODE();
        if(TMR3_COUNTER_ASYNCHRONOUS == _TMR->Clock_Mode){
            TIMER3_COUNTER_ASYNCHRONOUS();
        }
        else if(TMR3_COUNTER_SYNCHRONOUS == _TMR->Clock_Mode){
            TIMER3_COUNTER_SYNCHRONOUS();
        }
        else{ /* if you are here then you don't select External Clock Input Synchronization */}
    }
    else{ /* if you are here then you don't select any operating mode */}
}
void TMR3_ISR(void){
    TIMER3_INTERRUPT_CLEAR_FLAG();
    TMR3H = (TMR3_Preload) >> 8;
    TMR3L = (uint8)(TMR3_Preload);
    if(TIMER3_InterruptHandler){
        TIMER3_InterruptHandler();
    }
}