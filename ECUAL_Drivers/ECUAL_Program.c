/* 
 * File:   ECUAL_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 8, 2022, 2:48 PM
 */

#include "ECUAL_Interface.h"

//LCD_8BIT_t _LCD1 = {.Data[0].PIN = GPIO_pin0, .Data[0].PORT = GPIO_portD, 
//                    .Data[0].LOGIC = GPIO_LOW, .Data[0].DIRECTION = GPIO_OUTPUT,
//                    .Data[1].PIN = GPIO_pin1, .Data[1].PORT = GPIO_portD, 
//                    .Data[1].LOGIC = GPIO_LOW, .Data[1].DIRECTION = GPIO_OUTPUT,
//                    .Data[2].PIN = GPIO_pin2, .Data[2].PORT = GPIO_portD, 
//                    .Data[2].LOGIC = GPIO_LOW, .Data[2].DIRECTION = GPIO_OUTPUT,
//                    .Data[3].PIN = GPIO_pin3, .Data[3].PORT = GPIO_portD, 
//                    .Data[3].LOGIC = GPIO_LOW, .Data[3].DIRECTION = GPIO_OUTPUT,
//                    .Data[4].PIN = GPIO_pin4, .Data[4].PORT = GPIO_portD, 
//                    .Data[4].LOGIC = GPIO_LOW, .Data[4].DIRECTION = GPIO_OUTPUT,
//                    .Data[5].PIN = GPIO_pin5, .Data[5].PORT = GPIO_portD, 
//                    .Data[5].LOGIC = GPIO_LOW, .Data[5].DIRECTION = GPIO_OUTPUT,
//                    .Data[6].PIN = GPIO_pin6, .Data[6].PORT = GPIO_portD, 
//                    .Data[6].LOGIC = GPIO_LOW, .Data[6].DIRECTION = GPIO_OUTPUT,
//                    .Data[7].PIN = GPIO_pin7, .Data[7].PORT = GPIO_portD, 
//                    .Data[7].LOGIC = GPIO_LOW, .Data[7].DIRECTION = GPIO_OUTPUT,
//                    .EN_Pin.PORT = GPIO_portC, .EN_Pin.PIN = GPIO_pin7, 
//                    .EN_Pin.LOGIC = GPIO_LOW, .EN_Pin.DIRECTION = GPIO_OUTPUT,
//                    .RS_Pin.PORT = GPIO_portC, .RS_Pin.PIN = GPIO_pin6, 
//                    .RS_Pin.LOGIC = GPIO_LOW, .RS_Pin.DIRECTION = GPIO_OUTPUT};
//
//LCD_4BIT_t _LCD2 = {.Data[0].PIN = GPIO_pin2, .Data[0].PORT = GPIO_portC, 
//                    .Data[0].LOGIC = GPIO_LOW, .Data[0].DIRECTION = GPIO_OUTPUT,
//                    .Data[1].PIN = GPIO_pin3, .Data[1].PORT = GPIO_portC, 
//                    .Data[1].LOGIC = GPIO_LOW, .Data[1].DIRECTION = GPIO_OUTPUT,
//                    .Data[2].PIN = GPIO_pin4, .Data[2].PORT = GPIO_portC, 
//                    .Data[2].LOGIC = GPIO_LOW, .Data[2].DIRECTION = GPIO_OUTPUT,
//                    .Data[3].PIN = GPIO_pin5, .Data[3].PORT = GPIO_portC, 
//                    .Data[3].LOGIC = GPIO_LOW, .Data[3].DIRECTION = GPIO_OUTPUT,
//                    .EN_Pin.PORT = GPIO_portC, .EN_Pin.PIN = GPIO_pin1, 
//                    .EN_Pin.LOGIC = GPIO_LOW, .EN_Pin.DIRECTION = GPIO_OUTPUT,
//                    .RS_Pin.PORT = GPIO_portC, .RS_Pin.PIN = GPIO_pin0, 
//                    .RS_Pin.LOGIC = GPIO_LOW, .RS_Pin.DIRECTION = GPIO_OUTPUT};

//KEYPAD_t _Keypad1 = {.Rows_Pin[0].PORT = GPIO_portC, .Rows_Pin[0].PIN = GPIO_pin0,
//                     .Rows_Pin[0].LOGIC = GPIO_LOW, .Rows_Pin[0].DIRECTION = GPIO_OUTPUT,
//                     .Rows_Pin[1].PORT = GPIO_portC, .Rows_Pin[1].PIN = GPIO_pin1,
//                     .Rows_Pin[1].LOGIC = GPIO_LOW, .Rows_Pin[1].DIRECTION = GPIO_OUTPUT,
//                     .Rows_Pin[2].PORT = GPIO_portC, .Rows_Pin[2].PIN = GPIO_pin2,
//                     .Rows_Pin[2].LOGIC = GPIO_LOW, .Rows_Pin[2].DIRECTION = GPIO_OUTPUT,
//                     .Rows_Pin[3].PORT = GPIO_portC, .Rows_Pin[3].PIN = GPIO_pin3,
//                     .Rows_Pin[3].LOGIC = GPIO_LOW, .Rows_Pin[3].DIRECTION = GPIO_OUTPUT,
//                     .Columns_Pin[0].PORT = GPIO_portC, .Columns_Pin[0].PIN = GPIO_pin4,
//                     .Columns_Pin[0].LOGIC = GPIO_LOW, .Columns_Pin[0].DIRECTION = GPIO_INPUT,
//                     .Columns_Pin[1].PORT = GPIO_portC, .Columns_Pin[1].PIN = GPIO_pin5,
//                     .Columns_Pin[1].LOGIC = GPIO_LOW, .Columns_Pin[1].DIRECTION = GPIO_INPUT,
//                     .Columns_Pin[2].PORT = GPIO_portC, .Columns_Pin[2].PIN = GPIO_pin6,
//                     .Columns_Pin[2].LOGIC = GPIO_LOW, .Columns_Pin[2].DIRECTION = GPIO_INPUT,
//                     .Columns_Pin[3].PORT = GPIO_portC, .Columns_Pin[3].PIN = GPIO_pin7,
//                     .Columns_Pin[3].LOGIC = GPIO_LOW, .Columns_Pin[3].DIRECTION = GPIO_INPUT,};


void ECUAL_Initialize(void){
    
}