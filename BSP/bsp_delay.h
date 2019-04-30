/*
 * bsp_delay.h
 *
 *  Created on: 2018年12月1日
 *      Author: xu
 *      说	明:关于MSP430单片机使用__delay_cycles延时的问题.
 *				IAR for MSP430编译器提供了一个编译器内联的精确延时函数(并非真正的
 *				函数)以提供用户精确延时使用, 该函数原型是:
 *				__intrinsic void __delay_cycles(unsigned long __cycles);
 *				该内部函数实现__cycles个CPU周期的延时,但对于该参数的设置,我要陈述一下:
 *				__cycles需要我们传递的是CPU运行的周期个数
 *
 *				网上普遍的用法是:
 *				#define CPU_CLOCK 8000000
 *				#define delay_us(us) __delay_cycles(CPU_CLOCK/1000000*(us))
 *				#define delay_ms(ms) __delay_cycles(CPU_CLOCK/1000*(ms))
 *
 *				在CPU主时钟频率为8MHz时, 这确实没有问题, 但是这样的写法:
 *				#define CPU_CLOCK 8000000
 *				这很容易让人们想到, 可以通过修改它的值以实现对不同主频系统参数的统一,其实
 *				这是不正确的! 比如修改为#define CPU_CLOCK 32768以实现32KHz主频的延时...
 *
 *				下面来计算看看:
 *				当系统主时钟频率CPU_CLOCK为8MHz时:
 *				频率 f = 8MHz = 8,000,000Hz
 *				机器周期 Tm = 1/f = 1/8MHz = 1/8us
 *				也就是说,一个机器周期(nop)的时长是1/8us,所以延时1us即8*Tm,同上面:
 *				#define delay_us(us) __delay_cycles(8*(us))
 *				#define delay_ms(ms) __delay_cycles(8000*(ms))
 *
 *				按照上面的宏定义方法,我们把CPU_CLOCK定义成32768,那么:
 *				频率 f = 32KHz = 32,768Hz
 *				机器周期 Tm = 1/f = 1/32768Hz ~= 30.5us
 *				可想而知,CPU最短的指令执行周期为30.5us, 这时, 想延时1us, 这可能吗?
 *				所以, 简单地把上面的定义改成
 *				#define CPU_CLOCK 32768
 *				是绝对错误的.
 *
 *				同样, 还有些朋友实现了0.5us的延时, 这在当f = 1MHz = 1000000Hz时也
 *				是不现实的, 此时机器周期Tm = 1us. 在f = 8Mhz时, 4个机器周期为0.5us尚可.
 *
 *				所以, 为避免引起错误的使用或不正确的理解,最好像下面这样定义宏:
 *				#if CPU_CLOCK == 8000000
 *				#define delay_us(us) __delay_cycles(8*(us))
 *				#define delay_ms(ms) __delay_cycles(8000*(ms))
 *				#else
 *				#pragma error "CPU_CLOCK is defined implicitly!"
 *				#endif
 *
 *				另外:
 *　　				  __delay_cycles 并不是真正的函数, 只是提供编译器内联展开,该函数并
 *				不支持变量参数, 其参数只能是常数.
 */

#ifndef BSP_BSP_DELAY_H_
#define BSP_BSP_DELAY_H_

#include "msp430fr2433.h"

#define CPU_CLOCK		1000000			//1MHz
#define Delay_us(us)	 __delay_cycles(CPU_CLOCK/1000000*(us))
#define Delay_ms(ms) 	 __delay_cycles(CPU_CLOCK/1000*(ms))

#define uint8_t   unsigned char
#define uint16_t  unsigned int


#define _IO		  volatile				//允许读写
#define _I		  volatile const		//只允许读



#endif /* BSP_BSP_DELAY_H_ */
