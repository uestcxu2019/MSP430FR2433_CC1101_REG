/*
 * bsp_cs.c
 *
 *  Created on: 2019年6月11日
 *      Author: xuz
 */
#include "bsp_cs.h"

/************************************************************************************************
 *  说	明 : 时钟寄存器初始化
 *  参	数 : 无
 *  返回值  : 无
*************************************************************************************************/
void CS_Init(void)
{
	CSCTL1 = 0x0035; //配置DCO为4MHz

}



