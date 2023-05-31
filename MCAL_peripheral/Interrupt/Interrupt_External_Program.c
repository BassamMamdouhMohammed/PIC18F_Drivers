/* 
 * File:   Interrupt_External_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 14, 2022, 2:15 PM
 */
#include "Interrupt_External_Interface.h"

InterruptHandler INT0_Interrupt_Handler = NULL;
InterruptHandler INT1_Interrupt_Handler = NULL;
InterruptHandler INT2_Interrupt_Handler = NULL;

InterruptHandler RB4_Interrupt_HandlerHigh = NULL;
InterruptHandler RB4_Interrupt_HandlerLow  = NULL;
InterruptHandler RB5_Interrupt_HandlerHigh = NULL;
InterruptHandler RB5_Interrupt_HandlerLow  = NULL;
InterruptHandler RB6_Interrupt_HandlerHigh = NULL;
InterruptHandler RB6_Interrupt_HandlerLow  = NULL;
InterruptHandler RB7_Interrupt_HandlerHigh = NULL;
InterruptHandler RB7_Interrupt_HandlerLow  = NULL;

static void INTx_Enable(const INTx_t *_INTx);
static void INTx_Disable(const INTx_t *_INTx);
static void INTx_Priority(const INTx_t *_INTx);
static void INTx_ClearFlag(const INTx_t *_INTx);
static void INTx_EdgeSource(const INTx_t *_INTx);
static void INTx_SetInterrupt_Handler(const INTx_t *_INTx);

static void RBx_Priority(const RBx_t *_RBx);
static void RBx_SetInterrupt_Handler(const RBx_t *_RBx);

/**
 * 
 * @param _INTx
 * @return 
 */
STD_RETURN_t MCAL_Interrupt_INTx_Initialize(const INTx_t *_INTx){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _INTx){
        Return_Status = STD_NOT_OK;
    }
    else{
        INTx_Disable(_INTx);
        INTx_ClearFlag(_INTx);
        INTx_EdgeSource(_INTx);
        Return_Status = MCAL_GPIO_Pin_Direction_Initialize(&(_INTx->INTx_Pin));
        INTx_SetInterrupt_Handler(_INTx);
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTx_Priority(_INTx);
#endif        
        INTx_Enable(_INTx);
    }
    return Return_Status;
}
/**
 * 
 * @param _INTx
 * @return 
 */
STD_RETURN_t MCAL_Interrupt_INTx_DeInitialize(const INTx_t *_INTx){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _INTx){
        Return_Status = STD_NOT_OK;
    }
    else{
       INTx_Disable(_INTx);
    }
    return Return_Status;
}
/**
 * 
 * @param _RBx
 * @return 
 */
STD_RETURN_t MCAL_Interrupt_RBx_Initialize(const RBx_t *_RBx){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _RBx){
        Return_Status = STD_NOT_OK;
    }
    else{
        INTERRUPT_RBx_DISABLE();
        INTERRUPT_RBx_CLEAR_FLAG();
        RBx_Priority(_RBx);
        Return_Status = MCAL_GPIO_Pin_Direction_Initialize(&(_RBx->RBx_Pin));
        RBx_SetInterrupt_Handler(_RBx);
        INTERRUPT_RBx_ENABLE();
    }
    return Return_Status;
}
/**
 * 
 * @param _RBx
 * @return 
 */
STD_RETURN_t MCAL_Interrupt_RBx_DeInitialize(const RBx_t *_RBx){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _RBx){
        Return_Status = STD_NOT_OK;
    }
    else{
       INTERRUPT_RBx_DISABLE();
       INTERRUPT_RBx_CLEAR_FLAG();
    }
    return Return_Status;
}

