/* 
 * File:   Timer0_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:23 PM
 */
#include "Timer0_Interface.h"
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*TIMER0_InterruptHandler)(void) = NULL;
#endif

uint16 TMR0_Preload = ZERO_Init;

static void TIMER0_SELECT_MODE(const TIMER0_t *_TMR);
static void TIMER0_SELECT_CONTROL_BIT_SIZE(const TIMER0_t *_TMR);
static void TIMER0_SELECT_PRESCALER(const TIMER0_t *_TMR);

STD_RETURN_t MCAL_TIMER0_Initialize(const TIMER0_t *_TMR){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TIMER0_STOP();
            TIMER0_SELECT_MODE(_TMR);
            TIMER0_SELECT_CONTROL_BIT_SIZE(_TMR);
            TIMER0_SELECT_PRESCALER(_TMR);
            TMR0H = ((_TMR->Preloaded_Value) >> 8);
            TMR0L = (uint8)(_TMR->Preloaded_Value);
            TMR0_Preload = _TMR->Preloaded_Value;
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            TIMER0_INTERRUPT_ENABLE();
            TIMER0_INTERRUPT_CLEAR_FLAG();
            TIMER0_InterruptHandler = _TMR->TMR0_InterruptHandler;
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(Low_Priority == _TMR->TMR0_Priority){
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                TIMER0_INTERRUPT_LOW_PRIORITY();
            }
            else if(High_Priority == _TMR->TMR0_Priority){
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                TIMER0_INTERRUPT_HIGH_PRIORITY();
            }
            else{ /* if you are here then you don't select Priority Levels */}
    
#else
           INTERRUPT_GLOBAL_ENABLE();
           INTERRUPT_PERIPHERAL_ENABLE();
#endif           
#endif            
           TIMER0_ENABLE();
        }   
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER0_DeInitialize(const TIMER0_t *_TMR){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TIMER0_STOP();
#if TIMER0_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            TIMER0_INTERRUPT_DISABLE();
#endif            
        }
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER0_Write_Value(const TIMER0_t *_TMR, uint16 _Value){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _TMR){
            Return_Status = STD_NOT_OK;
        }
        else{
            TMR0H = (_Value) >> 8;
            TMR0L = (uint8)_Value;
        }
    return Return_Status;
}
STD_RETURN_t MCAL_TIMER0_Read_Value(const TIMER0_t *_TMR, uint16 *_Value){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 L_TMR0L = ZERO_Init;
    uint8 L_TMR0H = ZERO_Init;
    
        if((NULL == _TMR) || (NULL == _Value)){
            Return_Status = STD_NOT_OK;
        }
        else{
            L_TMR0L = TMR0L;
            L_TMR0H = TMR0H;
            *_Value = (uint16)((L_TMR0H << 8) + L_TMR0L);
        }
    
    return Return_Status;
}

static void TIMER0_SELECT_MODE(const TIMER0_t *_TMR){
    if(TMR0_TIMER_MODE_ENABLE == _TMR->Mode){
        TIMER0_TIMER_MODE();
    }
    else if(TMR0_COUNTER_MODE_ENABLE == _TMR->Mode){
        TIMER0_COUNTER_MODE();
        if(TMR0_FALLING_EDGE_SOURCE == _TMR->Edge_Source){
            TIMER0_COUNTER_FALLING_EDGE();
        }
        else if(TMR0_RISING_EDGE_SOURCE == _TMR->Edge_Source){
            TIMER0_COUNTER_RISING_EDGE();
        }
        else{ /* if you are here then you don't select edge source */}
    }
    else{ /* if you are here then you don't select any operating mode */}
}
static void TIMER0_SELECT_CONTROL_BIT_SIZE(const TIMER0_t *_TMR){
    if(TMR0_8BIT_CONTROL_REG == _TMR->Register_Size){
        TIMER0_8BIT_TIMER_COUNTER();
    }
    else if(TMR0_16BIT_CONTROL_REG == _TMR->Register_Size){
        TIMER0_16BIT_TIMER_COUNTER();
    }
    else{ /* if you are here then you don't select any Size */}
}
static void TIMER0_SELECT_PRESCALER(const TIMER0_t *_TMR){
    if(TMR0_PRESCALER_DISABLE == _TMR->Prescaler_Enable){
        TIMER0_PRESCALER_DISABLE();
    }
    else if(TMR0_PRESCALER_ENABLE == _TMR->Prescaler_Enable){
        TIMER0_PRESCALER_ENABLE();
        TIMER0_SET_PRESCALER_VALUE(_TMR->Prescaler_Value);
    }
    else{ /* if you are here then you don't select any Size */}
}
void TMR0_ISR(void){
    TIMER0_INTERRUPT_CLEAR_FLAG();
    TMR0H = (TMR0_Preload) >> 8;
    TMR0L = (uint8)(TMR0_Preload);
    if(TIMER0_InterruptHandler){
        TIMER0_InterruptHandler();
    }
}