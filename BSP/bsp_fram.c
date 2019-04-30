/*
 * bsp_fram_rw.c
 *
 *  Created on: 2019��4��11��
 *      Author: xuz
 *
 *      ˵��:
 *      		����������д�������������д����ǰ������Ҫ�����ý���FRAMд����
 */
#include "bsp_fram.h"


/*
 *	��	�������FRAMд����
 *	��	������
 *	����ֵ ����
*/
void Fram_Enable(void)
{
	SYSCFG0 = 0xA500;	//������FRAMд����
}


/*
 *	��	������Ϣ�洢������д��ʹ��
 *	��	������
 *	����ֵ ����
*/
void Data_Fram_Write_Enable(void)
{
	SYSCFG0 &=~ DFWP;	//��������дʹ��
}


/*
 *	��	������Ϣ�洢������д��ʧ��(��д�뱣��������д����)
 *	��	������
 *	����ֵ ����
*/
void Data_Fram_Write_Disable(void)
{
	SYSCFG0 |= DFWP;	//��������дʹ��
}


/*
 *	��	������FRAMָ����ַд������
 *	��	����write_addr: Ҫд�����ݵĵ�ַ
 *		   data :       Ҫд�������
 *	����ֵ ����
*/
void Fram_Write(uint16_t write_addr, uint8_t data)
{
	*(uint16_t *)write_addr = data;
}


/*
 *	��	������ȡFRAMָ����ַ��ֵ
 *	��	����read_addr: Ҫ��ȡ���ݵĵ�ַ
 *	����ֵ ����
*/
uint8_t Fram_Read(uint16_t read_addr)
{
	uint8_t Read_data;
	Read_data = *(uint16_t *)read_addr;
	return  Read_data;
}

