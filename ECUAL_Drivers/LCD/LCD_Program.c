/* 
 * File:   LCD_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 29, 2022, 4:28 PM
 */
#include "LCD_Interface.h"
static STD_RETURN_t LCD_Send_EN_Signal(const LCD_8BIT_t *_LCD);
static STD_RETURN_t LCD_8Bit_Set_Cursor(const LCD_8BIT_t *_LCD, uint8 _Row, uint8 _Column);
static STD_RETURN_t LCD_Send_4Bit_EN_Signal(const LCD_4BIT_t *_LCD);
static STD_RETURN_t LCD_Send_4Bits(const LCD_4BIT_t *_LCD, uint8 _Command);
static STD_RETURN_t LCD_4Bit_Set_Cursor(const LCD_4BIT_t *_LCD, uint8 _Row, uint8 _Column);

#if _LCD_8BIT_MODE_ENABLE==_LCD_MODE_ENABLE
STD_RETURN_t ECUAL_LCD_8BIT_Initialize(const LCD_8BIT_t *_LCD){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 Index_8Bit = ZERO_Init;
        if(NULL == _LCD){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status  = MCAL_GPIO_Pin_Initialize(&(_LCD->EN_Pin));
            Return_Status &= MCAL_GPIO_Pin_Initialize(&(_LCD->RS_Pin));
            for(Index_8Bit =0; Index_8Bit < 8; Index_8Bit++){
                Return_Status &= MCAL_GPIO_Pin_Initialize(&(_LCD->Data[Index_8Bit]));
            }
            __delay_ms(20);
            Return_Status &= ECUAL_LCD_8BIT_Write_Command(_LCD,_LCD_8BIT_BUS_MODE_2LINE);
            __delay_ms(5);
            Return_Status &= ECUAL_LCD_8BIT_Write_Command(_LCD,_LCD_8BIT_BUS_MODE_2LINE);
            __delay_ms(150);
            Return_Status &= ECUAL_LCD_8BIT_Write_Command(_LCD,_LCD_8BIT_BUS_MODE_2LINE);
            Return_Status &= ECUAL_LCD_8BIT_Write_Command(_LCD,_LCD_CLEAR_DISPLAY);
            Return_Status &= ECUAL_LCD_8BIT_Write_Command(_LCD,_LCD_CURSOR_HOME);
            Return_Status &= ECUAL_LCD_8BIT_Write_Command(_LCD,_LCD_INCREMENT_SHIFT_OFF);
            Return_Status &= ECUAL_LCD_8BIT_Write_Command(_LCD,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
            Return_Status &= ECUAL_LCD_8BIT_Write_Command(_LCD,_LCD_8BIT_BUS_MODE_2LINE);
            Return_Status &= ECUAL_LCD_8BIT_Write_Command(_LCD,_LCD_SET_ADDRESS_TO_DDRAM);
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_8BIT_Write_Command(const LCD_8BIT_t *_LCD,uint8 _Command){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 Index_8Bit = ZERO_Init;
        if(NULL == _LCD){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status = MCAL_GPIO_Pin_Write_Logic(&(_LCD->RS_Pin),GPIO_LOW);
            for(Index_8Bit =0; Index_8Bit < 8; Index_8Bit++){
                Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_LCD->Data[Index_8Bit]),((_Command >> Index_8Bit) & (uint8)0x01));
            }
            Return_Status &= LCD_Send_EN_Signal(_LCD);
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_8BIT_Write_Data(const LCD_8BIT_t *_LCD,uint8 _Data){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 Index_8Bit = ZERO_Init;
        if(NULL == _LCD){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status = MCAL_GPIO_Pin_Write_Logic(&(_LCD->RS_Pin),GPIO_HIGH);
            for(Index_8Bit =0; Index_8Bit < 8; Index_8Bit++){
                Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_LCD->Data[Index_8Bit]),((_Data >> Index_8Bit) & (uint8)0x01));
            }
            Return_Status &= LCD_Send_EN_Signal(_LCD);
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_8BIT_Write_Data_Position(const LCD_8BIT_t *_LCD,uint8 _Data,uint8 _Row, uint8 _Column){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _LCD){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status = LCD_8Bit_Set_Cursor(_LCD,_Row,_Column);
            Return_Status = ECUAL_LCD_8BIT_Write_Data(_LCD,_Data);
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_8BIT_Write_String(const LCD_8BIT_t *_LCD,uint8 *_Str){
    STD_RETURN_t Return_Status = STD_OK;
        if((NULL == _LCD) || (NULL == _Str)){
            Return_Status = STD_NOT_OK;
        }
        else{
            while(*_Str){
                Return_Status = ECUAL_LCD_8BIT_Write_Data(_LCD,*_Str++);
            }
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_8BIT_Write_String_Position(const LCD_8BIT_t *_LCD,uint8 *_Str,uint8 _Row, uint8 _Column){
    STD_RETURN_t Return_Status = STD_OK;
        if((NULL == _LCD) || (NULL == _Str)){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status  = LCD_8Bit_Set_Cursor(_LCD,_Row,_Column);
            Return_Status &= ECUAL_LCD_8BIT_Write_String(_LCD,_Str);
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_8BIT_Write_Custome_Char(const LCD_8BIT_t *_LCD,uint8 Row,uint8 Column,uint8 Mem_Pos,const uint8 _chr[]){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 Index_8Bit = ZERO_Init;
        if(NULL == _LCD){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status = ECUAL_LCD_8BIT_Write_Command(_LCD,(_LCD_SET_ADDRESS_TO_CGRAM+(Mem_Pos*8)));
            for(Index_8Bit =0; Index_8Bit < 8; Index_8Bit++){
                Return_Status &= ECUAL_LCD_8BIT_Write_Data(_LCD,_chr[Index_8Bit]);
            }
            Return_Status = ECUAL_LCD_8BIT_Write_Data_Position(_LCD,Mem_Pos,Row,Column);
        }
    return Return_Status;
}
static STD_RETURN_t LCD_Send_EN_Signal(const LCD_8BIT_t *_LCD){
    STD_RETURN_t Return_Status = STD_OK;
    MCAL_GPIO_Pin_Write_Logic(&(_LCD->EN_Pin),GPIO_HIGH);
    __delay_ms(5);
    MCAL_GPIO_Pin_Write_Logic(&(_LCD->EN_Pin),GPIO_LOW);
    return Return_Status;
}
static STD_RETURN_t LCD_8Bit_Set_Cursor(const LCD_8BIT_t *_LCD, uint8 _Row, uint8 _Column){
    STD_RETURN_t Return_Status = STD_OK;
    _Column--;
    switch(_Row){
        case ROW1 :
            Return_Status = ECUAL_LCD_8BIT_Write_Command(_LCD,(0x80 + _Column));
            break;
        case ROW2 :
            Return_Status = ECUAL_LCD_8BIT_Write_Command(_LCD,(0xC0 + _Column));
            break;
        case ROW3 :
            Return_Status = ECUAL_LCD_8BIT_Write_Command(_LCD,(0x94 + _Column));
            break;
        case ROW4 :
            Return_Status = ECUAL_LCD_8BIT_Write_Command(_LCD,(0xD4 + _Column));
            break;
        default: 
            Return_Status = STD_NOT_OK;
    }
    return Return_Status;
}
#endif
#if _LCD_4BIT_MODE_ENABLE==_LCD_MODE_ENABLE
STD_RETURN_t ECUAL_LCD_4BIT_Initialize(const LCD_4BIT_t *_LCD){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 Index_4Bit = ZERO_Init;
        if(NULL == _LCD){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status  = MCAL_GPIO_Pin_Initialize(&(_LCD->EN_Pin));
            Return_Status &= MCAL_GPIO_Pin_Initialize(&(_LCD->RS_Pin));
            for(Index_4Bit =0; Index_4Bit < 4; Index_4Bit++){
                Return_Status &= MCAL_GPIO_Pin_Initialize(&(_LCD->Data[Index_4Bit]));
            }
            __delay_ms(20);
            Return_Status &= ECUAL_LCD_4BIT_Write_Command(_LCD,_LCD_4BIT_BUS_MODE_2LINE);
            __delay_ms(5);
            Return_Status &= ECUAL_LCD_4BIT_Write_Command(_LCD,_LCD_4BIT_BUS_MODE_2LINE);
            __delay_ms(150);
            Return_Status &= ECUAL_LCD_4BIT_Write_Command(_LCD,_LCD_4BIT_BUS_MODE_2LINE);
            Return_Status &= ECUAL_LCD_4BIT_Write_Command(_LCD,_LCD_CLEAR_DISPLAY);
            Return_Status &= ECUAL_LCD_4BIT_Write_Command(_LCD,_LCD_CURSOR_HOME);
            Return_Status &= ECUAL_LCD_4BIT_Write_Command(_LCD,_LCD_INCREMENT_SHIFT_OFF);
            Return_Status &= ECUAL_LCD_4BIT_Write_Command(_LCD,_LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
            Return_Status &= ECUAL_LCD_4BIT_Write_Command(_LCD,_LCD_4BIT_BUS_MODE_2LINE);
            Return_Status &= ECUAL_LCD_4BIT_Write_Command(_LCD,_LCD_SET_ADDRESS_TO_DDRAM);
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_4BIT_Write_Command(const LCD_4BIT_t *_LCD,uint8 _Command){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _LCD){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status  = MCAL_GPIO_Pin_Write_Logic(&(_LCD->RS_Pin),GPIO_LOW);
            Return_Status &= LCD_Send_4Bits(_LCD,_Command >> 4);
            Return_Status &= LCD_Send_4Bit_EN_Signal(_LCD);   
            Return_Status &= LCD_Send_4Bits(_LCD,_Command);
            Return_Status &= LCD_Send_4Bit_EN_Signal(_LCD);
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_4BIT_Write_Data(const LCD_4BIT_t *_LCD,uint8 _Data){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _LCD){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_LCD->RS_Pin),GPIO_HIGH);
            Return_Status &= LCD_Send_4Bits(_LCD,_Data >> 4);
            Return_Status &= LCD_Send_4Bit_EN_Signal(_LCD);
            Return_Status &= LCD_Send_4Bits(_LCD,_Data);
            Return_Status &= LCD_Send_4Bit_EN_Signal(_LCD);
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_4BIT_Write_Data_Position(const LCD_4BIT_t *_LCD,uint8 _Data,uint8 _Row, uint8 _Column){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _LCD){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status = LCD_4Bit_Set_Cursor(_LCD,_Row,_Column);
            Return_Status = ECUAL_LCD_4BIT_Write_Data(_LCD,_Data);
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_4BIT_Write_String(const LCD_4BIT_t *_LCD,uint8 *_Str){
    STD_RETURN_t Return_Status = STD_OK;
        if((NULL == _LCD) || (NULL == _Str)){
            Return_Status = STD_NOT_OK;
        }
        else{
            while(*_Str){
                Return_Status = ECUAL_LCD_4BIT_Write_Data(_LCD,*_Str++);
            }
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_4BIT_Write_String_Position(const LCD_8BIT_t *_LCD,uint8 *_Str,uint8 _Row, uint8 _Column){
    STD_RETURN_t Return_Status = STD_OK;
        if((NULL == _LCD) || (NULL == _Str)){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status  = LCD_4Bit_Set_Cursor(_LCD,_Row,_Column);
            Return_Status &= ECUAL_LCD_4BIT_Write_String(_LCD,_Str);
        }
    return Return_Status;
}
STD_RETURN_t ECUAL_LCD_4BIT_Write_Custome_Char(const LCD_4BIT_t *_LCD,uint8 Row,uint8 Column,uint8 Mem_Pos,const uint8 _chr[]){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 Index_4Bit = ZERO_Init;
        if(NULL == _LCD){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status = ECUAL_LCD_4BIT_Write_Command(_LCD,(_LCD_SET_ADDRESS_TO_CGRAM+(Mem_Pos*8)));
            for(Index_4Bit =0; Index_4Bit < 8; Index_4Bit++){
                Return_Status &= ECUAL_LCD_4BIT_Write_Data(_LCD,_chr[Index_4Bit]);
            }
            Return_Status = ECUAL_LCD_4BIT_Write_Data_Position(_LCD,Mem_Pos,Row,Column);
        }
    return Return_Status;
}
    static STD_RETURN_t LCD_Send_4Bit_EN_Signal(const LCD_4BIT_t *_LCD){
        STD_RETURN_t Return_Status = STD_OK;
        Return_Status = MCAL_GPIO_Pin_Write_Logic(&(_LCD->EN_Pin),GPIO_HIGH);
        __delay_ms(5);
        Return_Status = MCAL_GPIO_Pin_Write_Logic(&(_LCD->EN_Pin),GPIO_LOW);
        return Return_Status;
    }
    static STD_RETURN_t LCD_Send_4Bits(const LCD_4BIT_t *_LCD, uint8 _Command){
        STD_RETURN_t Return_Status = STD_OK;
        Return_Status  = MCAL_GPIO_Pin_Write_Logic(&(_LCD->Data[0]),((_Command >> 0) & ((uint8 )0x01)));
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_LCD->Data[1]),((_Command >> 1) & ((uint8 )0x01)));
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_LCD->Data[2]),((_Command >> 2) & ((uint8 )0x01)));
        Return_Status &= MCAL_GPIO_Pin_Write_Logic(&(_LCD->Data[3]),((_Command >> 3) & ((uint8 )0x01)));
        return Return_Status;
    }
static STD_RETURN_t LCD_4Bit_Set_Cursor(const LCD_4BIT_t *_LCD, uint8 _Row, uint8 _Column){
    STD_RETURN_t Return_Status = STD_OK;
    _Column--;
    switch(_Row){
        case ROW1 :
            Return_Status = ECUAL_LCD_4BIT_Write_Command(_LCD,(0x80 + _Column));
            break;
        case ROW2 :
            Return_Status = ECUAL_LCD_4BIT_Write_Command(_LCD,(0xC0 + _Column));
            break;
        case ROW3 :
            Return_Status = ECUAL_LCD_4BIT_Write_Command(_LCD,(0x94 + _Column));
            break;
        case ROW4 :
            Return_Status = ECUAL_LCD_4BIT_Write_Command(_LCD,(0xD4 + _Column));
            break;
        default: 
            Return_Status = STD_NOT_OK;
    }
    return Return_Status;
}
#endif