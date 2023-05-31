/* 
 * File:   ADC_Interface.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:42 PM
 */

#ifndef ADC_INTERFACE_H
#define	ADC_INTERFACE_H

/********************************* Includes *********************************/
#include "../GPIO/GPIO_Interface.h"
#include "../Interrupt/Interrupt_Internal_Interface.h"
/********************************* Macro Definitions ************************/
#define ADC_AN0_CHANNEL  0
#define ADC_AN1_CHANNEL  1
#define ADC_AN2_CHANNEL  2
#define ADC_AN3_CHANNEL  3
#define ADC_AN4_CHANNEL  4
#define ADC_AN5_CHANNEL  5
#define ADC_AN6_CHANNEL  6
#define ADC_AN7_CHANNEL  7
#define ADC_AN8_CHANNEL  8
#define ADC_AN9_CHANNEL  9
#define ADC_AN10_CHANNEL 10
#define ADC_AN11_CHANNEL 11
#define ADC_AN12_CHANNEL 12

#define ADC_AQUISITION_TIME_0   0
#define ADC_AQUISITION_TIME_2   1
#define ADC_AQUISITION_TIME_4   2
#define ADC_AQUISITION_TIME_6   3
#define ADC_AQUISITION_TIME_8   4
#define ADC_AQUISITION_TIME_12  5
#define ADC_AQUISITION_TIME_16  6
#define ADC_AQUISITION_TIME_20  7

#define ADC_CONVERSION_CLOCK_FOSC_2   0
#define ADC_CONVERSION_CLOCK_FOSC_8   1
#define ADC_CONVERSION_CLOCK_FOSC_32  2
#define ADC_CONVERSION_CLOCK_FRC      3
#define ADC_CONVERSION_CLOCK_FOSC_4   4
#define ADC_CONVERSION_CLOCK_FOSC_16  5
#define ADC_CONVERSION_CLOCK_FOSC_64  6

#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F

#define ADC_CONVERSION_IN_PROGRESS 1
#define ADC_IDLE                   0

#define ADC_VOLTAGE_REF_ENABLE     1
#define ADC_VOLTAGE_REF_DISABLE    0
#define ADC_RIGHT_JUSTIFIED        1
#define ADC_LEFT_JUSTIFIED         0
/********************************* Macro Functions  *************************/
/* ADCON0: A/D CONTROL REGISTER 0 */
/* bit 0 ADON: A/D On bit */
#define ADC_MODULE_ENABLE()                    (ADCON0bits.ADON = 1)
#define ADC_MODULE_DISABLE()                   (ADCON0bits.ADON = 0)
/* bit 1 GO/DONE: A/D Conversion Status bit */
#define ADC_CONVERSION_STATUS()                (ADCON0bits.GO_nDONE)
#define ADC_START_CONVERSION()                 (ADCON0bits.GODONE = 1)
/* bit 5-2 CHS3:CHS0: Analog Channel Select bits */
#define ADC_SELECT_ANALOG_CHANNEL(_Channel)  (ADCON0bits.CHS = _Channel)
/* ADCON1: A/D CONTROL REGISTER 1 */
/* bit 5 VCFG1: Voltage Reference Configuration bit (VREF- source) */
/* bit 4 VCFG0: Voltage Reference Configuration bit (VREF+ source) */
#define ADC_VOLTAGE_REFERENCE_ENABLE()        do{ADCON1bits.VCFG1 = 1 ;\
                                               ADCON1bits.VCFG0 = 1 ;\
                                            }while(0); 
#define ADC_VOLTAGE_REFERENCE_DISABLE()       do{ADCON1bits.VCFG1 = 0 ;\
                                               ADCON1bits.VCFG0 = 0 ;\
                                            }while(0); 
/* bit 4 VCFG0: Voltage Reference Configuration bit (VREF+ source) */
#define ADC_PORT_CNONFIGURATION(_Config)       (ADCON1bits.PCFG = _Config)
/* ADCON2: A/D CONTROL REGISTER 2 */
/* bit 7 ADFM: A/D Result Format Select bit */
#define ADC_RIGHT_RESULT_FORMATE()             (ADCON2bits.ADFM = 1)
#define ADC_LEFT_RESULT_FORMATE()              (ADCON2bits.ADFM = 0)
/* bit 5-3 ACQT2:ACQT0: A/D Acquisition Time Select bits */
#define ADC_AQUISITION_TIME_SELECT(_Aq_Time)   (ADCON2bits.ACQT = _Aq_Time)
/* bit 2-0 ADCS2:ADCS0: A/D Conversion Clock Select bits */
#define ADC_CONVERSION_CLOCK_SELECT(_CLOCK)    (ADCON2bits.ADCS = _CLOCK)

/********************************* User-Defined Data Types ******************/
typedef struct{
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void(* ADC_InterruptHandler)(void);
    Priority_t ADC_Priority;
#endif
    uint8 Port_Control :4;
    uint8 ANx_Channel  :3;
    uint8 Voltage_Ref  :1;
    uint8 Aquisition_Time :3;
    uint8 Result_Format :1;
    uint8 Clock :3;
    uint8 Reserved :1;
}ADC_t;
/********************************* Functions Declaration ********************/
STD_RETURN_t MCAL_ADC_Initialize(const ADC_t *_ADC);
STD_RETURN_t MCAL_ADC_DeInitialize(const ADC_t *_ADC);
STD_RETURN_t ADC_SelectChannel(const ADC_t *_ADC, uint8 channel);
STD_RETURN_t ADC_Start_Conversion(const ADC_t *_ADC);
STD_RETURN_t ADC_IsConversion_Done(const ADC_t *_ADC, uint8 *conversion_status);
STD_RETURN_t ADC_GetConversionResult(const ADC_t *_ADC, uint8 *conversion_result);
STD_RETURN_t ADC_GetConversion_Blocking(const ADC_t *_ADC, uint8 channel, uint8 *conversion_result);
STD_RETURN_t ADC_StartConversion_Interrupt(const ADC_t *_ADC, uint8 channel);
#endif	/* ADC_INTERFACE_H */

