/* 
 * File:   Timer2_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:30 PM
 */
#include "Timer2_Interface.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TIMER2_InterruptHandler)(void) = NULL;
#endif
uint8 TMR2_Preload = ZERO_Init;

STD_RETURN_t MCAL_TIMER2_Initialize(const TIMER2_t *_TMR){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TIMER2_STOP();
            TIMER2_SET_PRESCALER_VALUE(_TMR->Prescaler_Value);
            TIMER2_SET_POSTSCALER_VALUE(_TMR->Postscaler_Value);
            TMR2 = _TMR->Preloaded_Value;
            TMR2_Preload = _TMR->Preloaded_Value;
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            TIMER2_INTERRUPT_ENABLE();
            TIMER2_INTERRUPT_CLEAR_FLAG();
            TIMER2_InterruptHandler = _TMR->TMR2_InterruptHandler;
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(Low_Priority == _TMR->TMR2_Priority){
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                TIMER2_INTERRUPT_LOW_PRIORITY();
            }
            else if(High_Priority == _TMR->TMR2_Priority){
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                TIMER2_INTERRUPT_HIGH_PRIORITY();
            }
            else{ /* if you are here then you don't select Priority Levels */}
    
#else
           INTERRUPT_GLOBAL_ENABLE();
           INTERRUPT_PERIPHERAL_ENABLE();
#endif           
#endif            
           TIMER2_ENABLE();            
        }
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER2_DeInitialize(const TIMER2_t *_TMR){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TIMER2_STOP();
#if TIMER2_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            TIMER2_INTERRUPT_DISABLE();
#endif                        
        }
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER2_Write_Value(const TIMER2_t *_TMR, uint8 _Value){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TMR2 = _Value;
        }
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER2_Read_Value(const TIMER2_t *_TMR, uint8 *_Value){
    STD_RETURN_t Return_Status = STD_OK;
        if((NULL == _TMR) || (NULL == _Value)){
            Return_Status = STD_NOT_OK;
        }
        else{
            *_Value = TMR2;
        }
    return Return_Status;
}
void TMR2_ISR(void){
    TIMER2_INTERRUPT_CLEAR_FLAG();
    TMR2 = TMR2_Preload;
    if(TIMER2_InterruptHandler){
        TIMER2_InterruptHandler();
    }
}