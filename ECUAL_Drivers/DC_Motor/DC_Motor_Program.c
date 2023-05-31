/* 
 * File:   DC_Motor_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on October 2, 2022, 11:11 AM
 */
#include "DC_Motor_Interface.h"

/**
 * 
 * @param _motor
 * @return 
 */
STD_RETURN_t ECUAL_DcMotor_Initialize(const DC_MOTOR_t *_motor){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _motor){
        Return_Status = STD_NOT_OK;
    }
    else{
        Return_Status &= MCAL_GPIO_Pin_Initialize(&(_motor->Motor_Pin[DC_MOTOR_PIN1]));
        Return_Status &= MCAL_GPIO_Pin_Initialize(&(_motor->Motor_Pin[DC_MOTOR_PIN2]));
    }
    return Return_Status;
}
/**
 * 
 * @param _motor
 * @return 
 */
STD_RETURN_t ECUAL_DcMotor_Move_Right(const DC_MOTOR_t *_motor){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _motor){
        Return_Status = STD_NOT_OK;
    }
    else{
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_motor->Motor_Pin[DC_MOTOR_PIN1]),GPIO_HIGH);
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_motor->Motor_Pin[DC_MOTOR_PIN2]),GPIO_LOW);
    }
    return Return_Status;
}
/**
 * 
 * @param _motor
 * @return 
 */
STD_RETURN_t ECUAL_DcMotor_Move_Left(const DC_MOTOR_t *_motor){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _motor){
        Return_Status = STD_NOT_OK;
    }
    else{
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_motor->Motor_Pin[DC_MOTOR_PIN1]),GPIO_LOW);
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_motor->Motor_Pin[DC_MOTOR_PIN2]),GPIO_HIGH);
    }
    return Return_Status;
}
/**
 * 
 * @param _motor
 * @return 
 */
STD_RETURN_t ECUAL_DcMotor_Stop(const DC_MOTOR_t *_motor){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _motor){
        Return_Status = STD_NOT_OK;
    }
    else{
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_motor->Motor_Pin[DC_MOTOR_PIN1]),GPIO_LOW);
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_motor->Motor_Pin[DC_MOTOR_PIN2]),GPIO_LOW);
    }
    return Return_Status;
}