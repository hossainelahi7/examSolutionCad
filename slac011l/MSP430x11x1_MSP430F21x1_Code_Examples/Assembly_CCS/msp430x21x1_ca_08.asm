; --COPYRIGHT--,BSD_EX
;  Copyright (c) 2012, Texas Instruments Incorporated
;  All rights reserved.
; 
;  Redistribution and use in source and binary forms, with or without
;  modification, are permitted provided that the following conditions
;  are met:
; 
;  *  Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
; 
;  *  Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
; 
;  *  Neither the name of Texas Instruments Incorporated nor the names of
;     its contributors may be used to endorse or promote products derived
;     from this software without specific prior written permission.
; 
;  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
;  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
;  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
;  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
;  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
;  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
;  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
;  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
;  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
;  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
; 
; ******************************************************************************
;  
;                        MSP430 CODE EXAMPLE DISCLAIMER
; 
;  MSP430 code examples are self-contained low-level programs that typically
;  demonstrate a single peripheral function or device feature in a highly
;  concise manner. For this the code may rely on the device's power-on default
;  register values and settings such as the clock configuration and care must
;  be taken when combining code from several examples to avoid potential side
;  effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
;  for an API functional library-approach to peripheral configuration.
; 
; --/COPYRIGHT--
;*****************************************************************************
;   MSP430x21x1 Demo - Comp_A, Millivolt Meter
;
;   Description: This program demonstrates how to implement an MSP430F21x1/
;   MSP430F11x1 millivolt meter using Comparator_A. The measurement result can
;   be readout of variable 'ADCRESULT' using the watch window.
;   ACLK = n/a, MCLK = SMCLK = DCO=8MHZ
;
;             MSP430F21x1/11x1
;            -----------------
;       /|\ |              XIN|-
;        |  |                 |
;        ---|RST          XOUT|-
;           |                 |
;    AIN--->|P2.4             |
;           |                 |
;    +-10k--|P2.0             |
;    |      |                 |
;    +----- |P2.3             |
;    |      |                 |
;   ===2.2  |                 |
;    |      |                 |
;    ------ |VSS              |
;
;
;  F.  Chen
;  Texas Instruments Inc.
;  November 2012
;  Built with Code Composer Studio Version: 5.2.1
;*****************************************************************************
 .cdecls C,LIST,  "msp430.h"

VCC_VALUE   .equ   2980
ADCRESULT .equ R4
Result    .equ R5
Counter   .equ R7
Result2   .equ R9
;------------------------------------------------------------------------------
            .text                           ; Program Start
;------------------------------------------------------------------------------
RESET       mov.w   #300h,SP                ; Initialize stackpointer
            mov.w   #WDTPW+WDTHOLD,&WDTCTL  ; Stop WDT
            mov.b   #020h,&P2OUT            ; P2.5 high
            mov.b   #021h,&P2DIR            ; P2.0 = DAC, P2.5 powers pot
            mov.b   #P2CA0+P2CA1,&CACTL2    ; Setup CA, P2.3+ P2.4-
			cmp.b   #0xFF,&CALBC1_8MHZ      ; Check calibration constant
            jne     Load                    ; if not erased, load.        
Trap        jmp     Trap                    ; if erased do not load, trap CPU!
Load		clr.b   &DCOCTL                 ; Select lowest DCOx and MODx settings
			mov.b   &CALBC1_8MHZ,&BCSCTL1   ;
            mov.b   &CALDCO_8MHZ,&DCOCTL    ; Set DCO

Mainloop    call    #Meas_ADC
            mov.w   Result,ADCRESULT
            nop
            jmp     Mainloop

;------------------------------------------------------------------------------
Meas_ADC;
;------------------------------------------------------------------------------
            mov.b   #CAON,&CACTL1           ; Comparator on
            call    #Meas_ADC2              ; Do 1st ADC conversion
            mov.w   Result2,Result
            bis.b   #CAEX,&CACTL1           ; Invert comparator terminals
            call    #Meas_ADC2              ; 2nd ADC, add inverted result
            add.w   Result2,Result
            clr.b   &CACTL1                 ; Comparator off
            ret                             ;
                                            ;
;------------------------------------------------------------------------------
Meas_ADC2;
;------------------------------------------------------------------------------
            mov.w   #VCC_VALUE,R8
            rra.w   R8
            mov.w   R8,Counter
            clr.w   Result2
            bis.b   #01h,&P2OUT             ; .set power to capacitor
test        bit.b   #01h,&CACTL2            ; Wait for CAOUT to get .set
            jnc     test
tstCA       bit.b   #01h,&CACTL2            ; Comparator high/low?
            jnc     itslow
            bic.b   #01h,&P2OUT             ; Remove power if high
            jmp     whloop
itslow      bis.b   #01h,&P2OUT             ; Set power if low
            inc.w   Result2                 ; Measure the 'ON' time
            nop
whloop      dec.w   Counter                 ; Decrement and loop
            jnz     tstCA                   ;
            bic.b   #01h,&P2OUT             ; Remove power from cap
            ret                             ;
;------------------------------------------------------------------------------
;           Interrupt Vectors
;------------------------------------------------------------------------------
            .sect ".reset"                  ; MSP430 RESET Vector
            .short  RESET                   ;
            .end
