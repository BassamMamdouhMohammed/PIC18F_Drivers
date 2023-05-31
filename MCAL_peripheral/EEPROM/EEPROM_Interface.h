/* 
 * File:   EEPROM_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:39 PM
 */

#ifndef EEPROM_INTERFACE_H
#define	EEPROM_INTERFACE_H

/********************************* Includes *********************************/
#include "../GPIO/GPIO_Interface.h"
#include "../Interrupt/Interrupt_Internal_Interface.h"
/********************************* Macro Definitions ************************/

/********************************* Macro Functions  *************************/
/* EECON1: EEPROM CONTROL REGISTER 1 */
/* bit 7 EEPGD: Flash Program or Data EEPROM Memory Select bit */
#define EEPROM_FLASH_PROGRAM_MEMORY()            (EECON1bits.EEPGD = 1)
#define EEPROM_DATA_EEPROM_MEMORY()              (EECON1bits.EEPGD = 0)
/* bit 6 CFGS: Flash Program/Data EEPROM or Configuration Select bit */
#define EEPROM_CONFIGURATION_REGISTERS()         (EECON1bits.CFGS = 1)
#define EEPROM_FLASH_OR_EEPROM()                 (EECON1bits.CFGS = 0)
/* bit 2 WREN: Flash Program/Data EEPROM Write Enable bit */
#define EEPROM_WRITE_CYCLES()                    (EECON1bits.WREN = 1)
#define EEPROM_INHIBITS_WRITE_CYCLES()           (EECON1bits.WREN = 0)
/* bit 1 WR: Write Control bit */
#define EEPROM_INITIATE_EEPROM_WRITE_ERASE()     (EECON1bits.WR = 1)
#define EEPROM_INITIATE_EEPROM_WRITE_COMPLETE()  (EECON1bits.WR = 0)
/* bit 0 RD: Read Control bit */
#define EEPROM_INITIATE_EEPROM_READ()            (EECON1bits.RD = 1)
#define EEPROM_UNINITIATE_EEPROM_READ()          (EECON1bits.RD = 0)
/********************************* User-Defined Data Types ******************/

/********************************* Functions Declaration ********************/
STD_RETURN_t MCAL_EEPROM_Write_Byte(uint16 _Adr,uint8 _Data);
STD_RETURN_t MCAL_EEPROM_Read_Byte(uint16 _Adr,uint8 *_Data);
#endif	/* EEPROM_INTERFACE_H */

