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
//  MSP430x21x1 Demo - Flash In-System Programming w/ EEI, Copy SegC to SegD
//
//  Description: This program first erases flash seg D, then it increments all
//  values in seg D, then it erases segs A,B,C and copies D to those locations
//  The EEI bit is set for the Flash Erase Cycles. This does allow the Timer_A
//  Interrupts to be handled also during the Segment erase time.
//  MCLK = 1Mhz Calibrated Value
//  //* Set Breakpoint on NOP in the Mainloop to avoid Stressing Flash *//
//
//               MSP430F21x1
//            -----------------
//        /|\|              XIN|-
//         | |                 |
//         --|RST          XOUT|-
//           |                 |
//
//  Z. Albus / L. Westlund
//  Texas Instruments Inc.
//  December 2005
//  Built with CCE Version: 3.2.0 and IAR Embedded Workbench Version: 3.40A
//******************************************************************************

#include <msp430.h>

char  value;                                // 8-bit value to write to segment D

// Function prototypes
void write_SegD (char value);
void copy_D2A (void);
void copy_D2B (void);
void copy_D2C (void);

int main(void)
{
  volatile unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  if (CALBC1_1MHZ==0xFF)					// If calibration constants erased
  {											// do not load, trap CPU!!	
    while(1);                               
  }
  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO to 1MHz
  DCOCTL = CALDCO_1MHZ;                     // Set DCO step + modulation

  P1DIR |= 0x01;                            // P1.0 output
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 1000;
  TACTL = TASSEL_1 + MC_1;                  // ACLK, upmode

  WDTCTL = WDT_ADLY_1000;                   // WDT 1s, ACLK, interval timer
  IE1 |= WDTIE;                             // Enable WDT interrupt

  _EINT();                                  // enable interrupts

  FCTL2 = FWKEY + FSSEL0 + FN1;             // MCLK/3 for Flash Timing Generator
  value = 0;                                // initialize value

  while(1)                                  // Repeat forever
  {
    LPM3;
    write_SegD(value++);                    // Write segment D, increment value
    copy_D2A();                             // Copy segment D to A
    copy_D2B();                             // Copy segment D to B
    copy_D2C();                             // Copy segment D to C
  }
}

void write_SegD (char value)
{
  char *Flash_ptr;                          // Flash pointer
  unsigned int i;

  Flash_ptr = (char *) 0x1000;              // Initialize Flash pointer
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  FCTL3 = FWKEY;                            // Clear Lock bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash segment

  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<64; i++)
  {
    *Flash_ptr++ = value;                   // Write value to flash
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

// Warning: When this function is called, it MUST complete or
// DCO calibration constants will be lost
void copy_D2A (void)
{
  char *Flash_ptrA;                         // Segment A pointer
  char *Flash_ptrD;                         // Segment D pointer
  unsigned int i;
  char CAL_DATA[10];

  Flash_ptrA = (char *) 0x10F6;             // Initialize Flash segment A pointer
  for (i=0; i<10; i++)
  {
      CAL_DATA[i] = *Flash_ptrA++;          // Save DCO constants
  }

  Flash_ptrA = (char *) 0x10C0;             // Initialize Flash segment A pointer
  Flash_ptrD = (char *) 0x1000;             // Initialize Flash segment D pointer
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  FCTL3 = FWKEY + LOCKA;                    // Clear LOCK & LOCKA bits
  *Flash_ptrA = 0;                          // Dummy write to erase Flash segment A
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<54; i++)
  {
    *Flash_ptrA++ = *Flash_ptrD++;          // copy value segment D to segment A
  }

  for (i=0; i<10; i++)
  {
    *Flash_ptrA++ = CAL_DATA[i];            // re-flash DCO calibration data
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCKA + LOCK;             // Set LOCK & LOCKA bit
}

void copy_D2B (void)
{
  char *Flash_ptrB;                         // Segment B pointer
  char *Flash_ptrD;                         // Segment D pointer
  unsigned int i;

  Flash_ptrB = (char *) 0x1080;             // Initialize Flash segment B pointer
  Flash_ptrD = (char *) 0x1000;             // Initialize Flash segment D pointer
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  FCTL3 = FWKEY;                            // Clear LOCK bit
  *Flash_ptrB = 0;                          // Dummy write to erase Flash segment B
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<64; i++)
  {
    *Flash_ptrB++ = *Flash_ptrD++;          // copy value segment D to segment B
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

void copy_D2C (void)
{
  char *Flash_ptrC;                         // Segment C pointer
  char *Flash_ptrD;                         // Segment D pointer
  unsigned int i;

  Flash_ptrC = (char *) 0x1040;             // Initialize Flash segment C pointer
  Flash_ptrD = (char *) 0x1000;             // Initialize Flash segment D pointer
  FCTL1 = FWKEY + ERASE + EEI;              // Set Erase bit, allow interrupts
  FCTL3 = FWKEY;                            // Clear LOCK bit
  *Flash_ptrC = 0;                          // Dummy write to erase Flash segment C
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<64; i++)
  {
    *Flash_ptrC++ = *Flash_ptrD++;          // copy value segment D to segment C
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}

// Timer A0 interrupt service routine
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}

// Watchdog Timer interrupt service routine
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  LPM3_EXIT;
}
