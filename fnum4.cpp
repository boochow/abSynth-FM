/*****************************************************/
/*                                                   */
/* 16-bit wide f-number table for MIDI lowest octave */
/* for OPERATOR_MULT = 0 (0.5x)                      */
/* 4 steps per semitone                              */
/* 100/4   = 25.000 cent step                        */
/* f_osc = 16.000 MHz, effective PWM period = 1024   */
/* fs = 15.625 kHz, phase acc Qfmt = 25              */
/*                                                   */
/*****************************************************/
//
#include "fmtg.h"
//
#if (F_CPU == 16000000UL)
//
const PROGMEM prog_uint16_t fnum4[48] = {
/* ****  C  ( 4.0880 Hz) **** */
   0x224b, 0x22ca, 0x234c, 0x23cf,
/* ****  C# ( 4.3311 Hz) **** */
   0x2455, 0x24dc, 0x2565, 0x25f0,
/* ****  D  ( 4.5886 Hz) **** */
   0x267e, 0x270d, 0x279e, 0x2832,
/* ****  D# ( 4.8615 Hz) **** */
   0x28c8, 0x2960, 0x29fa, 0x2a96,
/* ****  E  ( 5.1502 Hz) **** */
   0x2b34, 0x2bd5, 0x2c79, 0x2d1e,
/* ****  F  ( 5.4566 Hz) **** */
   0x2dc6, 0x2e71, 0x2f1e, 0x2fcd,
/* ****  F# ( 5.7812 Hz) **** */
   0x307f, 0x3134, 0x31eb, 0x32a5,
/* ****  G  ( 6.1248 Hz) **** */
   0x3361, 0x3421, 0x34e3, 0x35a8,
/* ****  G# ( 6.4890 Hz) **** */
   0x366f, 0x373a, 0x3808, 0x38d8,
/* ****  A  ( 6.8750 Hz) **** */
   0x39ac, 0x3a83, 0x3b5d, 0x3c3a,
/* ****  A# ( 7.2839 Hz) **** */
   0x3d1a, 0x3dfd, 0x3ee4, 0x3fce,
/* ****  B  ( 7.7169 Hz) **** */
   0x40bc, 0x41ad, 0x42a2, 0x439a
}; // const PROGMEM prog_uint16_t fnum4[48]
#endif
