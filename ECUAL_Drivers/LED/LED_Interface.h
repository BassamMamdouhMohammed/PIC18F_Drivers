/* 
 * File:   LED_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh 
 * Created on September 8, 2022, 2:07 PM
 */

#ifndef LED_INTERFACE_H
#define	LED_INTERFACE_H

/********************************* Preprocessor Includes *********************************/
#include "../../MCAL_peripheral/GPIO/GPIO_Interface.h"
/********************************* Macro Definitions *********************************/

/********************************* Macro Functions  *********************************/

/********************************* User-Defined Data Types *********************************/

/********** @LED_t is a Structure of Led Configuration members   ************/

typedef struct{
    PORT_t Port  ;
    GPIO_PIN_t Pin  ;
    LOGIC_t Logic ;
    DIRECTION_t DIRECTION ;
}LED_t;

/********************************* Functions Declaration *********************************/

/**
 * @brief This function is used to initialize the led pin  
 * @param _LED is a pointer to led structure in order to access configuration members @Look at LED_t 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_LED_Initialize(const LED_t *_LED);
/**
 * @brief This function is used to Turn on the LED
 * @precondition you must first initialize the pin using @ECUAL_LED_Initialize()  
 * @param _LED is a pointer to led structure in order to access configuration members @Look at LED_t 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_LED_Turn_On(const LED_t *_LED);
/**
 * @brief This function is used to Turn off the LED
 * @precondition you must first initialize the pin using @ECUAL_LED_Initialize()  
 * @param _LED is a pointer to led structure in order to access configuration members @Look at LED_t 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_LED_Turn_Off(const LED_t *_LED);
/**
 * @brief This function is used to Toggle the LED 
 * @precondition you must first initialize the pin using @ECUAL_LED_Initialize()  
 * @param _LED is a pointer to led structure in order to access configuration members @Look at LED_t 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_LED_Toggle(const LED_t *_LED);

#endif	/* LED_INTERFACE_H */

