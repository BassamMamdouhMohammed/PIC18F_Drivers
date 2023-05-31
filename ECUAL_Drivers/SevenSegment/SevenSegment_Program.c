/* 
 * File:   SevenSegment_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 13, 2022, 1:50 PM
 */
#include "SevenSegment_Interface.h"

STD_RETURN_t ECUAL_7SEGMENT_Initialize(const SevenSegment_t *_7Seg){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _7Seg){
        Return_Status = STD_NOT_OK;
    }
    else{
        Return_Status  = MCAL_GPIO_Pin_Initialize(&(_7Seg->SevenSeg_PINs[Segment_PIN0]));
        Return_Status &= MCAL_GPIO_Pin_Initialize(&(_7Seg->SevenSeg_PINs[Segment_PIN1]));
        Return_Status &= MCAL_GPIO_Pin_Initialize(&(_7Seg->SevenSeg_PINs[Segment_PIN2]));
        Return_Status &= MCAL_GPIO_Pin_Initialize(&(_7Seg->SevenSeg_PINs[Segment_PIN3]));
    }
    return Return_Status;
}
STD_RETURN_t ECUAL_7SEGMENT_Write(const SevenSegment_t *_7Seg, uint8 Number){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == _7Seg) || (Number > 9)){
        Return_Status = STD_NOT_OK;
    }
    else{
        Return_Status  = MCAL_GPIO_Pin_Write_Logic(&(_7Seg->SevenSeg_PINs[Segment_PIN0]),Number & 0x01);
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_7Seg->SevenSeg_PINs[Segment_PIN1]),(Number>>1) & 0x01);
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_7Seg->SevenSeg_PINs[Segment_PIN2]),(Number>>2) & 0x01);
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_7Seg->SevenSeg_PINs[Segment_PIN3]),(Number>>3) & 0x01);
    }
    return Return_Status;
}
