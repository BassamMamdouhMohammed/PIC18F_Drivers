/* 
 * File:   GPIO_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on 03 Sep, 2022, 05:03 PM
 */

#ifndef GPIO_INTERFACE_H
#define	GPIO_INTERFACE_H

/********************************* Preprocessor Includes *********************************/
#include "../pic18f4620.h"
#include "../STD_Types.h"
#include "../PIC18F_Configuration.h"
#include "GPIO_BIT_MATH.h"
#include "../pic18.h"
/********************************* Macro Definitions *********************************/

#define ENABLE_CONFIG           0x01         /* macro to Enable any selected function  */
#define DISABLE_CONFIG          0x00         /* macro to Disable any selected function */
#define PIN_CONFIG_Enable   ENABLE_CONFIG    /* macro to Enable any Pin functions      */
#define PORT_CONFIG_Enable  ENABLE_CONFIG    /* macro to Enable any Port functions     */
#define PORT_PIN_MAX_NUMBER       8          /* macro to Max number of MCU Pins        */
#define PORT_MAX_NUMBER           5          /* macro to Max number of MCU Ports       */

/********************************* Macro Functions  *********************************/

/********************************* User-Defined Data Types *************************/

/********** @GPIO_PIN_t is a enumerator of all Pins for a specific selected port ********/
typedef enum{
    GPIO_pin0,
    GPIO_pin1, 
    GPIO_pin2,
    GPIO_pin3,
    GPIO_pin4,
    GPIO_pin5, 
    GPIO_pin6,
    GPIO_pin7,        
}GPIO_PIN_t;
/************************ @PORT_t is a enumerator of all Ports   ************************/
typedef enum{
    GPIO_portA,
    GPIO_portB,
    GPIO_portC,
    GPIO_portD,
    GPIO_portE,        
}PORT_t;
/********** @DIRECTION_t is a enumerator of Pin Direction either Input or Output   ************/
typedef enum{
    GPIO_OUTPUT,
    GPIO_INPUT
}DIRECTION_t;
/********** @LOGIC_t is a enumerator of Pin Logic either High or Low   ************/
typedef enum{
    GPIO_HIGH,
    GPIO_LOW
}LOGIC_t;
/********** @PIN_t is a Structure of Pin Configuration members   ************/
typedef struct{
    PORT_t PORT ;
    GPIO_PIN_t PIN ;
    DIRECTION_t DIRECTION ;
    LOGIC_t LOGIC ;
}PIN_t;
/********************************* Functions Declaration *********************************/

#if PIN_CONFIG_Enable==ENABLE_CONFIG
/**
 * @brief this Function Initialize a particular pin in any selected port
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Direction_Initialize(const PIN_t *_PIN);
/**
 * @brief this Function Read Direction of any pin whether it's output or input
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @param DirectionStatus is a pointer to get the direction reading result
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Get_Direction_Status(const PIN_t *_PIN, DIRECTION_t *DirectionStatus);
/**
 * @brief this Function is used to do both Initializing and reading any pin
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Initialize(const PIN_t *_PIN);
/**
 * @brief this Function is used to Write desired Logic (High or Low) on any pin 
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @param Logic is our desired logic (High or Low) @Look LOGIC_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Write_Logic(const PIN_t *_PIN, LOGIC_t Logic);
/**
 * @brief this Function is used to Read  Logic (High or Low) from any pin 
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @param Logic is a pointer to get pin's logic @Look LOGIC_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Read_Logic(const PIN_t *_PIN, LOGIC_t *Logic);
/**
 * @brief this Function is used to Toggle the Logic of a pin 
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Toggle_Logic(const PIN_t *_PIN);
#endif

#if PORT_CONFIG_Enable==ENABLE_CONFIG
/**
 * @brief this Function is used to Initialize the Direction of a whole port 
 * @param _PORT is a variable of type PORT_t refer to a particular PORT @Look PORT_t
 * @param Direction is our desired direction and is either output or input 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Port_Direction_Initialize(PORT_t _PORT, uint8 Direction);
/**
 * @brief this Function is used to Initialize the Direction of a whole port
 * @param _PORT is a variable of type PORT_t refer to a particular PORT @Look PORT_t
 * @param DirectionStatus is a pointer to get the status ( output or input ) of your selected port
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Port_Get_Direction_Status(PORT_t _PORT, uint8 *DirectionStatus);
/**
 * @brief this Function is used to write a logic to the whole port
 * @param _PORT is a variable of type PORT_t refer to a particular PORT @Look PORT_t
 * @param Logic is a variable to write the logic ( high or low ) @Look LOGIC_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Port_Write_Logic(PORT_t _PORT, LOGIC_t Logic);
/**
 * @brief this Function is used to Read the logic of the whole port
 * @param _PORT is a variable of type PORT_t refer to a particular PORT @Look PORT_t
 * @param Logic is a pointer to read Logic ( high or low) of a selected port 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Port_Read_Logic(PORT_t _PORT, LOGIC_t *Logic);
/**
 * @brief this Function is used to Toggle the logic of the whole port
 * @param _PORT is a variable of type PORT_t  refer to a particular PORT @Look PORT_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Port_Toggle_Logic(PORT_t _PORT);
#endif

#endif	/* GPIO_INTERFACE_H */

