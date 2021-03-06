/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 * 
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP430x21x1 Demo - OFIFG ISR for LF Failsafe Operation
//
//  Description: Toggle P1.0 using software timed by the WDT ISR. Toggle rate
//  is approximately 250ms based on 32768Hz ACLK when present. When the LFXT1
//  input signal faults during operation, the NMI ISR is entered and the fault
//  is serviced. During this time the LED will flash at a faster rate indicating
//  an ACLK fault. During this time the CPU is held in the NMI ISR.
//
//  ACLK = 32768 Hz, MCLK = SMCLK = ~1.16 MHz
//
//                MSP430F21x1
//             -----------------
//         /|\|              XIN|-
//          | |                 |  32.768kHz
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  H. Grewal / A. Dannenberg
//  Texas Instruments, Inc
//  June 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: V3.30A
//******************************************************************************
#include <msp430.h>

int main(void)
{
  WDTCTL = WDT_ADLY_250;                    // Set WDT interval to ~250ms from ACLK
  IE1 |= OFIE;                              // Enable osc fault int (NMI)
  IE1 |= WDTIE;                             // Enable WDT interrupt

  P1OUT = 0x00;
  P1DIR |= 0x01;

  while(1)
  {
    _BIS_SR(LPM3_bits+GIE);                 // Enter LPM3 with ints
  }
}

// NMI interrupt service routine
#pragma vector=NMI_VECTOR
__interrupt void osc_fault(void)
{
  volatile unsigned int i;

  do                                        // Loop until flag is clear
  {
    IFG1 &= ~OFIFG;                         // Clear fault flag
    for (i = 0xFFF; i; i--);                // Delay for crystal to start
    P1OUT ^= 0x01;                          // Toggle LED: rate is faster
  }
  while (IFG1 & OFIFG);                     // Test LF oscillator fault flag
  IE1 |= OFIE;                              // Re-enable osc fault int
}

// WDT interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P1OUT ^= 0x01;                            // Toggle LED
}
