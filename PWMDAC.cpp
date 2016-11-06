/***********************************/
/* PWMDAC: Module to support       */
/* 9-bit DAC using Fast PWM mode   */
/* of TIMER1 of ATmega168          */
/* PWM freq = 31.25 kHz            */
/*                                 */
/* 2009/6/26 created by PCM1723    */
/* 2009/6/29 PWM mode changed      */
/*           from Fast 9-bit       */
/*           to Phase correct 8-bit*/
/***********************************/
//
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <wiring_private.h>
#include "PWMDAC.h"

#define cbi16(sfr, bit) (_SFR_WORD(sfr) &= ~_BV(bit))
#define sbi16(sfr, bit) (_SFR_WORD(sfr) |= _BV(bit))

//
// Timer1 overflow interrupt service routine
//
ISR(TIMER4_OVF_vect) 
{
  static volatile int8_t ovs_cnt = PWM_ovs-1;
  if (0 > (--ovs_cnt)) { // time to update new sample
    ovs_cnt = PWM_ovs-1;    // reset oversample count
    OCR4A   = ((uint16_t)(0x8000 ^ dac_l) >> 8); // outpubt to PWM duty
    fsflag  = 1;            // notify fs update timing to main loop
  } // if (OVS > ...
} // ISR(TIMER1_OVF_vect) 

//
// PWM DAC setup
//
void PWMDAC_setup(uint8_t PWM_mode)
{
//  modify Timer1 PWM setting
  pinMode(PWMDAC_PIN,OUTPUT);
  pinMode(PWMDAC_PIN2,OUTPUT);
 // analogWrite(PWMDAC_PIN, 256); // enable PWM output
/* 2009/6/29 changed
  TCCR1B  = 0x09; // 1/1 clk (16 MHz)
  TCCR1A  = 0xA2; // 9bit Fast PWM
                  // f_PWM = 16 MHz / 512 = 31.25 kHz
 */
  // Set Timer 4 prescale factor to 1 (CS43..1 = 0001)
  cbi(TCCR4B, CS43);
  cbi(TCCR4B, CS42);
  cbi(TCCR4B, CS41);
  sbi(TCCR4B, CS40);

  // Phase-correct PWM
  sbi(TCCR4A, PWM4A);
  sbi(TCCR4D, WGM40);
  cbi(TCCR4D, WGM41);

  // Connect PWM on Timer 4 to channel OC4A (COM4x1..0 = 10)
  cbi(TCCR4A, COM4A1);
  sbi(TCCR4A, COM4A0);
   
  sbi(TIMSK4,TOIE4); // Enable interrupt

  sbi(TIFR4, TOV4);
} // void PWMDAC_setup()
