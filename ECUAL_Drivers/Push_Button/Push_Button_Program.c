/* 
 * File:   Push_Button_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 10, 2022, 2:00 PM
 */

#include "Push_Button_Interface.h"

/**
 * @brief This function is used to initialize the button
 * @param _BUTTON is a pointer to structure to make the configurations @Look at PUSH_BUTTON_t  
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_pushButton_Initialize(const PUSH_BUTTON_t *_BUTTON){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _BUTTON){
        Return_Status = STD_NOT_OK;
    }
    else{
        Return_Status = MCAL_GPIO_Pin_Direction_Initialize(&(_BUTTON->PushButton_Pin));
    }
    return Return_Status;
}
/**
 * @brief This function is used to Read the button state either it pressed or released
 * @param _BUTTON is a pointer to structure to make the configurations @Look at PUSH_BUTTON_t
 * @param State is a pointer to structure to store button state @Look at PushButton_State
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t ECUAL_pushButton_Read_State(const PUSH_BUTTON_t *_BUTTON,PushButton_State *State){
    STD_RETURN_t Return_Status = STD_OK;
    LOGIC_t Button_Logic = GPIO_LOW; 
    if((NULL == _BUTTON) || (NULL == State)){
        Return_Status = STD_NOT_OK;
    }
    else{
        Return_Status = MCAL_GPIO_Pin_Read_Logic(&(_BUTTON->PushButton_Pin),&Button_Logic);
        if(Active_High == _BUTTON->Connection){
            if(GPIO_HIGH == Button_Logic){
                *State = Pressed;
            }
            else{
                *State = Released;
        }
    }
        else if(Active_Low == _BUTTON->Connection){
            if(GPIO_HIGH == Button_Logic){
                *State = Released;
            }
            else{
                *State = Pressed;
            }
        }
        else{}
    }
    return Return_Status;
}
