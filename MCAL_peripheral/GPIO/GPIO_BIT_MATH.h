/* 
 * File:   GPIO_BIT_MATH.h
 * Author: Bassam Mamdouh Mohammed
 * LinkedIn: https://www.linkedin.com/in/bassam-mamdouh
 * Created on 05 ??????, 2022, 01:53 ?
 */

#ifndef GPIO_BIT_MATH_H
#define	GPIO_BIT_MATH_H

#define BIT_MASK (STD_RETURN_t)1
#define PORT_MASK 0xFF

#define Set_BIT(Register,Bit)    (Register |=  (BIT_MASK  << Bit))
#define Clear_BIT(Register,Bit)  (Register &= ~(BIT_MASK  << Bit))
#define Toggle_BIT(Register,Bit) (Register ^=  (BIT_MASK  << Bit))
#define Read_BIT(Register,Bit)   ((Register >> Bit) & BIT_MASK)

#endif	/* GPIO_BIT_MATH_H */

