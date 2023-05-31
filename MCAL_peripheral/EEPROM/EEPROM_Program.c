/* 
 * File:   EEPROM_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:39 PM
 */
#include "EEPROM_Interface.h"

STD_RETURN_t MCAL_EEPROM_Write_Byte(uint16 _Adr,uint8 _Data){
    STD_RETURN_t Return_Status = STD_OK;
    uint8 Global_Interrupt = INTCONbits.GIE;
    INTERRUPT_GLOBAL_DISABLE();
    EEADRH = (uint8)((_Adr >> 8) & 0x03);
    EEADR  = (uint8)(_Adr & 0xFF);
    EEDATA = _Data;
    EEPROM_DATA_EEPROM_MEMORY();
    EEPROM_FLASH_OR_EEPROM();
    EECON2 = 0x55;
    EECON2 = 0x0AA;
    EEPROM_INITIATE_EEPROM_WRITE_ERASE(); 
    EEPROM_WRITE_CYCLES();
    while(EECON1bits.WR);
    EEPROM_INHIBITS_WRITE_CYCLES();
    INTCONbits.GIE = Global_Interrupt;
    return Return_Status;
}
STD_RETURN_t MCAL_EEPROM_Read_Byte(uint16 _Adr,uint8 *_Data){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _Data){
        Return_Status = STD_NOT_OK;
    }
    else{
        EEADRH = (uint8)((_Adr >> 8) & 0x03);
        EEADR  = (uint8)(_Adr & 0xFF);
        EEPROM_DATA_EEPROM_MEMORY();
        EEPROM_INITIATE_EEPROM_READ();
        EEPROM_FLASH_OR_EEPROM();
        NOP();
        NOP();
        *_Data = EEDATA;
    }
    return Return_Status;
}