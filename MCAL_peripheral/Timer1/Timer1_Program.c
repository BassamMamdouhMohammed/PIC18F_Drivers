/* 
 * File:   Timer1_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:28 PM
 */
#include "Timer1_Interface.h"

#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TIMER1_InterruptHandler)(void) = NULL;
#endif
uint16 TMR1_Preload = ZERO_Init;
static void TIMER1_SELECT_MODE(const TIMER1_t *_TMR);
STD_RETURN_t MCAL_TIMER1_Initialize(const TIMER1_t *_TMR){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TIMER1_STOP();
            TIMER1_SELECT_MODE(_TMR);
            TIMER1_SET_PRESCALER_VALUE(_TMR->Prescaler_Value);
            TMR1H = ((_TMR->Preloaded_Value) >> 8);
            TMR1L = (uint8)(_TMR->Preloaded_Value);
            TMR1_Preload = _TMR->Preloaded_Value;
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            TIMER1_INTERRUPT_ENABLE();
            TIMER1_INTERRUPT_CLEAR_FLAG();
            TIMER1_InterruptHandler = _TMR->TMR1_InterruptHandler;
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(Low_Priority == _TMR->TMR1_Priority){
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                TIMER1_INTERRUPT_LOW_PRIORITY();
            }
            else if(High_Priority == _TMR->TMR1_Priority){
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                TIMER1_INTERRUPT_HIGH_PRIORITY();
            }
            else{ /* if you are here then you don't select Priority Levels */}
    
#else
           INTERRUPT_GLOBAL_ENABLE();
           INTERRUPT_PERIPHERAL_ENABLE();
#endif           
#endif            
           TIMER1_ENABLE();
        }
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER1_DeInitialize(const TIMER1_t *_TMR){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TIMER1_STOP();
#if TIMER1_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            TIMER1_INTERRUPT_DISABLE();
#endif            
        }
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER1_Write_Value(const TIMER1_t *_TMR, uint16 _Value){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TMR1H = ((_Value) >> 8);
            TMR1L = (uint8)_Value;
        }
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER1_Read_Value(const TIMER1_t *_TMR, uint16 *_Value){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 L_TMR1L = ZERO_Init;
    uint8 L_TMR1H = ZERO_Init;
        if((NULL == _TMR) || (NULL == _Value)){
            Return_Status = STD_NOT_OK;
        }
        else{
            L_TMR1L = TMR1L;
            L_TMR1H = TMR1H;
            *_Value = (uint16)((L_TMR1H << 8) + L_TMR1L);
        }
    return Return_Status;
}
static void TIMER1_SELECT_MODE(const TIMER1_t *_TMR){
    if(TMR1_TIMER_MODE_ENABLE == _TMR->Mode){
        TIMER1_TIMER_MODE();
    }
    else if(TMR1_COUNTER_MODE_ENABLE == _TMR->Mode){
        TIMER1_COUNTER_MODE();
        if(TMR1_COUNTER_ASYNCHRONOUS == _TMR->Clock_Mode){
            TIMER1_COUNTER_ASYNCHRONOUS();
        }
        else if(TMR1_COUNTER_SYNCHRONOUS == _TMR->Clock_Mode){
            TIMER1_COUNTER_SYNCHRONOUS();
        }
        else{ /* if you are here then you don't select External Clock Input Synchronization */}
    }
    else{ /* if you are here then you don't select any operating mode */}
}
void TMR1_ISR(void){
    TIMER1_INTERRUPT_CLEAR_FLAG();
    TMR1H = (TMR1_Preload) >> 8;
    TMR1L = (uint8)(TMR1_Preload);
    if(TIMER1_InterruptHandler){
        TIMER1_InterruptHandler();
    }
}