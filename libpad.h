/*!
 * \file libpad.h
 * \version 1.0
 * \brief The module \a Pad is a pad interface for keyboard vt100 or PS{X}.
 */

#ifndef LIBPAD_H
#define LIBPAD_H

#include "configbits.h"
#include "libtype.h"
#include "libdriver.h"
#include "liboard.h"

// clang-format off

#ifdef __XC32
/*!
 * \union Pad
 * \brief The enumeration \a Pad describe a \f$PS{X}\f$'s touches.
 */
typedef union Pad {
    enum {
        Select = 0b1111111101111111,
         Start = 0b1111111111101111, /*! Escape key. */
            Up = 0b1111111111110111, /*! Up's key \f$ ESC [ A \f$. */
          Left = 0b1111111111111011, /*! Right's key \f$ ESC [ C \f$. */
          Down = 0b1111111111111101, /*! Down's key \f$ ESC [ B \f$. */
         Right = 0b1111111111111110, /*! Left's key \f$ ESC [ D \f$. */
      Triangle = 0b1111011111111111,
        Square = 0b1111111011111111,
         Cross = 0b1111110111111111,
        Circle = 0b1111101111111111,
            L1 = 0b1101111111111111,
            L2 = 0b0111111111111111,
            R1 = 0b1110111111111111,
            R2 = 0b1011111111111111,
           End = 0b1101111111111111, // L1
       Nothing = 0b1111111111111111,
       // AnalogOff = 0b0000000001011010,
       // AnalogOn = 0b0000000011001110,
    } key : 16;
    struct {
        u8 data4 : 8;
        u8 data5 : 8;
        u8 data2 : 8;
    } buf;
    u32 all : 16;
} Pad;
#else
/*!
 * \union Pad
 * \brief The enumeration \a Pad describe a keyboards touches.
 */
typedef union Pad {
    /*! The VT100 sequence are specified from the VT52 Mode as \link vt100.net/docs/vt100-ug/table3-6.html table3-6. */
    enum {
          Esc =                   0b11011, /*! Escape key. */
          End = 0b01101000101101100011011, /*! End's key. */
           Up = 0b10000010101101100011011, /*! Up's key \f$ ESC [ A \f$. */
        Right = 0b10000110101101100011011, /*! Right's key \f$ ESC [ C \f$. */
         Down = 0b10000100101101100011011, /*! Down's key \f$ ESC [ B \f$. */
         Left = 0b10001000101101100011011, /*! Left's key \f$ ESC [ D \f$. */
    } key : 32;
    u8 buf[3];
    u32 all : 32;
} Pad;
#endif

#endif /* LIBPAD_H */
