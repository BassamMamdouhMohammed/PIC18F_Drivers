/* 
 * File:   Keypad_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on October 2, 2022, 2:32 PM
 */
#include "Keypad_Interface.h"

static const uint8 btn_values[_KEYPAD_ROWS][_KEYPAD_COLUMNS] = {
                                                                        {'7', '8', '9', '/'},
                                                                        {'4', '5', '6', '*'},
                                                                        {'1', '2', '3', '-'},
                                                                        {'#', '0', '=', '+'}
                                                                     };

STD_RETURN_t ECUAL_KEYPAD_Initialize(const KEYPAD_t *_Keypad){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 Row_Index = ZERO_Init;
    uint8 Column_Index = ZERO_Init;
    
    if(NULL == _Keypad){
        Return_Status = STD_NOT_OK;
    }
    else{
        for(Row_Index=0; Row_Index < _KEYPAD_ROWS; Row_Index++){
            Return_Status &= MCAL_GPIO_Pin_Initialize(&(_Keypad->Rows_Pin[Row_Index]));
        }
        for(Column_Index=0; Column_Index < _KEYPAD_COLUMNS; Column_Index++){
            Return_Status &= MCAL_GPIO_Pin_Direction_Initialize(&(_Keypad->Columns_Pin[Column_Index]));
        }
    }
    return Return_Status;
}
STD_RETURN_t ECUAL_KEYPAD_Read_Value(const KEYPAD_t *_Keypad, uint8 *_Value){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 Row_Index = ZERO_Init;
    uint8 Column_Index = ZERO_Init;
    LOGIC_t column_logic = ZERO_Init;
    uint8 l_counter = ZERO_Init;
    
    if((NULL == _Keypad) || (NULL == _Value)){
        Return_Status = STD_NOT_OK;
    }
    else{
        for(Row_Index=ZERO_Init; Row_Index<_KEYPAD_ROWS; Row_Index++){
            for(l_counter=ZERO_Init; l_counter<_KEYPAD_ROWS; l_counter++){
                Return_Status = MCAL_GPIO_Pin_Write_Logic(&(_Keypad->Rows_Pin[l_counter]), GPIO_LOW);
            }
            
            Return_Status = MCAL_GPIO_Pin_Write_Logic(&(_Keypad->Rows_Pin[Row_Index]), GPIO_HIGH);
            __delay_ms(10);
            
            for(Column_Index=ZERO_Init; Column_Index<_KEYPAD_COLUMNS; Column_Index++){
                Return_Status = MCAL_GPIO_Pin_Read_Logic(&(_Keypad->Columns_Pin[Column_Index]), &column_logic);
                if(GPIO_HIGH == column_logic){
                    *_Value = btn_values[Row_Index][Column_Index];
                }
            }
        }
    }
    return Return_Status;
}