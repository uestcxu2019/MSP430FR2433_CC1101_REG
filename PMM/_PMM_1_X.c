/*
 * _PMM_1_X.c
 *
 *  Created on: 2018Äê12ÔÂ3ÈÕ
 *      Author: lenovo
 */
#include"_PMM_1_X.h"

void _PMM1X_IO_Start()
{
    _PMM_IO_CLKH;
    _PMM_IO_DH;
}

// t~150us
void _PMM1X_IO_End()
{
    while(1)
    {
        _PMM_IO_CLKL;
        _MCU_T0_Delay30us(5);       //~30.5us
        _PMM_IO_CLKH;
        _MCU_T0_Delay30us(5);       //~30.5us
    }
}


