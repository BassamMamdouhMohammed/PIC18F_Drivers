/* 
 * File:   Relay_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 12, 2022, 1:54 PM
 */

#ifndef RELAY_INTERFACE_H
#define	RELAY_INTERFACE_H

/********************************* Includes *********************************/
#include "../../MCAL_peripheral/GPIO/GPIO_Interface.h"
/********************************* Macro Definitions *********************************/
#define RELAY_ON  0x01U
#define RELAY_OFF 0x00U
/********************************* Macro Functions  *********************************/

/********************************* User-Defined Data Types *********************************/
typedef struct{
    uint8 Pin :3;
    uint8 Port :3;
    uint8 Status :1;
    uint8 Reserved :1;
}RELAY_t;
/********************************* Functions Declaration *********************************/

/**
 * @briaf This function is used to initialize the Relay 
 * @param _Relay is a pointer to structure to access configuration members @Look RELAY_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_RELAY_Initialize(const RELAY_t *_Relay);
/**
 * @briaf This function is used to Turn on the Relay 
 * @param _Relay is a pointer to structure to access configuration members @Look RELAY_t
 * @precondition you must initialize the relay first using -> ECUAL_RELAY_Initialize
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_RELAY_Turn_On(const RELAY_t *_Relay);
/**
 * @briaf This function is used to Turn off the Relay 
 * @param _Relay is a pointer to structure to access configuration members @Look RELAY_t
 * @precondition you must initialize the relay first using -> ECUAL_RELAY_Initialize
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_RELAY_Turn_Off(const RELAY_t *_Relay);

#endif	/* RELAY_INTERFACE_H */

