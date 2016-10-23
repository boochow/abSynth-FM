/***********************************/
/* PWMDAC: Module to support       */
/* 9-bit DAC using Fast PWM mode   */
/* of TIMER1 of ATmega168          */
/* PWM freq = 31.25 kHz            */
/*                                 */
/* 2009/6/26 created by PCM1723    */
/***********************************/
//
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//
#ifndef PWMDAC_h
#define PWMDAC_h
//
// oversampling ratio (f_PWM / f_sample)
//
#define PWM_ovs (2)
//
// PWM DAC pin define
//
#define PWMDAC_PIN (13)
//
// sample update timing flag
//
extern volatile uint8_t fsflag;
//
// DAC input buffer variable
//
extern volatile int16_t dac_l, dac_r;
//
// PWM DAC setup
//
extern void PWMDAC_setup(uint8_t PWM_mode);
//
#endif

