/* 
 * File:   I2C_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 27, 2022, 9:57 AM
 */

#ifndef I2C_INTERFACE_H
#define	I2C_INTERFACE_H

/********************************* Includes *********************************/
#include "../Interrupt/Interrupt_Internal_Interface.h"
#include "../GPIO/GPIO_Interface.h"
/********************************* Macro Definitions ************************/
#define I2C_START_BIT_DETECTED     1
#define I2C_START_BIT_NOT_DETECTED 0

#define I2C_STOP_BIT_DETECTED      1
#define I2C_STOP_BIT_NOT_DETECTED  0

#define I2C_ACK_RECIEVED_FROM_SLAVE      0
#define I2C_ACK_NOT_RECIEVED_FROM_SLAVE  1

#define I2C_LAST_RT_BYTE_DATA      1
#define I2C_LAST_RT_BYTE_ADDRESS   0

#define I2C_SLEW_RATE_ENABLE       0
#define I2C_SLEW_RATE_DISABLE      1

#define I2C_SMBUS_ENABLE           1
#define I2C_SMBUS_DISABLE          0

#define I2C_GENERAL_CALL_ENABLE    1
#define I2C_GENERAL_CALL_DISABLE   0

#define I2C_MASTER_MODE            1
#define I2C_SLAVE_MODE             0

#define I2C_MASTER_RECEIVE_ACK     0
#define I2C_MASTER_RECEIVE_NACK    1

#define I2C_SLAVE_7BIT_ADDRESS           0x06U
#define I2C_SLAVE_10BIT_ADDRESS          0x07U
#define I2C_MASTER_MODE_CLOCK            0x08U
#define I2C_MASTER_FIRMWARE_CONTROLLED   0x0BU
#define I2C_SLAVE_7BIT_WITH_INTERRUPT    0x0EU
#define I2C_SLAVE_10BIT_WITH_INTERRUPT   0x0FU

