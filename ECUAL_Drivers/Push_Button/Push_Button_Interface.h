/* 
 * File:   Push_Button_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 10, 2022, 2:00 PM
 */

#ifndef PUSH_BUTTON_INTERFACE_H
#define	PUSH_BUTTON_INTERFACE_H

/********************************* Includes *********************************/
#include "../../MCAL_peripheral/GPIO/GPIO_Interface.h"
/********************************* Macro Definitions *********************************/

/********************************* Macro Functions  *********************************/

/********************************* User-Defined Data Types *********************************/

typedef enum{
    Pressed = 0,                /* Detects wither Button is Pressed or not  */
    Released                    /* Detects wither Button is Released or not */
}PushButton_State;              /* @PushButton_State is a enumerator of Button two states  */

typedef enum{
    Active_High = 0,            /* Button should connect to 5v --> Logic 1 */
    Active_Low                  /* Button should connect to 0v --> Logic 0 */
}PushButton_Connection;         /* @PushButton_Connection is a enumerator of Button two Connections */

typedef struct{
    PIN_t PushButton_Pin;       /* @PIN_t is a Structure of Pin Configuration members */
    PushButton_State State;
    PushButton_Connection Connection;
}PUSH_BUTTON_t;                 /* @PUSH_BUTTON_t is a Structure of Button Configuration members */

/********************************* Functions Declaration *********************************/

/**
 * @brief This function is used to initialize the button
 * @param _BUTTON is a pointer to structure to make the configurations @Look at PUSH_BUTTON_t  
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_pushButton_Initialize(const PUSH_BUTTON_t *_BUTTON);
/**
 * @brief This function is used to Read the button state either it pressed or released
 * @param _BUTTON is a pointer to structure to make the configurations @Look at PUSH_BUTTON_t
 * @param State is a pointer to structure to store button state @Look at PushButton_State
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_pushButton_Read_State(const PUSH_BUTTON_t *_BUTTON,PushButton_State *State);

#endif	/* PUSH_BUTTON_INTERFACE_H */

