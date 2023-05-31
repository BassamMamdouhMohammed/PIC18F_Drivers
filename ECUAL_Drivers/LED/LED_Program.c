/* 
 * File:   LED_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 8, 2022, 2:07 PM
 */

#include "LED_Interface.h"

/**
 * @brief This function is used to initialize the led pin  
 * @param _LED is a pointer to led structure in order to access configuration members @Look at LED_t 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_LED_Initialize(const LED_t *_LED){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _LED){
        Return_Status = STD_NOT_OK;
    }
    else{
        PIN_t _LED_Obj = {.PORT = _LED->Port, .PIN = _LED->Pin, 
                          .LOGIC = _LED->Logic,.DIRECTION = GPIO_OUTPUT};
        MCAL_GPIO_Pin_Initialize(&_LED_Obj);
    }
    return Return_Status;
}
/**
 * @brief This function is used to Turn on the LED
 * @precondition you must first initialize the pin using @ECUAL_LED_Initialize()  
 * @param _LED is a pointer to led structure in order to access configuration members @Look at LED_t 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_LED_Turn_On(const LED_t *_LED){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _LED){
        Return_Status = STD_NOT_OK;
    }
    else{
        PIN_t _LED_Obj = {.PORT = _LED->Port, .PIN = _LED->Pin, 
                          .LOGIC = _LED->Logic, .DIRECTION = GPIO_OUTPUT};
        MCAL_GPIO_Pin_Write_Logic(&_LED_Obj,GPIO_HIGH);
    }
    return Return_Status;
}
/**
 * @brief This function is used to Turn off the LED
 * @precondition you must first initialize the pin using @ECUAL_LED_Initialize()  
 * @param _LED is a pointer to led structure in order to access configuration members @Look at LED_t 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_LED_Turn_Off(const LED_t *_LED){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _LED){
        Return_Status = STD_NOT_OK;
    }
    else{
        PIN_t _LED_Obj = {.PORT = _LED->Port, .PIN = _LED->Pin, 
                          .LOGIC = _LED->Logic, .DIRECTION = GPIO_OUTPUT};
        MCAL_GPIO_Pin_Write_Logic(&_LED_Obj,GPIO_LOW);
    }
    return Return_Status;
}
/**
 * @brief This function is used to Toggle the LED 
 * @precondition you must first initialize the pin using @ECUAL_LED_Initialize()  
 * @param _LED is a pointer to led structure in order to access configuration members @Look at LED_t 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_LED_Toggle(const LED_t *_LED){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _LED){
        Return_Status = STD_NOT_OK;
    }
    else{
        PIN_t _LED_Obj = {.PORT = _LED->Port, .PIN = _LED->Pin, 
                          .LOGIC = _LED->Logic, .DIRECTION = GPIO_OUTPUT};
        MCAL_GPIO_Pin_Toggle_Logic(&_LED_Obj);
    }
    return Return_Status;
}