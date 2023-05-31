/* 
 * File:   LCD_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 29, 2022, 4:28 PM
 */

#ifndef LCD_INTERFACE_H
#define	LCD_INTERFACE_H

/********************************* Includes *********************************/
#include "../../MCAL_peripheral/GPIO/GPIO_Interface.h"
/********************************* Macro Definitions ************************/
#define _LCD_MODE_ENABLE                          1U
#define _LCD_4BIT_MODE_ENABLE _LCD_MODE_ENABLE
#define _LCD_8BIT_MODE_ENABLE _LCD_MODE_ENABLE
#define _LCD_CLEAR_DISPLAY                        0x01
#define _LCD_CURSOR_HOME                          0x02
#define _LCD_DECREMENT_SHIFT_OFF                  0x04
#define _LCD_DECREMENT_SHIFT_ON                   0x05
#define _LCD_INCREMENT_SHIFT_OFF                  0x06
#define _LCD_INCREMENT_SHIFT_ON                   0x07
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_ON    0x0F
#define _LCD_DISPLAY_ON_UNDERLINE_ON_CURSOR_OFF   0x0E
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_ON   0x0D
#define _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF  0x0C
#define _LCD_DISPLAY_OFF_UNDERLINE_OFF_CURSOR_OFF 0x08
#define _LCD_CURSOR_MOVE_SHIFT_LEFT               0x10
#define _LCD_CURSOR_MOVE_SHIFT_RIGHT              0x14
#define _LCD_DISPLAY_SHIFT_LEFT                   0x18
#define _LCD_DISPLAY_SHIFT_RIGHT                  0x1C
#define _LCD_8BIT_BUS_MODE_2LINE                  0x38
#define _LCD_4BIT_BUS_MODE_2LINE                  0x28
#define _LCD_SET_ADDRESS_TO_CGRAM                 0x40
#define _LCD_SET_ADDRESS_TO_DDRAM                 0x80

#define ROW1                                      0x01
#define ROW2                                      0x02
#define ROW3                                      0x03
#define ROW4                                      0x04
/********************************* Macro Functions  *************************/

/********************************* User-Defined Data Types ******************/
typedef struct{
    PIN_t RS_Pin;
    PIN_t EN_Pin;
    PIN_t Data[8];
}LCD_8BIT_t;
typedef struct{
    PIN_t RS_Pin;
    PIN_t EN_Pin;
    PIN_t Data[4];
}LCD_4BIT_t;
/********************************* Functions Declaration ********************/
#if _LCD_8BIT_MODE_ENABLE==_LCD_MODE_ENABLE
STD_RETURN_t ECUAL_LCD_8BIT_Initialize(const LCD_8BIT_t *_LCD);
STD_RETURN_t ECUAL_LCD_8BIT_Write_Command(const LCD_8BIT_t *_LCD,uint8 _Command);
STD_RETURN_t ECUAL_LCD_8BIT_Write_Data(const LCD_8BIT_t *_LCD,uint8 _Data);
STD_RETURN_t ECUAL_LCD_8BIT_Write_Data_Position(const LCD_8BIT_t *_LCD,uint8 _Data,uint8 _Row, uint8 _Column);
STD_RETURN_t ECUAL_LCD_8BIT_Write_String(const LCD_8BIT_t *_LCD,uint8 *_Str);
STD_RETURN_t ECUAL_LCD_8BIT_Write_String_Position(const LCD_8BIT_t *_LCD,uint8 *_Str,uint8 _Row, uint8 _Column);
STD_RETURN_t ECUAL_LCD_8BIT_Write_Custome_Char(const LCD_8BIT_t *_LCD,uint8 Row,uint8 Column,uint8 Mem_Pos,const uint8 _chr[]);
#endif

#if _LCD_4BIT_MODE_ENABLE==_LCD_MODE_ENABLE
STD_RETURN_t ECUAL_LCD_4BIT_Initialize(const LCD_4BIT_t *_LCD);
STD_RETURN_t ECUAL_LCD_4BIT_Write_Command(const LCD_4BIT_t *_LCD,uint8 _Command);
STD_RETURN_t ECUAL_LCD_4BIT_Write_Data(const LCD_4BIT_t *_LCD,uint8 _Data);
STD_RETURN_t ECUAL_LCD_4BIT_Write_Data_Position(const LCD_4BIT_t *_LCD,uint8 _Data,uint8 _Row, uint8 _Column);
STD_RETURN_t ECUAL_LCD_4BIT_Write_String(const LCD_4BIT_t *_LCD,uint8 *_Str);
STD_RETURN_t ECUAL_LCD_4BIT_Write_String_Position(const LCD_8BIT_t *_LCD,uint8 *_Str,uint8 _Row, uint8 _Column);
STD_RETURN_t ECUAL_LCD_4BIT_Write_Custome_Char(const LCD_4BIT_t *_LCD,uint8 Row,uint8 Column,uint8 Mem_Pos,const uint8 _chr[]);
#endif

#endif	/* LCD_INTERFACE_H */

