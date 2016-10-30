/*********************************************/
/* fmtg.h : Simple FM operator definitions   */
/* 2009/6/26 created by pcm1723              */
/*********************************************/
//
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
//
#ifndef fmtg_h
#define fmtg_h
//
// macro for PROGMEM access
//
#define READ_BYTE(x)  pgm_read_byte(&(x))
#define READ_WORD(x)  pgm_read_word(&(x))
#define READ_DWORD(x) pgm_read_dword(&(x))
//
// tick count per 1 ms
// fs = 15.625 kHz
//
#define SEQTICK1ms (16)
//
// EG accumulator minimum value for -96dB
//
#define EG_MIN_VAL (0x00FF0000L)
//
// EG accumulator undeflow detection mask for < -96dB
//
#define EG_UDF_MASK (0xFF000000L)
//
// shift amount from lb value to EG accumulator
//
#define EG_SHIFT (16)
//
// EG increment unit for DR=1
//
#define EG_INC_UNIT (0x00000195L)
//
// operator modulation shift amount
//
#define MOD_SHIFT (12)
//
// Operator mult code to actual multiplier conversion
//
extern const uint8_t PROGMEM mult_tab[];
//
// MIDInote to oct-keycode table
//
extern const uint8_t PROGMEM octkey[];
// 
// 512 point sine table in log_binary value
// only first 129 points (0..pi/2) for symmetry
//
extern const uint8_t PROGMEM slbtab[];
//
// convert log2 value to linear value (Q15)
// LIN = lb2lin[LB] = 2**(-LB/16)
//
extern const int16_t PROGMEM lb2lin[];
//
/*****************************************************/
/*                                                   */
/* 16-bit wide f-number table for MIDI lowest octave */
/* for OPERATOR_MULT = 0 (0.5x)                      */
/* 4 steps per semitone                              */
/* 100/4   = 25.000 cent step                        */
/* f_osc = 16.000 MHz, effective PWM period =  512   */
/* fs = 31.250 kHz, phase acc Qfmt = 25              */
/*                                                   */
/*****************************************************/
//
extern const uint16_t PROGMEM fnum4[];
//
// FM operator class definition
//
class FMop {
    private:
    public:
      uint32_t ph_acc; // phase accumulator
      uint32_t ph_inc; // phase increment
      uint32_t mod_in; // phase modulation input
      uint32_t eg_acc; // EG accumulator
      uint32_t eg_inc; // EG increment
      int16_t  op_out; // op output for FEEDBACK
      int16_t  op_out2; // op output for FEEDBACK
      uint8_t  TL;     // Total Level (0..63)
      uint8_t  DR;     // Decay Rate  (0..15)
      uint8_t  FB;     // feedback amount (0..7)
      uint8_t  MULT;   // frequency multiplier code (0..15)
// member functions
      FMop(void);      // constructor
      int16_t  calc(int32_t mod_in); // operator calcuration at fs rate
      void     eg_update(void);      // EG update at 1 ms rate
      void     mute(void);           // set sound level to EG_MIN_VAL
      void     gate_on (int8_t notenum, int8_t vel); // GATE ON
}; // class FMop
#endif
