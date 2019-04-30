/*
 * bsp_fram_rw.c
 *
 *  Created on: 2019年4月11日
 *      Author: xuz
 *
 *      说明:
 *      		在配置数据写保护或代码数据写保护前，必须要先配置解锁FRAM写保护
 */
#include "bsp_fram.h"


/*
 *	描	述：解除FRAM写保护
 *	参	数：无
 *	返回值 ：无
*/
void Fram_Enable(void)
{
	SYSCFG0 = 0xA500;	//必须解除FRAM写保护
}


/*
 *	描	述：信息存储段数据写入使能
 *	参	数：无
 *	返回值 ：无
*/
void Data_Fram_Write_Enable(void)
{
	SYSCFG0 &=~ DFWP;	//配置数据写使能
}


/*
 *	描	述：信息存储段数据写入失能(即写入保护，不让写数据)
 *	参	数：无
 *	返回值 ：无
*/
void Data_Fram_Write_Disable(void)
{
	SYSCFG0 |= DFWP;	//配置数据写使能
}


/*
 *	描	述：向FRAM指定地址写入数据
 *	参	数：write_addr: 要写入数据的地址
 *		   data :       要写入的数据
 *	返回值 ：无
*/
void Fram_Write(uint16_t write_addr, uint8_t data)
{
	*(uint16_t *)write_addr = data;
}


/*
 *	描	述：读取FRAM指定地址的值
 *	参	数：read_addr: 要读取数据的地址
 *	返回值 ：无
*/
uint8_t Fram_Read(uint16_t read_addr)
{
	uint8_t Read_data;
	Read_data = *(uint16_t *)read_addr;
	return  Read_data;
}

