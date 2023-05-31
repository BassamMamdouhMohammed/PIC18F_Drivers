/* 
 * File:   I2C_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 27, 2022, 9:57 AM
 */
#include "I2C_Interface.h"

static void I2C_Mater_Clock_Configuration(const MSSP_I2C_t *_I2C);
static void I2C_Slave_Mode_Configuration(const MSSP_I2C_t *_I2C);
static void I2C_SlewRate(const MSSP_I2C_t *_I2C);
static void I2C_SMBus(const MSSP_I2C_t *_I2C);
static inline void I2C_Interrupt_Configuration(const MSSP_I2C_t *_I2C);
static inline void I2C_Bus_Collision_Interrupt_Configuration(const MSSP_I2C_t *_I2C);

#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void(* I2c_INTERRUPT_HANDLER)(void) = NULL;
static void(* I2c_INTERRUPT_WRITE_COLLISION)(void)  = NULL;
static void(* I2c_INTERRUPT_RECEIVE_OVERFLOW)(void) = NULL;
#endif

STD_RETURN_t MCAL_MSSP_I2C_Initialize(const MSSP_I2C_t *_I2C){
   STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _I2C){
            Return_Status = STD_NOT_OK;
        }
        else{
            MSSP_MODULE_DISABLE();
            if(I2C_MASTER_MODE == _I2C->I2C_Config.Mode){
                I2C_Mater_Clock_Configuration(_I2C);
            }
            else if(I2C_SLAVE_MODE == _I2C->I2C_Config.Mode){
                if(I2C_GENERAL_CALL_ENABLE == _I2C->I2C_Config.GeneralCall){
                    MSSP_I2C_GENERAL_CALL_ENABLE();
                }
                else if(I2C_GENERAL_CALL_DISABLE == _I2C->I2C_Config.GeneralCall){
                    MSSP_I2C_GENERAL_CALL_DISABLE();
                }
                else{}
                MSSP_I2C_NO_COLLISION_DETECTED();
                MSSP_I2C_RECEIVE_NO_OVERFLOW();
                MSSP_I2C_RELEASE_CLOCK();
                SSPADD = _I2C->I2C_Config.Slave_Address;
                I2C_Slave_Mode_Configuration(_I2C);
            }
            else{}
            TRISCbits.TRISC3 = 1;
            TRISCbits.TRISC4 = 1;
            I2C_SlewRate(_I2C);
            I2C_SMBus(_I2C);
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            I2C_Interrupt_Configuration(_I2C);
#endif        
#if MSSP_BUS_COLLISION_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            I2C_Bus_Collision_Interrupt_Configuration(_I2C);
#endif
            
        } 
   return Return_Status;
}
STD_RETURN_t MCAL_MSSP_I2C_DeInitialize(const MSSP_I2C_t *_I2C){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _I2C){
        Return_Status = STD_NOT_OK;
    }
    else{
         MSSP_MODULE_DISABLE();
         
    }
    return Return_Status;
}
STD_RETURN_t MCAL_MSSP_I2C_Send_Start_Condition(const MSSP_I2C_t *_I2C){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _I2C){
            Return_Status = STD_NOT_OK;
        }
        else{
            MSSP_I2C_SEND_START();
            while(SSPCON2bits.SEN);
            PIR1bits.SSPIF = 0;
            if(I2C_START_BIT_DETECTED == SSPSTATbits.S){
                Return_Status = STD_OK;
            }
            else{
                Return_Status = STD_NOT_OK;
            }
        }
    return Return_Status;
}
STD_RETURN_t MCAL_MSSP_I2C_Send_RStart_Condition(const MSSP_I2C_t *_I2C){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _I2C){
            Return_Status = STD_NOT_OK;
        }
        else{
            MSSP_I2C_SEND_REPEATED_START();
            while(SSPCON2bits.RSEN);
            PIR1bits.SSPIF = 0;
        }
    return Return_Status;
}
STD_RETURN_t MCAL_MSSP_I2C_Send_Stop_Condition(const MSSP_I2C_t *_I2C){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _I2C){
            Return_Status = STD_NOT_OK;
        }
        else{
            MSSP_I2C_SEND_STOP();
            while(SSPCON2bits.PEN);
            PIR1bits.SSPIF = 0;
            if(I2C_STOP_BIT_DETECTED == SSPSTATbits.P){
                Return_Status = STD_OK;
            }
            else{
                Return_Status = STD_NOT_OK;
            }
        }
    return Return_Status;
}
STD_RETURN_t MCAL_MSSP_I2C_Read_Blocking(const MSSP_I2C_t *_I2C,uint8 *_Data,uint8 _ACK){
    STD_RETURN_t Return_Status = STD_OK;
        if((NULL == _I2C) || (NULL == _Data)){
            Return_Status = STD_NOT_OK;
        }
        else{
            MSSP_I2C_MASTER_RECEIVE_ENABLE();
            while(!SSPSTATbits.BF);
           *_Data = SSPBUF;
           if(I2C_MASTER_RECEIVE_ACK == _ACK){
               MSSP_I2C_MASTER_RECEIVE_ACK();
               MSSP_I2C_MASTER_RECEIVE_INITIALIZE_ACK();
               while(SSPCON2bits.ACKEN);
           }
           else if(I2C_MASTER_RECEIVE_NACK == _ACK){
               MSSP_I2C_MASTER_RECEIVE_NACK();
               MSSP_I2C_MASTER_RECEIVE_INITIALIZE_ACK();
               while(SSPCON2bits.ACKEN);
           }
        }
    return Return_Status;
}
STD_RETURN_t MCAL_MSSP_I2C_Write_Blocking(const MSSP_I2C_t *_I2C, uint8 _Data,uint8 *_ACK){
    STD_RETURN_t Return_Status = STD_OK;
        if((NULL == _I2C) || (NULL == _ACK)){
            Return_Status = STD_NOT_OK;
        }
        else{
            SSPBUF = _Data;
            while(SSPSTATbits.BF);
            PIR1bits.SSPIF = 0;
            if(I2C_ACK_RECIEVED_FROM_SLAVE == SSPCON2bits.ACKSTAT){
                Return_Status = STD_OK;
            }
            else{
                Return_Status = STD_NOT_OK;
            }
        }
    return Return_Status;
}

