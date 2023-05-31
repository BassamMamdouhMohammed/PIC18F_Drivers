/* 
 * File:   Relay_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 12, 2022, 1:54 PM
 */
#include "Relay_Interface.h"

/**
 * @briaf This function is used to initialize the Relay 
 * @param _Relay is a pointer to structure to access configuration members @Look RELAY_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_RELAY_Initialize(const RELAY_t *_Relay){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _Relay){
        Return_Status = STD_NOT_OK;
    }
    else{
        PIN_t Relay_Obj = { .PORT = _Relay->Port, .PIN = _Relay->Pin, 
                            .DIRECTION = GPIO_OUTPUT, .LOGIC = _Relay->Status};
        Return_Status = MCAL_GPIO_Pin_Initialize(&Relay_Obj);
    }
    return Return_Status;
}
/**
 * @briaf This function is used to Turn on the Relay 
 * @param _Relay is a pointer to structure to access configuration members @Look RELAY_t
 * @precondition you must initialize the relay first using -> ECUAL_RELAY_Initialize
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_RELAY_Turn_On(const RELAY_t *_Relay){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _Relay){
        Return_Status = STD_NOT_OK;
    }
    else{
        PIN_t Relay_Obj = { .PORT = _Relay->Port, .PIN = _Relay->Pin, 
                            .DIRECTION = GPIO_OUTPUT, .LOGIC = _Relay->Status};
        Return_Status = MCAL_GPIO_Pin_Write_Logic(&Relay_Obj, GPIO_HIGH);
    }
    return Return_Status;
}
/**
 * @briaf This function is used to Turn off the Relay 
 * @param _Relay is a pointer to structure to access configuration members @Look RELAY_t
 * @precondition you must initialize the relay first using -> ECUAL_RELAY_Initialize
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_RELAY_Turn_Off(const RELAY_t *_Relay){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _Relay){
        Return_Status = STD_NOT_OK;
    }
    else{
        PIN_t Relay_Obj = { .PORT = _Relay->Port, .PIN = _Relay->Pin, 
                            .DIRECTION = GPIO_OUTPUT, .LOGIC = _Relay->Status};
        Return_Status = MCAL_GPIO_Pin_Write_Logic(&Relay_Obj, GPIO_LOW);
    }
    return Return_Status;
}