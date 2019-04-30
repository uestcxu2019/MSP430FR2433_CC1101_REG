/*
 * bsp_fram_rw.h
 *
 *  Created on: 2019Äê4ÔÂ11ÈÕ
 *      Author: xuz
 */

#ifndef BSP_BSP_FRAM_RW_H_
#define BSP_BSP_FRAM_RW_H_

#include "msp430fr2433.h"
#include "bsp_delay.h"
#include "stdio.h"


void Fram_Enable(void);
void Data_Fram_Write_Enable(void);
void Data_Fram_Write_Disable(void);

void Fram_Write(uint16_t write_addr, uint8_t data);
uint8_t Fram_Read(uint16_t read_addr);

#endif /* BSP_BSP_FRAM_RW_H_ */
