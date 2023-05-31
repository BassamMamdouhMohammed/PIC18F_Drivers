/* 
 * File:   STD_Types.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on 03 Sep, 2022, 05:11 ?
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H
/********************************* Includes *********************************/
#include "STD_Library.h"
/********************************* Macro Definitions *********************************/
#define ZERO_Init        0x00

#define STD_OK     (STD_RETURN_t)0x01
#define STD_NOT_OK (STD_RETURN_t)0x00

/********************************* Macro Functions  *********************************/

/********************************* User-Defined Data Types *********************************/
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned char  uint8;

typedef signed short   sint16;
typedef signed int     sint32;
typedef signed char    sint8;

typedef uint8 STD_RETURN_t;

/********************************* Functions Declaration *********************************/

#endif	/* STD_TYPES_H */

