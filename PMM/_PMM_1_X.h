/*
 * _PMM_1_X.h
 *
 *  Created on: 2018Äê12ÔÂ3ÈÕ
 *      Author: lenovo
 */

#ifndef PMM_1_X_H_
#define PMM_1_X_H_

#include "_msp430fr2433.h"

#define _PMM_IO_DH      P3OUT |= BIT0
#define _PMM_IO_CLKH    P3OUT |= BIT1
#define _PMM_IO_DL      P3OUT &= ~BIT0
#define _PMM_IO_CLKL    P3OUT &= ~BIT1

#define _PMM_IO_SHORT    P2OUT |= BIT7

void _PMM1X_IO_Start();
void _PMM1X_IO_End();

#endif /* PMM_1_X_H_ */
