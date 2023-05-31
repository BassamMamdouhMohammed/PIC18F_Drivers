/* 
 * File:   ADC_Program.c
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on September 20, 2022, 4:42 PM
 */
#include "ADC_Interface.h"

#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*ADC_Interrupt_Handler)(void) = NULL;
#endif

static void ADC_Result_Format_Select(const ADC_t *_ADC);
static void ADC_Volatage_Ref_Select(const ADC_t *_ADC);
static void ADC_Port_Configuration_Select(const ADC_t *_ADC);

STD_RETURN_t MCAL_ADC_Initialize(const ADC_t *_ADC){
    STD_RETURN_t Return_Status = STD_OK;
        if(NULL == _ADC){
            Return_Status = STD_NOT_OK;
        }
        else{
            ADC_MODULE_DISABLE();
            ADC_AQUISITION_TIME_SELECT(_ADC->Aquisition_Time);
            ADC_CONVERSION_CLOCK_SELECT(_ADC->Clock);
            ADC_SELECT_ANALOG_CHANNEL(_ADC->ANx_Channel);
            ADC_Port_Configuration_Select(_ADC);
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
            ADC_INTERRUPT_ENABLE();
            ADC_INTERRUPT_CLEAR_FLAG();
            ADC_Interrupt_Handler = _ADC->ADC_InterruptHandler;
#if INTERRUPT_PRIORITY_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PRIORITY_LEVELS_ENABLE();
            if(Low_Priority == _ADC->ADC_Priority){
                INTERRUPT_GLOBAL_LOW_PRIORITY_ENABLE();
                ADC_INTERRUPT_LOW_PRIORITY();
            }
            else if(High_Priority == _ADC->ADC_Priority){
                INTERRUPT_GLOBAL_HIGH_PRIORITY_ENABLE();
                ADC_INTERRUPT_HIGH_PRIORITY();
            }
            else{ /* if you are here then you don't select Priority Levels */}
    
#else
           INTERRUPT_GLOBAL_ENABLE();
           INTERRUPT_PERIPHERAL_ENABLE();
#endif           
#endif            
            ADC_Volatage_Ref_Select(_ADC);
            ADC_Result_Format_Select(_ADC);
            ADC_MODULE_ENABLE();
        }
    return Return_Status;
}
STD_RETURN_t MCAL_ADC_DeInitialize(const ADC_t *_ADC){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _ADC){
            Return_Status = STD_NOT_OK;
        }
        else{
        ADC_MODULE_DISABLE();
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE();
#endif        
        }
    return Return_Status;
}
STD_RETURN_t ADC_SelectChannel(const ADC_t *_ADC, uint8 channel){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _ADC){
            Return_Status = STD_NOT_OK;
        }
        else{
            ADC_SELECT_ANALOG_CHANNEL(channel);
            ADC_Port_Configuration_Select(_ADC);
        }
    return Return_Status;
}
STD_RETURN_t ADC_Start_Conversion(const ADC_t *_ADC){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _ADC){
            Return_Status = STD_NOT_OK;
        }
        else{
            ADC_START_CONVERSION();
        }
    return Return_Status;
}
STD_RETURN_t ADC_IsConversion_Done(const ADC_t *_ADC, uint8 *conversion_status){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == _ADC) || (NULL == conversion_status)){
            Return_Status = STD_NOT_OK;
        }
        else{
            *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
        }
    return Return_Status;
}
STD_RETURN_t ADC_GetConversionResult(const ADC_t *_ADC, uint8 *conversion_result){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == _ADC) || (NULL == conversion_result)){
            Return_Status = STD_NOT_OK;
    }
    else{ 
        if(ADC_RIGHT_JUSTIFIED == _ADC->Result_Format){
            *conversion_result = (uint8)((ADRESH << 8 ) + ADRESL);
        }
        else if(ADC_LEFT_JUSTIFIED == _ADC->Result_Format){
            *conversion_result = (uint8)(((ADRESH << 8) + ADRESL) >> 6);
        }
        else{ /* Hello There */ }
    }
    return Return_Status;
}
STD_RETURN_t ADC_GetConversion_Blocking(const ADC_t *_ADC, uint8 channel, uint8 *conversion_result){
    STD_RETURN_t Return_Status = STD_OK;
    if((NULL == _ADC) || (NULL == conversion_result)){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status = ADC_SelectChannel(_ADC,channel);
            Return_Status = ADC_Start_Conversion(_ADC);
            while(ADCON0bits.GO_nDONE);
            Return_Status = ADC_GetConversionResult(_ADC, conversion_result);
        }
    return Return_Status;
}
STD_RETURN_t ADC_StartConversion_Interrupt(const ADC_t *_ADC, uint8 channel){
    STD_RETURN_t Return_Status = STD_OK;
    if(NULL == _ADC){
            Return_Status = STD_NOT_OK;
        }
        else{
            Return_Status = ADC_SelectChannel(_ADC,channel);
            Return_Status = ADC_Start_Conversion(_ADC);
        }
    return Return_Status;
}
static void ADC_Volatage_Ref_Select(const ADC_t *_ADC){
    if(ADC_VOLTAGE_REF_ENABLE == _ADC->Voltage_Ref){
        ADC_VOLTAGE_REFERENCE_ENABLE();
    }
    else if(ADC_VOLTAGE_REF_DISABLE == _ADC->Voltage_Ref){
        ADC_VOLTAGE_REFERENCE_DISABLE();
    }
    else{ /* if you are here then you don't select Voltage Reference */ }
}
static void ADC_Result_Format_Select(const ADC_t *_ADC){
    if(ADC_RIGHT_JUSTIFIED == _ADC->Result_Format){
        ADC_RIGHT_RESULT_FORMATE();
    }
    else if(ADC_LEFT_JUSTIFIED == _ADC->Result_Format){
        ADC_LEFT_RESULT_FORMATE();
    }
    else{ /* if you are here then you don't select Result Format */ }
}
static void ADC_Port_Configuration_Select(const ADC_t *_ADC){
    switch(_ADC->ANx_Channel){
        case ADC_AN0_CHANNEL :
            Set_BIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_AN1_CHANNEL :
            Set_BIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_AN2_CHANNEL :
            Set_BIT(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_AN3_CHANNEL :
            Set_BIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_AN4_CHANNEL :
            Set_BIT(TRISA, _TRISA_RA5_POSN);
            break;  
        case ADC_AN5_CHANNEL :
            Set_BIT(TRISE, _TRISE_RE0_POSN);
            break;
        case ADC_AN6_CHANNEL :
            Set_BIT(TRISE, _TRISE_RE1_POSN);
            break;
        case ADC_AN7_CHANNEL :
            Set_BIT(TRISE, _TRISE_RE2_POSN);
            break;
        case ADC_AN8_CHANNEL :
            Set_BIT(TRISB, _TRISB_RB2_POSN);
            break;
        case ADC_AN9_CHANNEL :
            Set_BIT(TRISB, _TRISB_RB3_POSN);
            break;
        case ADC_AN10_CHANNEL :
            Set_BIT(TRISB, _TRISB_RB1_POSN);
            break;
        case ADC_AN11_CHANNEL :
            Set_BIT(TRISB, _TRISB_RB4_POSN);
            break;
        case ADC_AN12_CHANNEL :
            Set_BIT(TRISB, _TRISB_RB0_POSN);
            break;    
        default: /* Hello There*/ ;
    }
}