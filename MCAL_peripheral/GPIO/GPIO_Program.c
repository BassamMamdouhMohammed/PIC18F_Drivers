/* 
 * File:   GPIO_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on 03 Sep, 2022, 05:03 AM
 */

#include "GPIO_Interface.h"

/* Array of Pointers to Access Register (TRIS) responsible for output or input Pin Direction */
volatile STD_RETURN_t *TRIS_Register[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/* Array of Pointers to Access Register (LAT) responsible for Write High or Low Logic */
volatile STD_RETURN_t *LAT_Register[]  = {&LATA,&LATB,&LATC,&LATD,&LATE};
/* Array of Pointers to Access Register (PORT) responsible for Get Port Status */
volatile STD_RETURN_t *PORT_Register[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

#if PIN_CONFIG_Enable==ENABLE_CONFIG

/**
 * @brief this Function Initialize a particular pin in any selected port
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Direction_Initialize(const PIN_t *_PIN){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == _PIN) || (_PIN->PIN > PORT_PIN_MAX_NUMBER-1)){
        Return_Status = STD_NOT_OK;
    }
    else{
        switch(_PIN->DIRECTION){
            case GPIO_OUTPUT :
                Clear_BIT(*TRIS_Register[_PIN->PORT],_PIN->PIN);
                break;
            case GPIO_INPUT :
                Set_BIT(*TRIS_Register[_PIN->PORT],_PIN->PIN);
                break;
            default: Return_Status = STD_NOT_OK;
        }
    }
    return Return_Status;
}
/**
 * @brief this Function Read Direction of any pin whether it's output or input
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @param DirectionStatus is a pointer to get the direction reading result
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Get_Direction_Status(const PIN_t *_PIN, DIRECTION_t *DirectionStatus){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == _PIN) || (NULL == DirectionStatus) || (_PIN->PIN > PORT_PIN_MAX_NUMBER-1)){
        Return_Status = STD_NOT_OK;
    }
    else{
        *DirectionStatus = Read_BIT(*TRIS_Register[_PIN->PORT],_PIN->PIN);
    }   
    return Return_Status;
}
/**
 * @brief this Function is used to do both Initializing and reading any pin
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Initialize(const PIN_t *_PIN){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == _PIN) || (_PIN->PIN > PORT_PIN_MAX_NUMBER-1)){
        Return_Status = STD_NOT_OK;
    }
    else{
        Return_Status  = MCAL_GPIO_Pin_Direction_Initialize(_PIN);
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(_PIN,_PIN->LOGIC);
    }
    return Return_Status;    
}
/**
 * @brief this Function is used to Write desired Logic (High or Low) on any pin 
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @param Logic is our desired logic (High or Low) @Look LOGIC_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Write_Logic(const PIN_t *_PIN, LOGIC_t Logic){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == _PIN) || (_PIN->PIN > PORT_PIN_MAX_NUMBER-1)){
        Return_Status = STD_NOT_OK;
    }
    else{
        switch(Logic){
            case GPIO_HIGH :
                Set_BIT(*LAT_Register[_PIN->PORT],_PIN->PIN);
                break;
            case GPIO_LOW :
                Clear_BIT(*LAT_Register[_PIN->PORT],_PIN->PIN);
                break;
            default :
                Return_Status = STD_NOT_OK;
        }
    }
    return Return_Status;
} 
/**
 * @brief this Function is used to Read  Logic (High or Low) from any pin 
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @param Logic is a pointer to get pin's logic @Look LOGIC_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Read_Logic(const PIN_t *_PIN, LOGIC_t *Logic){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == _PIN) || (_PIN->PIN > PORT_PIN_MAX_NUMBER-1) || (NULL == Logic)){
        Return_Status = STD_NOT_OK;
    }
    else{
        *Logic = Read_BIT(*PORT_Register[_PIN->PORT],_PIN->PIN);
    }
    return Return_Status;    
}
/**
 * @brief this Function is used to Toggle the Logic of a pin 
 * @param _PIN is a pointer to a structure to access pin specification @look PIN_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Pin_Toggle_Logic(const PIN_t *_PIN){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == _PIN) || (_PIN->PIN > PORT_PIN_MAX_NUMBER-1)){
        Return_Status = STD_NOT_OK;
    }
    else{
        Toggle_BIT(*LAT_Register[_PIN->PORT],_PIN->PIN);
    }
    return Return_Status;    
}

#endif

#if PORT_CONFIG_Enable==ENABLE_CONFIG

/**
 * @brief this Function is used to Initialize the Direction of a whole port 
 * @param _PORT is a variable of type PORT_t refer to a particular PORT @Look PORT_t
 * @param Direction is our desired direction and is either output or input 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Port_Direction_Initialize(PORT_t _PORT, uint8 Direction){
   STD_RETURN_t Return_Status = STD_OK;
    if(_PORT > PORT_MAX_NUMBER-1){
        Return_Status = STD_NOT_OK;
    }
    else{
        *TRIS_Register[_PORT] = Direction;
    }
    return Return_Status; 
}
/**
 * @brief this Function is used to Initialize the Direction of a whole port
 * @param _PORT is a variable of type PORT_t refer to a particular PORT @Look PORT_t
 * @param DirectionStatus is a pointer to get the status ( output or input ) of your selected port
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Port_Get_Direction_Status(PORT_t _PORT, uint8 *DirectionStatus){
    STD_RETURN_t Return_Status = STD_OK;
    if((_PORT > PORT_MAX_NUMBER-1) || (NULL == DirectionStatus)){
        Return_Status = STD_NOT_OK;
    }
    else{
        *DirectionStatus = *TRIS_Register[_PORT];
    }
    return Return_Status;
}
/**
 * @brief this Function is used to write a logic to the whole port
 * @param _PORT is a variable of type PORT_t refer to a particular PORT @Look PORT_t
 * @param Logic is a variable to write the logic ( high or low ) @Look LOGIC_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Port_Write_Logic(PORT_t _PORT, LOGIC_t Logic){
    STD_RETURN_t Return_Status = STD_OK;
    if(_PORT > PORT_MAX_NUMBER-1){
        Return_Status = STD_NOT_OK;
    }
    else{
        *LAT_Register[_PORT] = Logic;
    }
    return Return_Status;
}
/**
 * @brief this Function is used to Read the logic of the whole port
 * @param _PORT is a variable of type PORT_t refer to a particular PORT @Look PORT_t
 * @param Logic is a pointer to read Logic ( high or low) of a selected port 
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Port_Read_Logic(PORT_t _PORT, LOGIC_t *Logic){
    STD_RETURN_t Return_Status = STD_OK;
    if((_PORT > PORT_MAX_NUMBER-1) || (NULL == Logic)){
        Return_Status = STD_NOT_OK;
    }
    else{
        *Logic = *LAT_Register[_PORT];
    }
    return Return_Status;
}
/**
 * @brief this Function is used to Toggle the logic of the whole port
 * @param _PORT is a variable of type PORT_t  refer to a particular PORT @Look PORT_t
 * @return STD_OK : refers to that this function do its functionality perfectly
 *         STD_NOT_OK : refers to an ERROR occurred during the running
 */
STD_RETURN_t MCAL_GPIO_Port_Toggle_Logic(PORT_t _PORT){
    STD_RETURN_t Return_Status = STD_OK;
    if(_PORT > PORT_MAX_NUMBER-1){
        Return_Status = STD_NOT_OK;
    }
    else{
        *LAT_Register[_PORT] ^= PORT_MASK;
    }
    return Return_Status;
}

#endif