<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en"><head>
<meta http-equiv="content-type" content="text/html; charset=UTF-8">
<title>msp430.h</title>
<style type="text/css">
.enscript-comment { font-style: italic; color: rgb(178,34,34); }
.enscript-function-name { font-weight: bold; color: rgb(0,0,255); }
.enscript-variable-name { font-weight: bold; color: rgb(184,134,11); }
.enscript-keyword { font-weight: bold; color: rgb(160,32,240); }
.enscript-reference { font-weight: bold; color: rgb(95,158,160); }
.enscript-string { font-weight: bold; color: rgb(188,143,143); }
.enscript-builtin { font-weight: bold; color: rgb(218,112,214); }
.enscript-type { font-weight: bold; color: rgb(34,139,34); }
.enscript-highlight { text-decoration: underline; color: 0; }
</style>
</head>
<body id="top">
<h1 style="margin:8px;" id="f1">msp430.h&nbsp;&nbsp;&nbsp;<span style="font-weight: normal; font-size: 0.5em;">[<a href="https://www.opensource.apple.com/source/gdb/gdb-1822/src/include/opcode/msp430.h?txt">plain text</a>]</span></h1>
<hr>
<div></div>
<pre><span class="enscript-comment">/* Opcode table for the TI MSP430 microcontrollers

   Copyright 2002, 2004 Free Software Foundation, Inc.
   Contributed by Dmitry Diky &lt;<a href="mailto:diwil@mail.ru">diwil@mail.ru</a>&gt;
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.  */</span>

#<span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">__MSP430_H_</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">__MSP430_H_</span>

<span class="enscript-type">struct</span> msp430_operand_s
{
  <span class="enscript-type">int</span> ol;	<span class="enscript-comment">/* Operand length words.  */</span>
  <span class="enscript-type">int</span> am;	<span class="enscript-comment">/* Addr mode.  */</span>
  <span class="enscript-type">int</span> reg;	<span class="enscript-comment">/* Register.  */</span>
  <span class="enscript-type">int</span> mode;	<span class="enscript-comment">/* Pperand mode.  */</span>
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">OP_REG</span>		0
#<span class="enscript-reference">define</span> <span class="enscript-variable-name">OP_EXP</span>		1
#<span class="enscript-reference">ifndef</span> <span class="enscript-variable-name">DASM_SECTION</span>
  expressionS	exp;
#<span class="enscript-reference">endif</span>
};

#<span class="enscript-reference">define</span> <span class="enscript-variable-name">BYTE_OPERATION</span>  (1 &lt;&lt; 6)  <span class="enscript-comment">/* Byte operation flag for all instructions.  */</span>

<span class="enscript-type">struct</span>  msp430_opcode_s
{
  <span class="enscript-type">char</span> *name;
  <span class="enscript-type">int</span> fmt;
  <span class="enscript-type">int</span> insn_opnumb;
  <span class="enscript-type">int</span> bin_opcode;
  <span class="enscript-type">int</span> bin_mask;
};

#<span class="enscript-reference">define</span> <span class="enscript-function-name">MSP_INSN</span>(name, size, numb, bin, mask) { #name, size, numb, bin, mask }

