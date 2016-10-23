/***************************************/
/* FMmelody : FM synthesis version of  */
/* Arduino sample sketch "Melody"      */
/*                                     */
/* PWM analog wave output assigned for */
/* Digital 9 pin by default            */
/*                                     */
/* Serial 16-bit Non-oversampling      */
/* digital audio DAC supported         */
/*                                     */
/* 2009/6/26 created by PCM1723        */
/***************************************/
//
// uncomment following "#define" 
// to enable Non-oversampling 16-bit DAC
//
//#define USE_NOSDAC
//
#include <inttypes.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include "fmtg.h"
#ifdef USE_NOSDAC
  #include "NosDAC.h"
#else
  #include "PWMDAC.h"
#endif
#include "notedefs.h"

//
// sequence data
//
#define BPM (120)

int8_t seq_length  = 15; // the number of notes

int8_t notes[] = {M_C5, M_C5, M_G5, M_G5, 
                  M_A5, M_A5, M_G5, 
                  M_F5, M_F5, M_E5, M_E5, 
                  M_D5, M_D5, M_C5, 
                  M_REST};
                  
int8_t beats[] = {L_4,  L_4,  L_4,  L_4,
                  L_4,  L_4,  L_2, 
                  L_4,  L_4,  L_4,  L_4,
                  L_4,  L_4,  L_2,  
                  L_1};
//
// calculate unit duration for 96th note
//
int16_t unit_dur = (((4883/BPM)+1)>>1);                 
//
//#ifdef USE_NOSDAC
//  uint8_t led_pin =  8; // Idle LED
//#else
//  uint8_t led_pin = 13; // Idle LED
//#endif
volatile int16_t dac_l, dac_r;  // DAC buffer
volatile uint8_t fsflag = 0;  // fs timing flag
FMop op[2]; // instantiate 2 FM operators
//
// instrument voice param array
//
#define NUM_INST (7)

const int8_t PROGMEM v_data[NUM_INST][6] = {
//
// +---- OP0 ----+  OP1 oct
// FB MULT  TL  DR  DR  shift
  { 5,  1,  32,  1,  2,  0}, // Acoustic Piano
  { 7,  5,  44,  5,  2,  0}, // Electric Piano
  { 5,  9,  32,  2,  2,  0}, // Tubular Bells
  { 0,  8,  34,  8,  7,  0}, // Marimba
  { 7,  3,  32,  1,  2,  0}, // Jazz Guitar
  { 4,  1,  16,  1,  2, -2}, // Finger Bass
  { 4,  1,   8,  3,  2, -2}, // Slap Bass
}; // const PROGMEM prog_int8_t v_data[][]
//
// setup voice parameter for the program number
//
void program_change(FMop op[2], uint8_t pno) 
{
  op[0].FB   = READ_BYTE(v_data[pno][0]);
  op[0].MULT = READ_BYTE(v_data[pno][1]);
  op[0].TL   = READ_BYTE(v_data[pno][2]);
  op[0].DR   = READ_BYTE(v_data[pno][3]);
  op[1].DR   = READ_BYTE(v_data[pno][4]);
} // void program_change()

void setup_synth(FMop op[2]) 
{
  PWMDAC_setup(1);
  program_change(op, 0); // default instrument
} // void setup() 
//
//void update_seq2(FMop op[2]) {
//  static uint8_t seq = 0; // sequencer index
//  static int8_t  nofs = 0; // note offset
//  static int16_t dur_cnt = 0; // duration counter
//
//        if (0 > (--dur_cnt)){ // note duration over ?
//        if (M_REST < notes[seq]) { // is it a note ? (skip if rest)
//          for (uint8_t i = 0; i < 2; i++) { // GATE ON each OP for the note
//            op[i].gate_on(notes[seq]+nofs, 127);
//          } // for (i
//        } // if (M_REST ...
//        dur_cnt = beats[seq] * unit_dur - 1; // calculate unit_dur of this note
//        if (seq_length <= (++seq)) seq = 0;  // rewind to top if the last note
//      } // if (0 > (--dur_cnt)) ...
//}

bool update_synth(FMop op[2]) 
{ 
  static int16_t ww  = 0; // wave work
//  static uint8_t seq = 0; // sequencer index
//  static uint8_t pno = 0; // program number
//  static int8_t  nofs = 0; // note offset
  static int8_t  tick1ms = SEQTICK1ms-1; // 1ms tick counter
//  static int16_t dur_cnt = 0; // duration counter
//  
  if (fsflag) { // wave output timing
    dac_l = ww;   // update DAC Lch
    fsflag = 0; // reset flag
    if (0 > (--tick1ms)) { // 1ms rate processing
      tick1ms = SEQTICK1ms-1;  // reset 1ms tick count
      op[0].eg_update(); // EG update for mod.
      op[1].eg_update(); // EG update for carr.
//      update_seq2(op);
//      if (0 > (--dur_cnt)){ // note duration over ?
//        if (M_REST < notes[seq]) { // is it a note ? (skip if rest)
//          for (uint8_t i = 0; i < 2; i++) { // GATE ON each OP for the note
//            op[i].gate_on(notes[seq]+nofs, 127);
//          } // for (i
//        } // if (M_REST ...
//        dur_cnt = beats[seq] * unit_dur - 1; // calculate unit_dur of this note
//        if (seq_length <= (++seq)) seq = 0;  // rewind to top if the last note
//      } // if (0 > (--dur_cnt)) ...
    } // if (0 > (--tick1ms)) ...
// Operator calculation for series alghrithm
    ww = op[0].calc(0);  // modulator
    ww = op[1].calc((int32_t)ww << MOD_SHIFT); // carrier
    return true;
  }
  else {
    return false;
  }
} 


