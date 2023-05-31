/* 
 * File:   Keypad_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on October 2, 2022, 2:32 PM
 */

#ifndef KEYPAD_INTERFACE_H
#define	KEYPAD_INTERFACE_H

/********************************* Includes *********************************/
#include "../../MCAL_peripheral/GPIO/GPIO_Interface.h"
/********************************* Macro Definitions ************************/
#define _KEYPAD_ROWS    4
#define _KEYPAD_COLUMNS 4
/********************************* Macro Functions  *************************/

/********************************* User-Defined Data Types ******************/
typedef struct{
    PIN_t Rows_Pin[_KEYPAD_ROWS];
    PIN_t Columns_Pin[_KEYPAD_COLUMNS];
}KEYPAD_t;
/********************************* Functions Declaration ********************/
STD_RETURN_t ECUAL_KEYPAD_Initialize(const KEYPAD_t *_Keypad);
STD_RETURN_t ECUAL_KEYPAD_Read_Value(const KEYPAD_t *_Keypad, uint8 *_Value);
#endif	/* KEYPAD_INTERFACE_H */

