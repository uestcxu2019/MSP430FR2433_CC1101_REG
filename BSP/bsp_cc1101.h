/*
 * bsp_cc1101.h
 *
 *  Created on: 2018年11月30日
 *      Author: xu
 */

#ifndef BSP_BSP_CC1101_H_
#define BSP_BSP_CC1101_H_

#include "msp430fr2433.h"
#include "bsp_delay.h"
#include "bsp_spi.h"
#include "bsp_led.h"

/*
**	说明：所有的请参照CC115L 或CC1101手册
 *	IDLE：空闲状态
*/


//定义写入或读取方式

#define	CC1101_UNIQUE_ADDR		0xAB


#define		WRITE_SINGLE		0x00						//单字节写入
#define 	WRITE_BURST     	0x40						//连续写入
#define 	READ_SINGLE     	0x80						//单字节读取
#define 	READ_BURST      	0xC0						//连续读取


#define     READ_BURST_FIFO     0xFF        //突发读取RX FIFO
#define     READ_SINGLE_FIFO    0xBF        //单字节读取 RX FIFO
#define     WRITE_BURST_FIFO    0x7F        //突发写TX FIFO
#define     WRITE_SINGLE_FIFO   0x3F        //单字节写 TX FIFO


//PATABLE存取
#define     READ_BURST_PATABLE     0xFE        //突发读取PATABLE
#define     READ_SINGLE_PATABLE    0xBE        //单字节读取 RX FIFO
#define     WRITE_BURST_PATABLE    0x7E        //突发写TX FIFO
#define     WRITE_SINGLE_PATABLE   0x3E        //单字节写 TX FIFO

/*******************************选通寄存器地址(写地址)【13个】**********************************
	*	当操作这些寄存器时，会使内部状态或模式发生改变
	*	bit7,R(1),当地址大于0x20时,bit6不再为突发位，bit6 --1,时为状态，bit6 --0时为选通

*/
#define		SRES				0x30						//复位芯片
#define		SFSTXON				0x31						//开启和校准频率合成器
#define		SXOFF				0x32						//关闭晶体振荡器
#define		SCAL				0x33						//校准频率合成器并将其关闭
#define		SRX					0x34						//进入 RX
#define		STX					0x35						//进入TX模式(写)
#define		SIDLE				0x36						//退出 RX/TX 模式,可以SIDLE 指令选通脉冲来强制无线控制器进入 IDLE 状态
#define		SWOR				0x38						//若 WORCTRL.RC_PD=0,则运行自动 RX轮询序列（无线唤醒）
#define		SPWD				0x39						//当 CSn 为高电平时进入断电模式(休眠模式)
#define		SFRX				0x3A						//刷 新RXFIFO缓冲器,仅在IDLE或RXFIFO_OVERFLOW状态下才发送SFRX
#define		SFTX				0x3B						//刷 新TXFIFO缓冲器,仅在IDLE或TXFIFO_OVERFLOW状态下才发送SFTX
#define		SWORRST				0x3C						//复位实时时钟为事件 1 值



/*******************************8位通用(标准)地址(可读可写地址,这里定义写地址)【47个】**********************************
	*	如果要读取，可以对当前指令直接(与上)&0x80(单字节读取)
	*	bit7,R(1),当地址大于0x20时,bit6不再为突发位，bit6 --1,时为状态，bit6 --0时为选通
*/

