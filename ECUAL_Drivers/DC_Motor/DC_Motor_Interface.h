/* 
 * File:   DC_Motor_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on October 2, 2022, 11:11 AM
 */

#ifndef DC_MOTOR_INTERFACE_H
#define	DC_MOTOR_INTERFACE_H

/********************************* Includes *********************************/
#include "../../MCAL_peripheral/GPIO/GPIO_Interface.h"
/********************************* Macro Definitions ************************/
#define DC_MOTOR_PIN1       0x00U
#define DC_MOTOR_PIN2       0x01U
#define DC_MOTOR_ON_STATUS  0x00U
#define DC_MOTOR_OFF_STATUS 0x01U
/********************************* Macro Functions  *************************/

/********************************* User-Defined Data Types ******************/
typedef struct{
    PIN_t Motor_Pin[2];
}DC_MOTOR_t;
/********************************* Functions Declaration ********************/
STD_RETURN_t ECUAL_DcMotor_Initialize(const DC_MOTOR_t *_motor);
STD_RETURN_t ECUAL_DcMotor_Move_Right(const DC_MOTOR_t *_motor);
STD_RETURN_t ECUAL_DcMotor_Move_Left(const DC_MOTOR_t *_motor);
STD_RETURN_t ECUAL_DcMotor_Stop(const DC_MOTOR_t *_motor);
#endif	/* DC_MOTOR_INTERFACE_H */

