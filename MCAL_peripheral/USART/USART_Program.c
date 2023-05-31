/*
 * File:   USART_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 18, 2022, 1:26 PM
 */
#include "USART_Interface.h"

static void BaudRate_Estimate(const UART_t *_UART);
static void UART_Tx_Initialize(const UART_t *_UART);
static void UART_Rx_Initialize(const UART_t *_UART);

#if UART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*UART_TX_InterruptHandler)(void) = NULL;
#endif

#if UART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*UART_RX_InterruptHandler)(void) = NULL;
static void (*UART_FRAMMING_ERROR_InterruptHandler)(void) = NULL;
static void (*UART_OVERRUN_ERROR_InterruptHandler)(void) = NULL;
#endif

STD_RETURN_t MCAL_UART_Initialize(const UART_t *_UART){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _UART){
        Return_Status = STD_NOT_OK;
    }
    else{
        UART_SERIAL_PORT_DISABLE();
        TRISCbits.RC6 = 1;
        TRISCbits.RC7 = 1;
        BaudRate_Estimate(_UART);
        UART_Tx_Initialize(_UART);
        UART_Rx_Initialize(_UART);
        UART_SERIAL_PORT_ENABLE();
    }
    return Return_Status;
}
STD_RETURN_t MCAL_UART_DeInitialize(const UART_t *_UART){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _UART){
        Return_Status = STD_NOT_OK;
    }
    else{
        UART_SERIAL_PORT_DISABLE();
    }
    return Return_Status;
}
STD_RETURN_t MCAL_UART_WriteByte_Blocking(uint8 _Data){
    STD_RETURN_t Return_Status = STD_OK;
    while(!TXSTAbits.TRMT);
#if UART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    UART_TX_INTERRUPT_ENABLE();
#endif
    TXREG = _Data;
    return Return_Status;
}
STD_RETURN_t MCAL_UART_ReadByte_Blocking(uint8 *_Data){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _Data){
        Return_Status = STD_NOT_OK;
    }
    else{
        while(!PIR1bits.RCIF);
        *_Data = RCREG;
    }
    return Return_Status;
}
static void BaudRate_Estimate(const UART_t *_UART){
    float Baud_Rate = ZERO_Init;
    switch(_UART->BaudRate_Formula){
        case BaudRate_Asyn_8Bit_LowSpeed :
            UART_8BIT_BAUD_GENERATOR();
            UART_ASYNCHRONOUS_MODE();
            UART_Asynchronous_LOW_SPEED();
            Baud_Rate = ((_XTAL_FREQ / (float)_UART->BaudRate) / 64) - 1;
            break;
        case BaudRate_Asyn_8Bit_HighSpeed :
            UART_8BIT_BAUD_GENERATOR();
            UART_ASYNCHRONOUS_MODE();
            UART_Asynchronous_HIGH_SPEED();
            Baud_Rate = ((_XTAL_FREQ / (float)_UART->BaudRate) / 16) - 1;
            break;
        case BaudRate_Asyn_16Bit_LowSpeed :
            UART_16BIT_BAUD_GENERATOR();
            UART_ASYNCHRONOUS_MODE();
            UART_Asynchronous_LOW_SPEED();
            Baud_Rate = ((_XTAL_FREQ / (float)_UART->BaudRate) / 16) - 1;
            break;
        case BaudRate_Asyn_16Bit_HighSpeed :
            UART_16BIT_BAUD_GENERATOR();
            UART_ASYNCHRONOUS_MODE();
            UART_Asynchronous_HIGH_SPEED();
            Baud_Rate = ((_XTAL_FREQ / (float)_UART->BaudRate) / 4) - 1;
            break;
        case BaudRate_Syn_16Bit:
            UART_16BIT_BAUD_GENERATOR();
            UART_SYNCHRONOUS_MODE();
            Baud_Rate = ((_XTAL_FREQ / (float)_UART->BaudRate) / 4) - 1;
            break;
        case BaudRate_Syn_8Bit:
            UART_8BIT_BAUD_GENERATOR();
            UART_SYNCHRONOUS_MODE();
            Baud_Rate = ((_XTAL_FREQ / (float)_UART->BaudRate) / 4) - 1;
            break;
        default: /* Hello There */ ;
    }
    SPBRG  = (uint8)((uint32)Baud_Rate);
    SPBRGH = (uint8)(((uint32)Baud_Rate) >> 8);
}
static void UART_Tx_Initialize(const UART_t *_UART){
    if(uart_TX_ENABLE == _UART->TX_Config.TX_Enable){
        UART_TX_ENABLE();
        UART_TX_InterruptHandler = _UART->UART_tx_InterruptHandler;
        if(uart_TX_INTERRUPT_ENABLE == _UART->TX_Config.TX_Interrupt_Enable){
#if UART_TX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            UART_TX_INTERRUPT_ENABLE();
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(High_Priority == _UART->TX_Config.TX_Priority){
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                UART_TX_INTERRUPT_HIGH_PRIORITY();
            }
            else if(Low_Priority == _UART->TX_Config.TX_Priority){
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                UART_TX_INTERRUPT_LOW_PRIORITY();
            }
            else{}
#else
            INTERRUPT_GLOBAL_ENABLE();
            INTERRUPT_PERIPHERAL_ENABLE();
#endif
#endif
        }
        else if(uart_TX_INTERRUPT_DISABLE == _UART->TX_Config.TX_Interrupt_Enable){
            UART_TX_INTERRUPT_DISABLE();
        }
        else{ /* Hello There*/ }

        if(uart_9BIT_TX_ENABLE == _UART->TX_Config.TX_9Bit_Enable){
            UART_9BIT_TX_ENABLE();
        }
        else if(uart_9BIT_TX_DISABLE == _UART->TX_Config.TX_9Bit_Enable){
            UART_9BIT_TX_DISABLE();
        }
        else{ /* Hello There*/ }
    }
    else{ /* Hello There*/ }
}
static void UART_Rx_Initialize(const UART_t *_UART){
    if(uart_RX_ENABLE == _UART->RX_Config.RX_Enable){
        UART_RX_ENABLE();
        UART_RX_InterruptHandler = _UART->UART_rx_InterruptHandler;
        UART_FRAMMING_ERROR_InterruptHandler = _UART->UART_FrammingError_InterruptHandler;
        UART_OVERRUN_ERROR_InterruptHandler = _UART->UART_OverrunError_InterruptHandler;
        if(uart_RX_INTERRUPT_ENABLE == _UART->RX_Config.RX_Interrupt_Enable){
#if UART_RX_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            UART_RX_INTERRUPT_ENABLE();
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(High_Priority == _UART->RX_Config.RX_Priority){
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                UART_RX_INTERRUPT_HIGH_PRIORITY();
            }
            else if(Low_Priority == _UART->RX_Config.RX_Priority){
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                UART_RX_INTERRUPT_LOW_PRIORITY();
            }
            else{}
#else
            INTERRUPT_GLOBAL_ENABLE();
            INTERRUPT_PERIPHERAL_ENABLE();
#endif
#endif
        }
        else if(uart_RX_INTERRUPT_DISABLE == _UART->RX_Config.RX_Interrupt_Enable){
            UART_RX_INTERRUPT_DISABLE();
        }
        else{ /* Hello There*/ }

        if(uart_9BIT_RX_ENABLE == _UART->RX_Config.RX_9Bit_Enable){
            UART_9BIT_RX_ENABLE();
        }
        else if(uart_9BIT_RX_DISABLE == _UART->RX_Config.RX_9Bit_Enable){
            UART_9BIT_RX_DISABLE();
        }
        else{ /* Hello There*/ }
    }
    else{ /* Hello There*/ }
}
STD_RETURN_t USART_Asynchronous_WriteByte_NoBlocking(uint8 _Data){
    STD_RETURN_t Return_Status = STD_OK;
    if(1 == TXSTAbits.TRMT){
        TXREG = _Data;
    }
    else{
        Return_Status = STD_NOT_OK;
    }
    return Return_Status;
}
STD_RETURN_t USART_Asynchronous_ReadByte_NoBlocking(uint8 *_Data){
    STD_RETURN_t Return_Status = STD_OK;
    if(1 == PIR1bits.RCIF){
        *_Data = RCREG;
    }
    else{
        Return_Status = STD_NOT_OK;
    }
    return Return_Status;
}
STD_RETURN_t USART_Asynchronous_WriteString_Blocking(uint8 *_Data, uint16 str_Length){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == _Data) || (str_Length <= 0)){
        Return_Status = STD_NOT_OK;
    }
    else{
        uint16 Chr_Iterator = ZERO_Init;
        for(Chr_Iterator = ZERO_Init; Chr_Iterator < str_Length; Chr_Iterator++){
        Return_Status = MCAL_UART_WriteByte_Blocking(_Data[Chr_Iterator]);
        }
    }
    return Return_Status;
}
void UART_TX_ISR(void){
    UART_TX_INTERRUPT_CLEAR_FLAG();
    if(UART_TX_InterruptHandler){
        UART_TX_InterruptHandler();
    }
    else{ /* Hello There */}
}
void UART_RX_ISR(void){
    UART_RX_INTERRUPT_CLEAR_FLAG();
    if(UART_RX_InterruptHandler){
        UART_RX_InterruptHandler();
    }
    else{ /* Hello There */}
    if(UART_FRAMMING_ERROR_InterruptHandler){
        UART_FRAMMING_ERROR_InterruptHandler();
    }
    else{ /* Hello There */}
    if(UART_OVERRUN_ERROR_InterruptHandler){
        UART_OVERRUN_ERROR_InterruptHandler();
    }
    else{ /* Hello There */}
}