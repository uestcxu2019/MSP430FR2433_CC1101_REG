/*
 * _msp430fr2433_lanchpad.c
 *  HR2018.11.29
 */
#include <PMM/_msp430fr2433.h>

/*******************************************************************************************
 * basic operation
 *******************************************************************************************/
void _MCU_OPeration_NULL_()
{
    __no_operation();
}

// low power set
void _MCU_LPM_Set_(void(*ptr)())
{
	P1OUT = 0x00;
    P2OUT = 0x00;
    P3OUT = 0x00;


    P1DIR = 0xFF;
    P2DIR = 0xFF;
    P3DIR = 0xFF;


    (*ptr)();

}


/*******************************************************************************************
 * MCU operation
 *******************************************************************************************/
// port interrupt set
/**************************************************************
P1OUT |= portBit;           // Pull-up resistor on P1x
P1REN |= portBit;           // Select pull-up mode for P1x
P1DIR &= ~portBit;   	    // Set all but P1x to output direction
P1IES |= portIES;          	// P1x Hi/Lo edge
P1IFG = 0;         			// Clear all P1 interrupt flags
P1IE |= portBit;           	// P1x interrupt enabled

// Port Interrupt vector
#pragma vector=PORT1_VECTOR
__interrupt void Port_1()
{
	...
}
**************************************************************/

// timer0 delay30us
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
	TA0CCTL0 &= ~CCIE;
	__bic_SR_register_on_exit(LPM3_bits + GIE);
}

/*******************************************************************************************
 * UCA0 UART operation
 *******************************************************************************************/
char *pTxData0;	// Tx data buff
char *pRxData0;	// Rx data Buff
uchar readFlag0,readLength0;	// Rx indicator variable
// UART init
void _UCA0_UART_Init_()
{
	_UCA0_UART_PORTINIT;			// UCA0 port initial

	// Configure USCI_A1 for UART mode
	UCA0CTLW0 = UCSWRST;               		// Put eUSCI in reset
	UCA0CTLW0 |= UCSSEL__SMCLK;         	// CLK = ACLK
	UCA0BR0 = 8;                          	// 115200 baud
	UCA0MCTLW |= 0xD600;
	UCA0BR1 = 0;
	UCA0CTL1 &= ~UCSWRST;           		// Initialize eUSCI
}

// UART write(TX)
void _UCA0_UART_Write_(char* txBuff)
{
	UCA0IE |= UCTXIE;				// enable the TXIE

	pTxData0 = txBuff;				// write buff
	__bis_SR_register(LPM1_bits + GIE);

	while (UCA0IE & UCTXIE);
}

// UART read(RX)
void _UCA0_UART_Read_(char* rxBuff)
{
	readFlag0 = 0;
	readLength0 = 0;

	UCA0IE |= UCRXIE;
	pRxData0 = rxBuff;

	__bis_SR_register(LPM1_bits + GIE);

	while (UCA0IE & UCRXIE);
}

// UART A1 vector
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  switch(__even_in_range(UCA0IV,4))
  {
  case 0:break;                             	// Vector 0 - no interrupt
  case 2:										// Vector 2 - RXIFG
	  *pRxData0 = UCA0RXBUF;

  	  if(*pRxData0 == '#' | readFlag0 == 1)		// start?
  	  {
  		  readFlag0 = 1;
  		  if(*pRxData0 == '$' | readLength0 >= D_UART_READmaxLength) 	// out of range?
  		  {
  			  UCA0IE &= ~UCRXIE;
  			  __bic_SR_register_on_exit(LPM1_bits + GIE);			// Exit to active CPU
  		  }
  		  else
  		  {
  			  pRxData0++;
  			  readLength0++;
  		  }
  	  }
	  break;

  case 4:										// Vector 4 - TXIFG
	  UCA0TXBUF = *(pTxData0++);
	  if (*pTxData0 == '$')
	  {
		  UCA0IE &= ~UCTXIE;
	  	  __bic_SR_register_on_exit(LPM1_bits + GIE);	// Exit active CPU
	  }
	  break;
  default: break;
  }
}

/*******************************************************************************************
 * UCA1 UART operation
 *******************************************************************************************/
char *pTxData1;	// Tx data buff
char *pRxData1;	// Rx data Buff
uchar readFlag1,readLength1;	// Rx indicator variable
// UART init
void _UCA1_UART_Init_()
{
	_UCA1_UART_PORTINIT;			// UCA1 port initial

	// Configure USCI_A1 for UART mode
	UCA1CTLW0 = UCSWRST;               		// Put eUSCI in reset
	UCA1CTLW0 |= UCSSEL__SMCLK;         	// CLK = ACLK
	UCA1BR0 = 8;                          	// 115200 baud
	UCA1MCTLW |= 0xD600;
	UCA1BR1 = 0;
	UCA1CTL1 &= ~UCSWRST;           		// Initialize eUSCI
}

