/*
 * _msp430fr6989_lanchpad.h
 *  HR2018.11.29
 */
/*
 * Data typy name   :   uint, uchar
 *
 * Define number    :   D_UART_READmaxLength
 *
 * Define operation :   _LED_R_INIT
 *                      _LED_R_on
 *                      _LED_R_off
 *                      _LED_L_INIT
 *                      _LED_L_on
 *                      _LED_L_off
 *                      _UCB0_I2C_PORTINIT
 *                      _ADC12_ADC_PORTINIT
 *                      _UCA1_UART_PORTINIT
 *                      _UCA0_UART_PORTINIT
 *
 * function         :   void _MCU_OPeration_NULL_();
 *                      #define _LED_Blink_R(time)
 *                      #define _LED_Blink_L(time)
 *                      #define _MCU_T0_Delay30us(time)
 *                      void _MCU_LPM_Set_(void(*ptr)());
 *
 *                      void _UCA0_UART_Init_();
 *                      void _UCA0_UART_Write_(char* txBuff);
 *                      void _UCA0_UART_Read_(char* rxBuff);
 *
 *                      void _UCA1_UART_Init_();
 *                      void _UCA1_UART_Write_(char* txBuff);
 *                      void _UCA1_UART_Read_(char* rxBuff);
 *
 *                      void _UCB0_I2C_Init_();
 *                      void _UCB0_I2C_Address_(uchar address);
 *                      void _UCB0_I2C_Write_(uchar* writeData, uint dataL);
 *                      void _UCB0_I2C_Read_(uchar* readData, uint dataL);
 *
 *                      void _ADC12_AVCC_Init_();
 *                      void _ADC12_Power_Off_();
 *                      void _ADC12_Power_On_();
 */

#ifndef MSP430FR6989_LANCHPAD_H_
#define MSP430FR6989_LANCHPAD_H_

#include"msp430.h"
#include <stdio.h>

#define uchar unsigned char
#define uint unsigned int

// UART
#define D_UART_READmaxLength 20

// Lanchpad
// LED port operation
#define _LED_R_INIT 	P9DIR |= BIT7
#define _LED_R_on 	    P9OUT |= BIT7
#define _LED_R_off 	    P9OUT &= ~BIT7

#define _LED_L_INIT 	P1DIR |= BIT0
#define _LED_L_on 	    P1OUT |= BIT0
#define _LED_L_off 	    P1OUT &= ~BIT0

// special port set
#define _UCB0_I2C_PORTINIT\
	P1SEL1 &= ~(BIT6 | BIT7);\
	P1SEL0 |= BIT6 | BIT7;		// Configure P1.6/P1.7 for I2C
#define _ADC12_ADC_PORTINIT\
	P8SEL1 |= BIT4;\
	P8SEL0 |= BIT4;				// Configure P1.1 for ADC
#define _UCA1_UART_PORTINIT\
	P3SEL0 |= BIT4 | BIT5;\
	P3SEL1 &= ~(BIT4 | BIT5);	// Configure P3.4/P3.5 for USCI_A1 UART operation
#define _UCA0_UART_PORTINIT\
	P2SEL0 |= BIT0 | BIT1;\
	P2SEL1 &= ~(BIT0 | BIT1);	// Configure P2.0/P2.1 for USCI_A0 UART operation

// function
// MCU basic operation
void _MCU_OPeration_NULL_();
#define _LED_Blink_R(time) \
        {\
            _LED_R_on;\
            _MCU_T0_Delay30us(time);\
            _LED_R_off;\
        }
#define _LED_Blink_L(time) \
        {\
            _LED_L_on;\
            _MCU_T0_Delay30us(time);\
            _LED_L_off;\
        }
//
//Timer 1/32768s = 30.517us
#define _MCU_T0_Delay30us(time) \
        {\
            TA0CCTL0 = CCIE;\
            TA0CCR0 = time;\
            TA0CTL = TASSEL__ACLK | MC__UP; \
            TA0R = 0;\
            __bis_SR_register(LPM3_bits+GIE);\
        }
void _MCU_LPM_Set_(void(*ptr)());
// UCA0 UART operation
void _UCA0_UART_Init_();
void _UCA0_UART_Write_(char* txBuff);
void _UCA0_UART_Read_(char* rxBuff);
// UCA1 UART operation
void _UCA1_UART_Init_();
void _UCA1_UART_Write_(char* txBuff);
void _UCA1_UART_Read_(char* rxBuff);
// UCB0 I2C operation
void _UCB0_I2C_Init_();
void _UCB0_I2C_Address_(uchar address);
void _UCB0_I2C_Write_(uchar* writeData, uint dataL);
void _UCB0_I2C_Read_(uchar* readData, uint dataL);
// ADC12 operation
void _ADC12_AVCC_Init_();
void _ADC12_Power_Off_();
void _ADC12_Power_On_();

#endif /* MSP430FR6989_LANCHPAD_H_ */