/********************************* Macro Functions  *************************/
/* SSPSTAT: MSSP STATUS REGISTER (I2C? MODE) */
/* bit 6 CKE: SMBus Select bit */
#define MSSP_I2C_SMBUS_ENABLE()                 (SSPSTATbits.CKE = 1)
#define MSSP_I2C_SMBUS_DISABLE()                (SSPSTATbits.CKE = 0)
/* bit 7 SMP: Slew Rate Control bit */
#define MSSP_I2C_SLEW_RATE_ENABLE()             (SSPSTATbits.SMP = 0)
#define MSSP_I2C_SLEW_RATE_DISABLE()            (SSPSTATbits.SMP = 1)
/* SSPCON1: MSSP CONTROL REGISTER 1 (I2C? MODE) */
/* bit 5 SSPEN: Master Synchronous Serial Port Enable bit(1) */
#define MSSP_MODULE_ENABLE()                    (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE()                   (SSPCON1bits.SSPEN = 0)
/* bit 3-0 SSPM3:SSPM0: Master Synchronous Serial Port Mode Select bits(2) */
#define MSSP_I2C_SSP_SELECT(_Config)     (SSPCON1bits.SSPM = _Config)
/* bit 7 WCOL: Write Collision Detect bit */
#define MSSP_I2C_NO_COLLISION_DETECTED()        (SSPCON1bits.WCOL = 0)
#define MSSP_I2C_COLLISION_DETECTED()           (SSPCON1bits.WCOL = 1)
/* bit 6 SSPOV: Receive Overflow Indicator bit */
#define MSSP_I2C_RECEIVE_OVERFLOW()             (SSPCON1bits.SSPOV = 1)
#define MSSP_I2C_RECEIVE_NO_OVERFLOW()          (SSPCON1bits.SSPOV = 0)
/* bit 4 CKP: SCK Release Control bit */
#define MSSP_I2C_RELEASE_CLOCK()                (SSPCON1bits.CKP = 1)
#define MSSP_I2C_HOLDS_CLOCK()                  (SSPCON1bits.CKP = 0)
/* SSPCON2: MSSP CONTROL REGISTER 2 (I2C? MODE) */
/* bit 7 GCEN: General Call Enable bit (Slave mode only) */
#define MSSP_I2C_GENERAL_CALL_ENABLE()          (SSPCON2bits.GCEN = 1)
#define MSSP_I2C_GENERAL_CALL_DISABLE()         (SSPCON2bits.GCEN = 0)
/* bit 3 RCEN: Receive Enable bit (Master mode only)(1) */
#define MSSP_I2C_MASTER_RECEIVE_ENABLE()        (SSPCON2bits.RCEN = 1)
#define MSSP_I2C_MASTER_RECEIVE_DISABLE()       (SSPCON2bits.RCEN = 0)
/* bit 0 SEN: Start Condition Enable/Stretch Enable bit(1) */
#define MSSP_I2C_SEND_START()                   (SSPCON2bits.SEN = 1)
#define MSSP_I2C_IDLE_START()                   (SSPCON2bits.SEN = 0)
/* bit 1 RSEN: Repeated Start Condition Enable bit (Master mode only)(1) */
#define MSSP_I2C_SEND_REPEATED_START()          (SSPCON2bits.RSEN = 1)
#define MSSP_I2C_IDLE_REPEATED_START()          (SSPCON2bits.RSEN = 0)
/* bit 2 PEN: Stop Condition Enable bit (Master mode only)(1) */
#define MSSP_I2C_SEND_STOP()                    (SSPCON2bits.PEN = 1)
#define MSSP_I2C_IDLE_STOP()                    (SSPCON2bits.PEN = 0)
/* bit 5 ACKDT: Acknowledge Data bit (Master Receive mode only)(2) */
#define MSSP_I2C_MASTER_RECEIVE_ACK()           (SSPCON2bits.ACKDT = 0)
#define MSSP_I2C_MASTER_RECEIVE_NACK()          (SSPCON2bits.ACKDT = 1)
/* bit 4 ACKEN: Acknowledge Sequence Enable bit (Master Receive mode only)(1) */
#define MSSP_I2C_MASTER_RECEIVE_INITIALIZE_ACK() (SSPCON2bits.ACKEN = 1)
#define MSSP_I2C_MASTER_RECEIVE_IDLE_ACK()       (SSPCON2bits.ACKEN = 0)
/********************************* User-Defined Data Types ******************/
typedef struct{
    uint8 Slave_Address;
    uint8 SSP_Mode;
    uint8 Mode :1;
    uint8 SlewRate :1;
    uint8 GeneralCall :1;
    uint8 SMBus :1;
    uint8 Master_Receive :1;
    uint8 Reserved :3;
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE    
    Priority_t I2C_Priority;
    Priority_t I2C_Bus_Priority;
#endif
}I2C_t;

typedef struct{
   uint32 I2C_Clock;
   I2C_t I2C_Config;
#if MSSP_I2C_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
   void (*I2C_InterruptHandler)(void);
   void (*I2C_Write_Collision)(void);
   void (*I2C_Receive_Overflow)(void);
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE    
    Priority_t I2C_Priority;
    Priority_t I2C_Bus_Priority;
#endif   
#endif   
}MSSP_I2C_t;

/********************************* Functions Declaration ********************/
STD_RETURN_t MCAL_MSSP_I2C_Initialize(const MSSP_I2C_t *_I2C);
STD_RETURN_t MCAL_MSSP_I2C_DeInitialize(const MSSP_I2C_t *_I2C);
STD_RETURN_t MCAL_MSSP_I2C_Send_Start_Condition(const MSSP_I2C_t *_I2C);
STD_RETURN_t MCAL_MSSP_I2C_Send_RStart_Condition(const MSSP_I2C_t *_I2C);
STD_RETURN_t MCAL_MSSP_I2C_Send_Stop_Condition(const MSSP_I2C_t *_I2C);
STD_RETURN_t MCAL_MSSP_I2C_Read_Blocking(const MSSP_I2C_t *_I2C,uint8 *_Data,uint8 _ACK);
STD_RETURN_t MCAL_MSSP_I2C_Write_Blocking(const MSSP_I2C_t *_I2C, uint8 _Data,uint8 *_ACK);
#endif	/* I2C_INTERFACE_H */