static void INTx_Enable(const INTx_t *_INTx){
    switch(_INTx->INTx_Source){
        case EXT_INT0 :
            INTERRUPT_INT0_ENABLE();
            break;
        case EXT_INT1 :
            INTERRUPT_INT1_ENABLE();
            break;
        case EXT_INT2 :
            INTERRUPT_INT2_ENABLE();
            break;
        default: /* Hello There */ ;
    }
}
static void INTx_Disable(const INTx_t *_INTx){
    switch(_INTx->INTx_Source){
        case EXT_INT0 :
            INTERRUPT_INT0_DISABLE();
            break;
        case EXT_INT1 :
            INTERRUPT_INT1_DISABLE();
            break;
        case EXT_INT2 :
            INTERRUPT_INT2_DISABLE();
            break;
        default: /* Hello There */ ;
    }
}
static void INTx_Priority(const INTx_t *_INTx){
    switch(_INTx->INTx_Source){
        case EXT_INT0 :
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
#else
            INTERRUPT_GLOBAL_ENABLE();
            INTERRUPT_PERIPHERAL_ENABLE();
#endif            
            break;
        case EXT_INT1 :
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE  
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(High_Priority == _INTx->INTx_Priority){
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                INTERRUPT_INT1_HIGH_PRIORITY();
            }
            else if(Low_Priority == _INTx->INTx_Priority){
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                INTERRUPT_INT1_LOW_PRIORITY();
            }
#else
            INTERRUPT_GLOBAL_ENABLE();
            INTERRUPT_PERIPHERAL_ENABLE();
#endif
            break;
        case EXT_INT2 :
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE  
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(High_Priority == _INTx->INTx_Priority){
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                INTERRUPT_INT2_HIGH_PRIORITY();
            }
            else if(Low_Priority == _INTx->INTx_Priority){
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                INTERRUPT_INT2_LOW_PRIORITY();
            }
#else
            INTERRUPT_GLOBAL_ENABLE();
            INTERRUPT_PERIPHERAL_ENABLE();
#endif
            break;
        default: /* Hello There */ ;    
    }
}
static void INTx_ClearFlag(const INTx_t *_INTx){
    switch(_INTx->INTx_Source){
        case EXT_INT0 :
            INTERRUPT_INT0_CLEAR_FLAG();
            break;
        case EXT_INT1 :
            INTERRUPT_INT1_CLEAR_FLAG();
            break;
        case EXT_INT2 :
            INTERRUPT_INT2_CLEAR_FLAG();
            break;
        default: /* Hello There */ ;    
    }
}
static void INTx_EdgeSource(const INTx_t *_INTx){
    switch(_INTx->INTx_Source){
        case EXT_INT0 :
            if(INTx_RISING_EDGE == _INTx->INTx_Edge){
                INTERRUPT_INT0_RISING_EDGE();
            }
            else if(INTx_FALLING_EDGE == _INTx->INTx_Edge){
                INTERRUPT_INT0_FALLING_EDGE();
            }
            break;
        case EXT_INT1 :
            if(INTx_RISING_EDGE == _INTx->INTx_Edge){
                INTERRUPT_INT1_RISING_EDGE();
            }
            else if(INTx_FALLING_EDGE == _INTx->INTx_Edge){
                INTERRUPT_INT1_FALLING_EDGE();
            }
            break;
        case EXT_INT2 :
            if(INTx_RISING_EDGE == _INTx->INTx_Edge){
                INTERRUPT_INT2_RISING_EDGE();
            }
            else if(INTx_FALLING_EDGE == _INTx->INTx_Edge){
                INTERRUPT_INT2_FALLING_EDGE();
            }
            break;
        default: /* Hello There */ ;    
    }
}
static void INTx_SetInterrupt_Handler(const INTx_t *_INTx){
    switch(_INTx->INTx_Source){
        case EXT_INT0 :
            INT0_Interrupt_Handler = _INTx->INTx_InterruptHandler;
            break;
        case EXT_INT1 :
            INT1_Interrupt_Handler = _INTx->INTx_InterruptHandler;
            break;
        case EXT_INT2 :
            INT2_Interrupt_Handler = _INTx->INTx_InterruptHandler;
            break;
        default: /* Hello There */ ;    
    }
}
static void RBx_Priority(const RBx_t *_RBx){
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PRIORITY_LEVELS_ENABLE();
        if(Low_Priority == _RBx->RBx_Priority){
            INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
            INTERRUPT_RB_LOW_PRIORITY();
        }
        else if(High_Priority == _RBx->RBx_Priority){
            INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
            INTERRUPT_RB_HIGH_PRIORITY();
        }
        else{/* Hello There */}
#else
            INTERRUPT_GLOBAL_ENABLE();
            INTERRUPT_PERIPHERAL_ENABLE();
#endif
            
}
static void RBx_SetInterrupt_Handler(const RBx_t *_RBx){
    switch(_RBx->RBx_Pin.PIN){
        case GPIO_pin4 :
            RB4_Interrupt_HandlerHigh = _RBx->RBx_InterruptHandler_High;
            RB4_Interrupt_HandlerLow  = _RBx->RBx_InterruptHandler_Low;
            break;
        case GPIO_pin5 :
            RB5_Interrupt_HandlerHigh = _RBx->RBx_InterruptHandler_High;
            RB5_Interrupt_HandlerLow  = _RBx->RBx_InterruptHandler_Low;
            break;
        case GPIO_pin6 :
            RB6_Interrupt_HandlerHigh = _RBx->RBx_InterruptHandler_High;
            RB6_Interrupt_HandlerLow  = _RBx->RBx_InterruptHandler_Low;
            break;
        case GPIO_pin7 :
            RB7_Interrupt_HandlerHigh = _RBx->RBx_InterruptHandler_High;
            RB7_Interrupt_HandlerLow  = _RBx->RBx_InterruptHandler_Low;
            break;    
        default: /* Hello There */ ;    
    }
}