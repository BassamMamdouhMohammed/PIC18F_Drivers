/* 
 * File:   SevenSegment_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 13, 2022, 1:50 PM
 */

#ifndef SEVENSEGMENT_INTERFACE_H
#define	SEVENSEGMENT_INTERFACE_H

/********************************* Includes *********************************/
#include "../../MCAL_peripheral/GPIO/GPIO_Interface.h"

/********************************* Macro Definitions *********************************/
#define Segment_PIN0 0
#define Segment_PIN1 1
#define Segment_PIN2 2
#define Segment_PIN3 3
/********************************* Macro Functions  *********************************/

/********************************* User-Defined Data Types **************************/
typedef enum{
    Common_Anode,
    Common_Cathod  
}COMMON_t;
typedef struct{
    PIN_t SevenSeg_PINs[4];
    COMMON_t Common;
}SevenSegment_t;
/********************************* Functions Declaration *********************************/
STD_RETURN_t ECUAL_7SEGMENT_Initialize(const SevenSegment_t *_7Seg);
STD_RETURN_t ECUAL_7SEGMENT_Write(const SevenSegment_t *_7Seg, uint8 Number);
#endif	/* SEVENSEGMENT_INTERFACE_H */