<span class="enscript-type">static</span> <span class="enscript-type">struct</span> msp430_opcode_s msp430_opcodes[] = 
{
  MSP_INSN (and,   1, 2, 0xf000, 0xf000),
  MSP_INSN (inv,   0, 1, 0xe330, 0xfff0),
  MSP_INSN (xor,   1, 2, 0xe000, 0xf000),
  MSP_INSN (setz,  0, 0, 0xd322, 0xffff),
  MSP_INSN (setc,  0, 0, 0xd312, 0xffff),
  MSP_INSN (eint,  0, 0, 0xd232, 0xffff),
  MSP_INSN (setn,  0, 0, 0xd222, 0xffff),
  MSP_INSN (bis,   1, 2, 0xd000, 0xf000),
  MSP_INSN (clrz,  0, 0, 0xc322, 0xffff),
  MSP_INSN (clrc,  0, 0, 0xc312, 0xffff),
  MSP_INSN (dint,  0, 0, 0xc232, 0xffff),
  MSP_INSN (clrn,  0, 0, 0xc222, 0xffff),
  MSP_INSN (bic,   1, 2, 0xc000, 0xf000),
  MSP_INSN (bit,   1, 2, 0xb000, 0xf000),
  MSP_INSN (dadc,  0, 1, 0xa300, 0xff30),
  MSP_INSN (dadd,  1, 2, 0xa000, 0xf000),
  MSP_INSN (tst,   0, 1, 0x9300, 0xff30),
  MSP_INSN (cmp,   1, 2, 0x9000, 0xf000),
  MSP_INSN (decd,  0, 1, 0x8320, 0xff30),
  MSP_INSN (dec,   0, 1, 0x8310, 0xff30),
  MSP_INSN (sub,   1, 2, 0x8000, 0xf000),
  MSP_INSN (sbc,   0, 1, 0x7300, 0xff30),
  MSP_INSN (subc,  1, 2, 0x7000, 0xf000),
  MSP_INSN (adc,   0, 1, 0x6300, 0xff30),
  MSP_INSN (rlc,   0, 2, 0x6000, 0xf000),
  MSP_INSN (addc,  1, 2, 0x6000, 0xf000),
  MSP_INSN (incd,  0, 1, 0x5320, 0xff30),
  MSP_INSN (inc,   0, 1, 0x5310, 0xff30),
  MSP_INSN (rla,   0, 2, 0x5000, 0xf000),
  MSP_INSN (add,   1, 2, 0x5000, 0xf000),
  MSP_INSN (nop,   0, 0, 0x4303, 0xffff),
  MSP_INSN (clr,   0, 1, 0x4300, 0xff30),
  MSP_INSN (ret,   0, 0, 0x4130, 0xff30),
  MSP_INSN (pop,   0, 1, 0x4130, 0xff30),
  MSP_INSN (br,    0, 3, 0x4000, 0xf000),
  MSP_INSN (mov,   1, 2, 0x4000, 0xf000),
  MSP_INSN (jmp,   3, 1, 0x3c00, 0xfc00),
  MSP_INSN (jl,    3, 1, 0x3800, 0xfc00),
  MSP_INSN (jge,   3, 1, 0x3400, 0xfc00),
  MSP_INSN (jn,    3, 1, 0x3000, 0xfc00),
  MSP_INSN (jc,    3, 1, 0x2c00, 0xfc00),
  MSP_INSN (jhs,   3, 1, 0x2c00, 0xfc00),
  MSP_INSN (jnc,   3, 1, 0x2800, 0xfc00),
  MSP_INSN (jlo,   3, 1, 0x2800, 0xfc00),
  MSP_INSN (jz,    3, 1, 0x2400, 0xfc00),
  MSP_INSN (jeq,   3, 1, 0x2400, 0xfc00),
  MSP_INSN (jnz,   3, 1, 0x2000, 0xfc00),
  MSP_INSN (jne,   3, 1, 0x2000, 0xfc00),
  MSP_INSN (reti,  2, 0, 0x1300, 0xffc0),
  MSP_INSN (call,  2, 1, 0x1280, 0xffc0),
  MSP_INSN (push,  2, 1, 0x1200, 0xff80),
  MSP_INSN (sxt,   2, 1, 0x1180, 0xffc0),
  MSP_INSN (rra,   2, 1, 0x1100, 0xff80),
  MSP_INSN (swpb,  2, 1, 0x1080, 0xffc0),
  MSP_INSN (rrc,   2, 1, 0x1000, 0xff80),
  <span class="enscript-comment">/* Simple polymorphs.  */</span>
  MSP_INSN (beq,   4, 0, 0, 0xffff),
  MSP_INSN (bne,   4, 1, 0, 0xffff),
  MSP_INSN (blt,   4, 2, 0, 0xffff),
  MSP_INSN (bltu,  4, 3, 0, 0xffff),
  MSP_INSN (bge,   4, 4, 0, 0xffff),
  MSP_INSN (bgeu,  4, 5, 0, 0xffff),
  MSP_INSN (bltn,  4, 6, 0, 0xffff),
  MSP_INSN (jump,  4, 7, 0, 0xffff),
  <span class="enscript-comment">/* Long polymorphs.  */</span>
  MSP_INSN (bgt,   5, 0, 0, 0xffff),
  MSP_INSN (bgtu,  5, 1, 0, 0xffff),
  MSP_INSN (bleu,  5, 2, 0, 0xffff),
  MSP_INSN (ble,   5, 3, 0, 0xffff),

  <span class="enscript-comment">/* End of instruction set.  */</span>
  { NULL, 0, 0, 0, 0 }
};

#<span class="enscript-reference">endif</span>
</pre>
<hr>
</body></html>