// UART write(TX)
void _UCA1_UART_Write_(char* txBuff)
{
	UCA1IE |= UCTXIE;				// enable the TXIE

	pTxData1 = txBuff;				// write buff
	__bis_SR_register(LPM1_bits + GIE);

	while (UCA1IE & UCTXIE);
}

// UART read(RX)
void _UCA1_UART_Read_(char* rxBuff)
{
	readFlag1 = 0;
	readLength1 = 0;

	UCA1IE |= UCRXIE;
	pRxData1 = rxBuff;

	__bis_SR_register(LPM1_bits + GIE);

	while (UCA1IE & UCRXIE);
}

// UART A1 vector
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
  switch(__even_in_range(UCA1IV,4))
  {
  case 0:break;                             	// Vector 0 - no interrupt
  case 2:										// Vector 2 - RXIFG
	  *pRxData1 = UCA1RXBUF;

  	  if(*pRxData1 == '#' | readFlag1 == 1)		// start?
  	  {
  		  readFlag1 = 1;
  		  if(*pRxData1 == '$' | readLength1 >= D_UART_READmaxLength) 	// out of range?
  		  {
  			  UCA1IE &= ~UCRXIE;
  			  __bic_SR_register_on_exit(LPM1_bits + GIE);			// Exit to active CPU
  		  }
  		  else
  		  {
  			  pRxData1++;
  			  readLength1++;
  		  }
  	  }
	  break;

  case 4:										// Vector 4 - TXIFG
	  UCA1TXBUF = *(pTxData1++);
	  if (*pTxData1 == '$')
	  {
		  UCA1IE &= ~UCTXIE;
	  	  __bic_SR_register_on_exit(LPM1_bits + GIE);	// Exit active CPU
	  }


	  break;
  default: break;
  }
}

/*******************************************************************************************
 * UCB0 I2C operation
 *******************************************************************************************/
uint ReadByteCtr,WriteByteCtr;
uchar *pWriteData,*pReadData;

// UCB0 I2C init
void _UCB0_I2C_Init_()
{
	_UCB0_I2C_PORTINIT;								// Assign I2C pins to USCI_B0
	UCB0CTLW0  |= UCSWRST;                      	// Enable SW reset
	UCB0CTLW0  |= UCMODE_3 + UCMST + UCSSEL__SMCLK; // I2C, Master, SMCLK
	UCB0BRW = 0x08;                            		// baudrate = SMCLK / 4
	UCB0CTL1 &= ~UCSWRST;                     		// Clear SW reset, resume operation
}

// I2C slave address
void _UCB0_I2C_Address_(uchar address)
{
	UCB0I2CSA = address;							// set slave device address
}

// I2C Write data with a length of dataL
void _UCB0_I2C_Write_(uchar* writeData, uint dataL)
{
	UCB0IE |= UCTXIE0 + UCNACKIE;				// Enable TX interrupt

	pWriteData = (uchar *)writeData;      		// TX array start address
	                                            // Place breakpoint here to see each
	                                            // transmit operation.
	WriteByteCtr = dataL;              			// Load TX byte counter

	UCB0CTLW0  |= UCTR + UCTXSTT;             	// I2C TX, start condition

	__bis_SR_register(LPM0_bits + GIE);     	// Enter LPM0, enable interrupts
												// Remain in LPM0 until all data is Tx'd

	while (UCB0CTLW0  & UCTXSTP);             	// Ensure stop condition got sent
	UCB0IE &= ~(UCTXIE0 + UCNACKIE);			// Disable TX interrupt
}

// I2C Raed data with a length of dataL
void _UCB0_I2C_Read_(uchar* readData, uint dataL)
{
	UCB0IE |= UCRXIE0;						// Enable RX interrupt

	pReadData = readData;    					// Start of RX buffer
	ReadByteCtr = dataL;                   	// Load RX byte counter

	while (UCB0CTLW0  & UCTXSTP);			// Ensure stop condition got sent

	UCB0CTLW0  &= ~UCTR;					// I2C Rx
	UCB0CTLW0  |= UCTXSTT;                  // I2C start condition
	while (UCB0CTLW0  & UCTXSTT);

	if(dataL == 1)
		UCB0CTLW0  |= UCTXSTP;            	// Generate I2C stop condition

	__bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, enable interrupts
	__no_operation();						// Remain in LPM0 until all data is Rx'd

	UCB0IE &= ~UCRXIE0;						// Disable RX interrupt
}

