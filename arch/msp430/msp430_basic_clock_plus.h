
/**
 *  \file   msp430_basic_clock_plus.h
 *  \brief  MSP430x2xx basic clock plus definition (based on "msp430_basic_clock.h") 
 *  \author Julien Carpentier
 *  \date   2011
 **/

// WARNING : mportant mofications in this file must be send back in "msp430_basic_block.h"

#ifndef MSP430_BASIC_CLOCK_PLUS_H
#define MSP430_BASIC_CLOCK_PLUS_H

#if defined(__msp430_have_basic_clock_plus)

/* default on */
#define HIGH_RES_CLOCK 1
#define TRACER_SPEED   1

/**
 * 
 * The basic clock plus module includes three or four clock sources:
 * 
 * - LFXT1CLK: Low-frequency/high-frequency oscillator that can be used
 *   with low-frequency watch crystals or external clock sources of 32,768-Hz.
 *   or with standard crystals, resonators, or external clock sources in the
 *   400-kHz to 16-MHz range.
 * - XT2CLK: Optional high-frequency oscillator that can be used with
 *   standard crystals, resonators, or external clock sources in the 400-kHz to
 *   16-MHz range.
 * - DCOCLK: Internal digitally controlled oscillator (DCO).
 * - VLOCLK: Internal very low power, low frequency oscillator with 12-kHz
 *   typical frequency.
 *  
 * 
 * Three clock signals are available from the basic clock plus module:
 * 
 * - ACLK: Auxiliary clock. ACLK is software selectable as LFXT1CLK or
 *   VLOCLK. ACLK is divided by 1, 2, 4, or 8. ACLK is software selectable for
 *   individual peripheral modules.
 * - MCLK: Master clock. MCLK is software selectable as LFXT1CLK,
 *   VLOCLK, XT2CLK (if available on-chip), or DCOCLK. MCLK is divided by
 *   1, 2, 4, or 8. MCLK is used by the CPU and system.
 * - SMCLK: Sub-main clock. SMCLK is software selectable as LFXT1CLK,
 *   VLOCLK, XT2CLK (if available on-chip), or DCOCLK. SMCLK is divided
 *   by 1, 2, 4, or 8. SMCLK is software selectable for individual peripheral
 *   modules.
 * 
 */




#define BCP_START     0x56
#define BCP_END       0x58

#define BCP_DCOCTL    0x56
#define BCP_BCSCTL1   0x57
#define BCP_BCSCTL2   0x58
#define BCP_BCSCTL3   0x53 

#if defined(WORDS_BIGENDIAN)
struct __attribute__ ((packed)) dcoctl_t {
  uint8_t
    dco:3,
    mod:5;
};
#else
struct __attribute__ ((packed)) dcoctl_t {
  uint8_t
    mod:5,
    dco:3;
};
#endif

#if defined(WORDS_BIGENDIAN)
struct __attribute__ ((packed)) bcsctl1_t {
  uint8_t
    xt2off:1,
    xts:1, //XTS = 1 is not supported in MSP430x20xx devices (#define __msp430_have_xts > msp430_models.h ?)
    diva:2,
    rsel:4;
};
#else
struct __attribute__ ((packed)) bcsctl1_t {
  uint8_t
    rsel:4,
    diva:2,
    xts:1, //XTS = 1 is not supported in MSP430x20xx devices (#define __msp430_have_xts > msp430_models.h ?)
    xt2off:1;
};
#endif

#if defined(WORDS_BIGENDIAN)
struct __attribute__ ((packed)) bcsctl2_t {
  uint8_t
    selm:2,
    divm:2,
    sels:1,
    divs:2,
    dcor:1;
};
#else
struct __attribute__ ((packed)) bcsctl2_t {
  uint8_t
    dcor:1,
    divs:2,
    sels:1,
    divm:2,
    selm:2;
};
#endif

#if defined(WORDS_BIGENDIAN)
struct __attribute__ ((packed)) bcsctl3_t {
  uint8_t
    xt2s:2,
    lfxt1s:2,
    xcap:2,
    xt2of:1,
    lfxt1of:1;
};
#else
struct __attribute__ ((packed)) bcsctl3_t {
  uint8_t
    
    lfxt1of:1,
    xt2of:1,
    xcap:2,
    lfxt1s:2,
    xt2s:2;
};
#endif


/* ************************************************** */
/* ************************************************** */
/* ************************************************** */


struct msp430_basic_clock_plus_t
{
  union {
    struct dcoctl_t  b;
    int8_t           s;
  } dco;
  union {
    struct bcsctl1_t b;
    int8_t           s;
  } bcsctl1;
  union {
    struct bcsctl2_t b;
    int8_t           s;
  } bcsctl2;
  union {
    struct bcsctl3_t b;
    int8_t           s;
  } bcsctl3;

  /* internal clocks */

  uint64_t MCLK_counter;
  int      MCLK_increment;
  int      MCLK_bitmask;

  uint64_t ACLK_counter;
  int      ACLK_temp;
  int      ACLK_increment;
  int      ACLK_bitmask;

  uint64_t SMCLK_counter;
  int      SMCLK_temp;
  int      SMCLK_increment;
  int      SMCLK_bitmask;

  /* external clocks */

  uint32_t lfxt1_freq;
  uint64_t lfxt1_counter;
  int      lfxt1_increment;

  uint32_t dco_freq;
  uint64_t dco_counter;
  int      dco_increment;
  
  uint32_t vlo_freq;
  uint64_t vlo_counter;
  int      vlo_increment;

  /* external clock temporary variables */

#if defined(HIGH_RES_CLOCK)
  float    lfxt1_temp;
  float    lfxt1_cycle_nanotime;
  float    xt2_temp;
  float    xt2_cycle_nanotime;
  float    dco_temp;
  float    dco_cycle_nanotime;
  float    vlo_temp;
  float    vlo_cycle_nanotime;
  
#else
  int      lfxt1_temp;
  uint32_t lfxt1_cycle_nanotime;
  int      xt2_temp;
  uint32_t xt2_cycle_nanotime;
  int      dco_temp;
  uint32_t dco_cycle_nanotime;
  int      vlo_temp;
  uint32_t vlo_cycle_nanotime;
  
#endif
};

/* ************************************************** */
/* ************************************************** */
/* ************************************************** */

void    msp430_basic_clock_plus_create();
void    msp430_basic_clock_plus_reset();

int     msp430_basic_clock_plus_update(int clock_add);
void    msp430_basic_clock_plus_update_done();

int8_t  msp430_basic_clock_plus_read (uint16_t addr);
void    msp430_basic_clock_plus_write(uint16_t addr, int8_t val);

#if TRACER_SPEED != 0
void    msp430_basic_clock_plus_speed_tracer_init();
void    msp430_basic_clock_plus_speed_tracer_update();
#else
#define msp430_basic_clock_plus_speed_tracer_init() do { } while (0)
#define msp430_basic_clock_plus_speed_tracer_update() do { } while (0)
#endif

#define MCU_CLOCK_SYSTEM_UPDATE(n)       msp430_basic_clock_plus_update(n)
#define MCU_CLOCK_SYSTEM_UPDATE_DONE()   msp430_basic_clock_plus_update_done()
#define MCU_CLOCK_SYSTEM_SPEED_TRACER()  msp430_basic_clock_plus_speed_tracer_update()

/* ************************************************** */
/* ************************************************** */
/* ************************************************** */
#else
#define msp430_basic_clock_plus_create() do { } while (0)
#define msp430_basic_clock_plus_reset()  do { } while (0)
#endif /* defined(__msp430_have_basic_clock_plus) */
#endif /* _H_ */
