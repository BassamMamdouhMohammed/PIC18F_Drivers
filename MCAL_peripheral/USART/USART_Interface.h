/* 
 * File:   USART_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 18, 2022, 1:26 PM
 */

#ifndef USART_INTERFACE_H
#define	USART_INTERFACE_H

/********************************* Includes *********************************/
#include "../GPIO/GPIO_Interface.h"
#include "../Interrupt/Interrupt_Internal_Interface.h"
/********************************* Macro Definitions ************************/
#define uart_TX_ENABLE 1
#define uart_RX_ENABLE 1
#define uart_TX_INTERRUPT_ENABLE  1
#define uart_TX_INTERRUPT_DISABLE 0
#define uart_RX_INTERRUPT_ENABLE  1
#define uart_RX_INTERRUPT_DISABLE 0
#define uart_9BIT_TX_ENABLE  1
#define uart_9BIT_TX_DISABLE 0
#define uart_9BIT_RX_ENABLE  1
#define uart_9BIT_RX_DISABLE 0
/********************************* Macro Functions  *************************/
/* TXSTA: TRANSMIT STATUS AND CONTROL REGISTER     */
/* bit 4 SYNC: EUSART Mode Select bit    */
#define UART_ASYNCHRONOUS_MODE()       (TXSTAbits.SYNC = 0)
#define UART_SYNCHRONOUS_MODE()        (TXSTAbits.SYNC = 1)
/* bit 5 TXEN: Transmit Enable bit       */

#define UART_TX_ENABLE()               (TXSTAbits.TXEN = 1)
#define UART_TX_DISABLE()              (TXSTAbits.TXEN = 0)
/* bit 6 TX9: 9-Bit Transmit Enable bit  */
#define UART_9BIT_TX_ENABLE()          (TXSTAbits.TX9 = 1)
#define UART_9BIT_TX_DISABLE()         (TXSTAbits.TX9 = 0)
/* bit 2 BRGH: High Baud Rate Select bit */
#define UART_Asynchronous_LOW_SPEED()  (TXSTAbits.BRGH = 0)
#define UART_Asynchronous_HIGH_SPEED() (TXSTAbits.BRGH = 1)

/* RCSTA: RECEIVE STATUS AND CONTROL REGISTER       */
/* bit 7 SPEN: Serial Port Enable bit  */
#define UART_SERIAL_PORT_ENABLE()       (RCSTAbits.SPEN = 1)
#define UART_SERIAL_PORT_DISABLE()      (RCSTAbits.SPEN = 0)
/* bit 6 RX9: 9-Bit Receive Enable bit */
#define UART_9BIT_RX_ENABLE()           (RCSTAbits.RX9 = 1)
#define UART_9BIT_RX_DISABLE()          (RCSTAbits.RX9 = 0)
/* bit 2 FERR: Framing Error bit       */
#define UART_FRAMMINIG_ERROR_DETECTED() (RCSTAbits.FERR = 1)
#define UART_FRAMMINIG_ERROR_CLEARED()  (RCSTAbits.FERR = 0)
/* bit 1 OERR: Overrun Error bit       */
#define UART_OVERRUN_ERROR_DETECTED()   (RCSTAbits.OERR = 1)
#define UART_OVERRUN_ERROR_CLEARED()    (RCSTAbits.OERR = 0)
/* bit 4 CREN: Continuous Receive Enable bit */
#define UART_RX_ENABLE()                (RCSTAbits.CREN = 1)
#define UART_RX_DISABLE()               (RCSTAbits.CREN = 0)

/* BAUDCON: BAUD RATE CONTROL REGISTER               */
/* bit 3 BRG16: 16-Bit Baud Rate Register Enable bit */
#define UART_16BIT_BAUD_GENERATOR()     (BAUDCONbits.BRG16 = 1)
#define UART_8BIT_BAUD_GENERATOR()      (BAUDCONbits.BRG16 = 0)

/* PIE1: PERIPHERAL INTERRUPT ENABLE REGISTER 1     */
/* bit 4 TXIE: EUSART Transmit Interrupt Enable bit */
#define UART_TX_INTERRUPT_ENABLE()      (PIE1bits.TXIE = 1)
#define UART_TX_INTERRUPT_DISABLE()     (PIE1bits.TXIE = 0)

/* PIE1: PERIPHERAL INTERRUPT ENABLE REGISTER 1     */
/* bit 5 RCIE: EUSART Receive Interrupt Enable bit  */
#define UART_RX_INTERRUPT_ENABLE()      (PIE1bits.RCIE = 1)
#define UART_RX_INTERRUPT_DISABLE()     (PIE1bits.RCIE = 0)
/********************************* User-Defined Data Types ******************/
typedef enum{
    BaudRate_Asyn_8Bit_LowSpeed,
    BaudRate_Asyn_8Bit_HighSpeed, 
    BaudRate_Asyn_16Bit_LowSpeed,
    BaudRate_Asyn_16Bit_HighSpeed,
    BaudRate_Syn_8Bit,
    BaudRate_Syn_16Bit        
}BaudRate_t;
typedef struct{
    Priority_t TX_Priority;
    uint8 TX_Enable           : 1;
    uint8 TX_Interrupt_Enable : 1;
    uint8 TX_9Bit_Enable      : 1;
    uint8 Reserved            : 5;
}UART_TX_t;
typedef struct{
    Priority_t RX_Priority;
    uint8 RX_Enable           : 1;
    uint8 RX_Interrupt_Enable : 1;
    uint8 RX_9Bit_Enable      : 1;
    uint8 Reserved            : 5;
}UART_RX_t;
typedef union{
    uint8 Reserved   : 6;
    uint8 uart_ferr : 1;
    uint8 uart_oerr : 1;
}UART_Error_t;
typedef struct{
    uint32 BaudRate;
    BaudRate_t BaudRate_Formula;
    UART_RX_t RX_Config;
    UART_TX_t TX_Config;
    void (* UART_tx_InterruptHandler)(void);
    void (* UART_rx_InterruptHandler)(void);
    void (* UART_FrammingError_InterruptHandler)(void);
    void (* UART_OverrunError_InterruptHandler)(void);
}UART_t;
/********************************* Functions Declaration ********************/
STD_RETURN_t MCAL_UART_Initialize(const UART_t *_USART);
STD_RETURN_t MCAL_UART_DeInitialize(const UART_t *_USART);
STD_RETURN_t MCAL_UART_WriteByte_Blocking(uint8 _Data);
STD_RETURN_t MCAL_UART_ReadByte_Blocking(uint8 *_Data);
STD_RETURN_t MCAL_UART_WriteString_Blocking(uint8 *_Data, uint16 str_Length);
STD_RETURN_t MCAL_UART_WriteByte_NoBlocking(uint8 _Data);
STD_RETURN_t MCAL_UART_ReadByte_NoBlocking(uint8 *_Data);
#endif	/* USART_INTERFACE_H */