// UCB0 I2C interrupt function
#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
{
	switch(__even_in_range(UCB0IV, USCI_I2C_UCBIT9IFG))
	{
		case USCI_NONE:          break;         // Vector 0: No interrupts
	    case USCI_I2C_UCALIFG:   break;         // Vector 2: ALIFG

	    case USCI_I2C_UCNACKIFG:                // Vector 4: NACKIFG
	      UCB0CTLW0 |= UCTXSTT;                 // resend start if NACK
	      break;

	    case USCI_I2C_UCSTTIFG:  break;         // Vector 6: STTIFG
	    case USCI_I2C_UCSTPIFG:  break;         // Vector 8: STPIFG
	    case USCI_I2C_UCRXIFG3:  break;         // Vector 10: RXIFG3
	    case USCI_I2C_UCTXIFG3:  break;         // Vector 12: TXIFG3
	    case USCI_I2C_UCRXIFG2:  break;         // Vector 14: RXIFG2
	    case USCI_I2C_UCTXIFG2:  break;         // Vector 16: TXIFG2
	    case USCI_I2C_UCRXIFG1:  break;         // Vector 18: RXIFG1
	    case USCI_I2C_UCTXIFG1:  break;         // Vector 20: TXIFG1

	    case USCI_I2C_UCRXIFG0:					// Vector 22: RXIFG0
	    	ReadByteCtr--;
	    	*pReadData = UCB0RXBUF;            	// Move final RX data to pRxData1// Decrement RX byte counter
	    	if (ReadByteCtr)
	    	{
	    		pReadData++;               		// Move RX data to address pRxData1
	    		if (ReadByteCtr == 1)        		// Only one byte left?
	    			UCB0CTLW0 |= UCTXSTP;      	// Generate I2C stop condition
	    	}
	    	else
	    		__bic_SR_register_on_exit(LPM0_bits + GIE);		// Exit active CPU
	    	break;

	    case USCI_I2C_UCTXIFG0:                 // Vector 24: TXIFG0
			if (WriteByteCtr)              		// Check TX byte counter
			{
				UCB0TXBUF = *pWriteData++;       	// Load TX buffer
				WriteByteCtr--;                	// Decrement TX byte counter
			}
			else
			{
				UCB0CTLW0 |= UCTXSTP;           // I2C stop condition
				UCB0IFG &= ~UCTXIFG;            // Clear USCI_B0 TX int flag
				__bic_SR_register_on_exit(LPM0_bits + GIE); 	// Exit LPM0
			}
			break;

	    default: break;
	}
}

/*******************************************************************************************
 * ADC12 operation
 *******************************************************************************************/
unsigned int ADC12CTL0_0,ADC12CTL0_1;
unsigned int ADC12CTL1_0,ADC12CTL1_1;
unsigned int ADC12CTL2_0,ADC12CTL2_1;
// ADC12 AVCC init
/********************************************************************************
 xu  mod begin
********************************************************************************/
#if 0
void _ADC12_AVCC_Init_()
{
    // ADC12 port init
	_ADC12_ADC_PORTINIT;

	// ADC12 close record
    ADC12CTL0_0 = ADC12CTL0;
    ADC12CTL1_0 = ADC12CTL1;
    ADC12CTL2_0 = ADC12CTL2;

    // Configure ADC12
    ADC12CTL0_1 = ADC12SHT0_2 | ADC12ON;	// Sampling time, S&H=16, ADC12 on
    ADC12CTL1_1 = ADC12SHP;           	// Use sampling timer
    ADC12CTL2_1 |= ADC12RES_2;         	// 12-bit conversion results
    ADC12MCTL0 |= ADC12INCH_7;         	// A7 ADC input select; Vref=AVCC
}


// ADC12 close
void _ADC12_Power_Off_()
{
    ADC12CTL0 &= ~(ADC12ENC + ADC12SC);
    ADC12CTL0 = ADC12CTL0_0;
    ADC12CTL1 = ADC12CTL1_0;
    ADC12CTL2 = ADC12CTL2_0;
}

// ADC12 open
void _ADC12_Power_On_()
{
    ADC12CTL0 = ADC12CTL0_1;
    ADC12CTL1 = ADC12CTL1_1;
    ADC12CTL2 = ADC12CTL2_1;
    ADC12CTL0 |= (ADC12ENC + ADC12SC);
}

#endif
/********************************************************************************
 xu mod end
********************************************************************************/