#define     IOCFG2_ADDR			0x00						//GDO2单字节写地址
#define     IOCFG1_ADDR			0x01						//GDO1单字节写地址,用作MISO,默认注释掉,不做普通IO口
#define     IOCFG0_ADDR			0x02						//GDO0单字节写地址
#define     FIFOTHR				0x03						//RX FIFO 和 TX FIFO 阈值
#define     SYNC1				0x04						//同步字，高字节
#define     SYNC0				0x05						//同步字，低字节
#define     PKTLEN				0x06						//数据包长度
#define     PKTCTRL1			0x07						//数据包自动控制
#define     PKTCTRL0			0x08						//数据包自动控制
#define     ADDR				0x09						//器件地址
#define     CHANNR				0x0A						//信道数量
#define     FSCTRL1				0x0B						//频率合成器控制
#define     FSCTRL0				0x0C						//频率合成器控制
#define     FREQ2				0x0D						//频率控制字，高字节
#define     FREQ1				0x0E						//频率控制字，中间字节
#define     FREQ0				0x0F						//频率控制字，低字节
#define     MDMCFG4				0x10						//调制解调器配置
#define     MDMCFG3				0x11						//调制解调器配置
#define     MDMCFG2				0x12						//调制解调器配置
#define     MDMCFG1				0x13						//调制解调器配置
#define     MDMCFG0				0x14						//调制解调器配置
#define     DEVIATN				0x15						//调制解调器偏差设置
#define     MCSM2				0x16						//主无线控制状态机配置
#define     MCSM1				0x17						//主无线控制状态机配置
#define     MCSM0				0x18						//主无线控制状态机配置
#define     FOCCFG				0x19						//频率偏移补偿配置
#define     BSCFG				0x1A						//位同步配置
#define     AGCTRL2				0x1B						//AGC 控制
#define     AGCTRL1				0x1C						//AGC 控制
#define     AGCTRL0				0x1D						//AGC 控制
#define     WOREVT1				0x1E						//高字节事件 0 超时
#define     WOREVT0				0x1F						//低字节事件 0 超时
#define     WORCTRL				0x20						//无线唤醒控制
#define     FREND1				0x21						//前端 RX 配置
#define     FREND0				0x22						//前端 TX 配置
#define     FSCAL3				0x23						//频率合成器校准
#define     FSCAL2				0x24						//频率合成器校准
#define     FSCAL1				0x25						//频率合成器校准
#define     FSCAL0				0x26						//频率合成器校准
#define     RCCTRL1				0x27						//RC 振荡器配置
#define     RCCTRL0				0x28						//RC 振荡器配置
#define     FSTEST				0x29						//频率合成器校准控制,不得进行写操作
#define     PTEST				0x2A						//生产测试
#define     AGCTEST				0x2B						//AGC 测试,不得进行写操作
#define     TEST2    			0x2C						//各种测试设置
#define     TEST1				0x2D						//各种测试设置
#define     TEST0				0x2E						//各种测试设置

#define		PATABLE				0x3E						//输出功率控制


//两个通用引脚输出值
#define     GDO_LOW				0x00						//查阅手册，0x00保留,bit7 无用,bit6 判定输出高低电平
#define     GDO_HIGH			0X40						//输出高电平

						//bit7,R(1),当地址大于0x20时,bit6不再为突发位，bit6 --1,时为状态，bit6 --0时为选通

/*******************************状态寄存器地址(读地址)【只能读(12个)】**********************************
	*	bit7,R(1),当地址大于0x20时,bit6不再为突发位，bit6 --1,时为状态，bit6 --0时为选通
*/

#define		PARTNUM				0xF0				//芯片组件数目地址
#define		VERSION				0xF1				//读取版本指令地址
#define		FREQEST				0xF2				//频率偏移估计
#define		LQI					0xF3				//链路质量解调器评估
#define		RSSI				0xF4				//接收信号强度指示地址
#define		MARCSTATE			0xF5				//主无线控制状态机状态地址
#define		WORTIME1			0xF6				//WOR 定时器高字节
#define		WORTIME0			0xF7				//WOR 定时器低字节
#define		PKTSTATUS			0xF8				//当前 GDOx 状态和数据包状态
#define		VCO_VC_DAC			0xF9				//PLL 校准模块的当前设置
#define		TXBYTES				0xFA				//TX FIFO 中的下溢和字节数
#define		RXBYTES				0xFB				//RX FIFO 中的下溢和字节数
#define		RCCTRL1_STATUS		0xFC				//最终 RC 振荡器校准结果
#define		RCCTRL0_STATUS		0xFD				//最终 RC 振荡器校准结果



//定义数据包长度
#define		DATA_LEN			255					//定义数据包长度


void Write_CMD(uint8_t CMD);
void Write_Data(uint8_t Write_Addr,uint8_t Write_data);
void Write_burst(uint8_t Write_Addr,uint8_t *pbuffer,uint8_t Length);
void CC1101_Reset(void);
void CC1101_Init(void);
void WriteTxFITO(uint8_t * pBuffer,uint8_t len);
void CC1101_RFDataPack_Send(uint8_t *pBuff, uint16_t len);

#endif /* BSP_BSP_CC1101_H_ */