static void I2C_Mater_Clock_Configuration(const MSSP_I2C_t *_I2C){
    MSSP_I2C_SSP_SELECT(_I2C->I2C_Config.SSP_Mode);
    SSPADD = (uint8)(((_XTAL_FREQ / 4.0) / _I2C->I2C_Clock) - 1);
}
static void I2C_Slave_Mode_Configuration(const MSSP_I2C_t *_I2C){
    MSSP_I2C_SSP_SELECT(_I2C->I2C_Config.SSP_Mode);
}
static void I2C_SlewRate(const MSSP_I2C_t *_I2C){
    if(I2C_SLEW_RATE_DISABLE == _I2C->I2C_Config.SlewRate){
        MSSP_I2C_SLEW_RATE_DISABLE();
    }
    else if(I2C_SLEW_RATE_ENABLE == _I2C->I2C_Config.SlewRate){
        MSSP_I2C_SLEW_RATE_ENABLE();
    }
    else{ /* Hello There */}
}
static void I2C_SMBus(const MSSP_I2C_t *_I2C){
    if(I2C_SMBUS_DISABLE == _I2C->I2C_Config.SMBus){
        MSSP_I2C_SMBUS_DISABLE();
    }
    else if(I2C_SMBUS_ENABLE == _I2C->I2C_Config.SMBus){
        MSSP_I2C_SMBUS_ENABLE();
    }
    else{ /* Hello There */}
}
static inline void I2C_Interrupt_Configuration(const MSSP_I2C_t *_I2C){
            MSSP_I2C_INTERRUPT_ENABLE();
            MSSP_I2C_INTERRUPT_CLEAR_FLAG();
            I2c_INTERRUPT_HANDLER = _I2C->I2C_InterruptHandler;
            I2c_INTERRUPT_RECEIVE_OVERFLOW = _I2C->I2C_Receive_Overflow;
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(Low_Priority == _I2C->I2C_Priority){
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                MSSP_I2C_INTERRUPT_LOW_PRIORITY();
            }
            else if(High_Priority == _I2C->I2C_Priority){
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                MSSP_I2C_INTERRUPT_HIGH_PRIORITY();
            }
            else{ /* if you are here then you don't select Priority Levels */}
    
#else
           INTERRUPT_GLOBAL_ENABLE();
           INTERRUPT_PERIPHERAL_ENABLE();
#endif           

}
static inline void I2C_Bus_Collision_Interrupt_Configuration(const MSSP_I2C_t *_I2C){
            BUS_COLLISION_INTERRUPT_ENABLE();
            BUS_COLLISION_INTERRUPT_CLEAR_FLAG();
            I2c_INTERRUPT_WRITE_COLLISION = _I2C->I2C_Write_Collision;
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(Low_Priority == _I2C->I2C_Bus_Priority){
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                BUS_COLLISION_INTERRUPT_LOW_PRIORITY();
            }
            else if(High_Priority == _I2C->I2C_Bus_Priority){
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                BUS_COLLISION_INTERRUPT_HIGH_PRIORITY();
            }
            else{ /* if you are here then you don't select Priority Levels */}
    
#else
           INTERRUPT_GLOBAL_ENABLE();
           INTERRUPT_PERIPHERAL_ENABLE();
#endif           
}