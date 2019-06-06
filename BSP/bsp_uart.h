/*
 * bsp_uart.h
 *
 *  Created on: 2019年5月28日
 *      Author: xuz
 *      硬件说明: 与下载端口相接的uart  RXD P1.5  TXD P1.4
 */




#ifndef BSP_BSP_UART_H_
#define BSP_BSP_UART_H_

#include "msp430fr2433.h"
#include "bsp_delay.h"

#define UART_TXD_PIN	BIT4
#define UART_RXD_PIN	BIT5


void Uart_GPIO_Config(void);
void Uart_REG_Config(void);
void UART_Init(void);

void Uart_Send(uint16_t data);


#endif /* BSP_BSP_UART_H_ */
