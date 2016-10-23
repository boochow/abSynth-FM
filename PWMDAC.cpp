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
#include <Wiring.h>
#include "PWMDAC.h"
//
// Timer1 overflow interrupt service routine
//
ISR(TIMER1_OVF_vect) 
{
  static volatile int8_t ovs_cnt = PWM_ovs-1;
  if (0 > (--ovs_cnt)) { // time to update new sample
    ovs_cnt = PWM_ovs-1;    // reset oversample count
// 2009/6/29 changed
//    OCR1A   = ((uint16_t)(0x8000 ^ dac_l) >> 7); // outpubt to PWM duty
    OCR1A   = ((uint16_t)(0x8000 ^ dac_l) >> 8); // outpubt to PWM duty
    fsflag  = 1;            // notify fs update timing to main loop
  } // if (OVS > ...
} // ISR(TIMER1_OVF_vect) 
//
// PWM DAC setup
//
void PWMDAC_setup(uint8_t PWM_mode)
{
//  modify Timer1 PWM setting
  analogWrite(PWMDAC_PIN, 256); // enable PWM output
/* 2009/6/29 changed
  TCCR1B  = 0x09; // 1/1 clk (16 MHz)
  TCCR1A  = 0xA2; // 9bit Fast PWM
                  // f_PWM = 16 MHz / 512 = 31.25 kHz
 */
  TCCR1B  = 0x01; // 1/1 clk (16 MHz), 8-bit Phase Correct PWM
  if (PWM_mode) { // use interrupt
    TIMSK1 |= _BV(TOIE1);    // enable  TIMER1 OVF interrupt 
  } else { // 
    TIMSK1 &= ~(_BV(TOIE1)); // disable TIMER1 OVF interrupt 
  }
} // void PWMDAC_setup()
