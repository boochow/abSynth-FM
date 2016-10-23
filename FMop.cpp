/*********************************************/
/* FMop.cpp: Simple FM operator definitions  */
/* 2009/6/26 created by pcm1723              */
/*********************************************/
//
#include "fmtg.h"
//
// constructor
//
FMop::FMop(void)
{
  ph_acc  = 0; // clear phase acc
  eg_acc  = 0; // clear EG acc
  ph_inc  = 0; // clear phase acc inc
  eg_inc  = 0; // clear EG acc inc
  op_out  = 0; // clear prev. output
  op_out2 = 0; // clear prev. output
  MULT = 1;
  DR   = 0; 
  TL   = 0;
  FB   = 0; // initalize tone params  
} // FMop::FMop()

//
// Operator GATE ON
//
void FMop::gate_on(int8_t nn, int8_t vel)
{
  register uint8_t oct, key;
  uint32_t inc;
  key  = READ_WORD(octkey[nn >> 2]);  // octave-key code conversion
  oct  = (key >> 4);               // extract octave code
  key  = ((0x0F & key) | (0x03 & nn)); // combine key code
  inc  = READ_WORD(fnum4[key << 2]); // calc phase increment value
  inc *= READ_BYTE(mult_tab[MULT]); // multiples
  ph_inc = (inc << oct); // apply octave shift
  ph_acc = 0;  // start from zero
  op_out = 0;  // clear previous output
  op_out = 2;  // clear previous output
  eg_acc = ((uint32_t)TL << (EG_SHIFT+1)); // fast attack
  if (0 == DR) eg_inc = 0; // Decay rate = 0 means no change
  else {
    eg_inc = (EG_INC_UNIT << DR); // calculate decay rate
  } // if (0 == DR) ... else ...
} // void FMop::note_on()
//
// EG update at 1 ms rate
//
void FMop::eg_update(void)
{
  if (EG_MIN_VAL > eg_acc) { // not too small
    eg_acc += eg_inc; // update EG accumulator
    if (EG_UDF_MASK & eg_acc) { // if too small
      eg_acc = EG_MIN_VAL; // replace by minimum value
    } // if (0xFF ...
  } // if (0x00 ...
} // void FMop::eg_update()
//
// Operator calcuration at sampling rate
//
int16_t FMop::calc(int32_t mod_in)
{
  register uint8_t ix;
  register int16_t si;
  if (FB) { // feedback enabled ?
    mod_in += ((int32_t)((op_out > 1) + (op_out2 > 1)) << (4+FB));
  } // if (FB)
  mod_in += ph_acc; // apply modulation input
  ph_acc += ph_inc; // phase accumulator update
  ix = (0x7F  & (mod_in >> 16)); // sine index
  if (0x00800000L & mod_in) ix = 0x80 - ix;  // flip direcion
  si = READ_BYTE(slbtab[ix]); // log binary value of sine
  si += (0xFF & (eg_acc >> EG_SHIFT));  // apply EG scaling
  if (0xFF00 & si) si = 0xFF;     // saturate to min level if too small
  si = READ_WORD(lb2lin[0xFF & si]); // get linear magnitude
  op_out2 = op_out; // remember last op output
  if (0x01000000L & mod_in) { // extract sign bit of sine wave
    op_out = -si; // negative
  } else {
    op_out =  si; // positive
  } // if (0x ...
    return(op_out); 
} // int16_t FMop::calc()
