/*!
 * \file libdriver.h
 * \version 1.0
 * \brief The module \a Dot is a driver interface.
 */

#ifndef LIBDRIVER_H
#define LIBDRIVER_H

#include "libtype.h"
#include <stdbool.h>

#ifdef __XC32
#include <xc.h>
#else
#include <unistd.h>
#endif

/*! The constante \a \f$X_{MAX}\f$ is the abscissa limit. */
#define X_MAX 11
/*! The constante \a \f$Y_{MAX}\f$ is the ordinate limit. */
#define Y_MAX 28
/*! The constante \a \f$XY_{MAX}\f$ is the orthonormal limit. */
#define XY_MAX X_MAX *Y_MAX
/*! The constante \a \f$BUF_{MAX}\f$ is the buffer limit. */
#define BUFF_MAX XY_MAX * 2

/*!
 * \enum Color
 * \brief The enumeration \a Color limits state of flip-disc.
 * \param [open] \f$1\f$
 * \param [close] \f$0\f$
 */
typedef enum Color {
    Close = 0b0, /*! Black's Color. */
    Open = 0b1,  /*! Yellow's Color. */
} Color;

/*!
 * \union Dot
 * \brief The union \a Dot describes a representation who is empty or will be writted.
 * \param [check] 0b0 @ the dot flip the dot without check the mutable \a board variable.
 * \param [check] 0b1 @ the dot flip the dot according to the mutable \a board variable.
 * \param [x] \f$0..10\f$
 * \param [y] \f$0..27\f$
 */
typedef union Dot {
    struct {
        Color color : 1; /*! Color. */
        i8 x : 8;
        u16 y : 5; /*! Y: \f$0..27..30-1\f$ */
    } bits;
    u16 all : 14;
} Dot;

/*!
 * \struct BufferDot
 * \brief \a BufferDot stocks structs containing the dot and its change to operate
 * \brief While \a lenght count the number of values left in the buffer
 * \brief The structure \a BufferDot is a array limitied at dot's \f$XY_{MAX}\f$.
 */
typedef struct BufferDot {
    Dot content[BUFF_MAX]; /*! Stack of dots. */
    u16 lenght : 9;        /*! Lenght: \f$0..512-1\f$ */
} BufferDot;

/*! The mutable registry \a buffer_dot contains the dot's list to writes to the board's display. */
BufferDot buffer_dot;

/*!
 * \enum SwitchY
 * \brief The enumeration \a SwitchY excludes the NC pins \note {NC pins stands for Not Connected pins} possibility of
 * the oderly \f$U{6..7}\f$ multiplexers.
 * \brief First
*/
enum SwitchY {
    SYF1 = 0b00000,
    SYF2 = 0b00010,
    SYF3 = 0b00100,
    SYF4 = 0b00110,
    SYF5 = 0b01000,
    SYF6 = 0b01010,
    SYF7 = 0b01100,
    SYF8 = 0b01110,
    SYF11 = 0b10100,
    SYF12 = 0b10110,
    SYF13 = 0b11000,
    SYF14 = 0b11010,
    SYF15 = 0b11100,
    SYF16 = 0b11110,
    // Extend
    SYN3 = 0b00101,
    SYN4 = 0b00111,
    SYN5 = 0b01001,
    SYN6 = 0b01011,
    SYN7 = 0b01101,
    SYN8 = 0b01111,
    SYN9 = 0b10001,
    SYN10 = 0b10011,
    SYN11 = 0b10101,
    SYN12 = 0b10111,
    SYN13 = 0b11001,
    SYN14 = 0b11011,
    SYN15 = 0b11101,
    SYN16 = 0b11111,
} SwitchY;

/*!
 * \enum SwitchX
 * \brief The enumeration \a SwitchX excludes the NC pins of the abscis \f$U{4,5}\f$ multiplexers.
 */
enum SwitchX {
    SX16_8 = 0b11110111,
    SX15_7 = 0b11100110,
    SX14_6 = 0b11010101,
    SX13_5 = 0b11000100,
    SX12_4 = 0b10110011,
    SX11_3 = 0b10100010,
    SX10_2 = 0b10010001,
    SX1_9 = 0b00001000,
    SX2_10 = 0b00011001,
    SX3_11 = 0b00101010,
    SX4_12 = 0b00111011,
} SwitchX;

/*!
 * \union PinY
 * \brief The union \a PinY describes a multiplexer's switch representation.
 */
typedef union PinY {
    const struct {
        // Extend.
        bool en : 1; /*! B_EN */
        // Port
        bool b0 : 1; /*! B_0 */
        bool b1 : 1; /*! B_1 */
        bool b2 : 1; /*! B_2 */
        bool b3 : 1; /*! B_3 */
    } bits;
    bool en : 1;
    u8 all : 5;
} PinY;

/*!
 * \union PinX
 * \brief The union \a PinX describes a multiplexer's switch representation.
 */
typedef union PinX {
    const struct {
        /*! Close's color - component $u_4$. */
        bool a0 : 1; /*! A_0 */
        bool a1 : 1; /*! A_1 */
        bool a2 : 1; /*! A_2 */
        bool a3 : 1; /*! A_3 */
        /*! Open's color - component $u_5$. */
        bool a4 : 1; /*! A_0 */
        bool a5 : 1; /*! A_1 */
        bool a6 : 1; /*! A_2 */
        bool a7 : 1; /*! A_3 */
    } bits;
    u8 all : 8;
} PinX;

#if defined __XC32
/*!
 * The constant dictionary \a pins_y contains PIC's the oderly configuration.
 * Active if compiled with XC32
 */
const PinY pins_y[Y_MAX] = {
    {.all = SYN16}, /*! Pin 02. */
    {.all = SYN8},  /*! Pin 03. */
    {.all = SYN15}, /*! Pin 04. */
    {.all = SYN7},  /*! Pin 05. */
    {.all = SYN14}, /*! Pin 06. */
    {.all = SYN6},  /*! Pin 07. */
    {.all = SYN13}, /*! Pin 08. */
    {.all = SYN12}, /*! Pin 10. */
    {.all = SYN5},  /*! Pin 11. */
    {.all = SYN11}, /*! Pin 12. */
    {.all = SYN4},  /*! Pin 13. */
    {.all = SYN10}, /*! Pin 14. */
    {.all = SYN3},  /*! Pin 15. */
    {.all = SYN9},  /*! Pin 16. */
    {.all = SYF1},  /*! Pin 18. */
    {.all = SYF11}, /*! Pin 19. */
    {.all = SYF2},  /*! Pin 20. */
    {.all = SYF12}, /*! Pin 21. */
    {.all = SYF3},  /*! Pin 22. */
    {.all = SYF13}, /*! Pin 23. */
    {.all = SYF4},  /*! Pin 24. */
    {.all = SYF5},  /*! Pin 26. */
    {.all = SYF14}, /*! Pin 27. */
    {.all = SYF6},  /*! Pin 28. */
    {.all = SYF15}, /*! Pin 29. */
    {.all = SYF7},  /*! Pin 30. */
    {.all = SYF16}, /*! Pin 31. */
    {.all = SYF8},  /*! Pin 32. */
};
#else
/*! The constant dictionary \a pins_y contains the VT100's oderly configuration.
 * Active with gcc
 */
const u8 pins_y[Y_MAX][2] = {
    "01", /*! y0 */
    "02", /*! y1 */
    "03", /*! y2 */
    "04", /*! y3 */
    "05", /*! y4 */
    "06", /*! y5 */
    "07", /*! y6 */
    "08", /*! y7 */
    "09", /*! y8 */
    "10", /*! y9 */
    "11", /*! y10 */
    "12", /*! y11 */
    "13", /*! y12 */
    "14", /*! y13 */
    "15", /*! y14 */
    "16", /*! y15 */
    "17", /*! y16 */
    "18", /*! y17 */
    "19", /*! y18 */
    "20", /*! y19 */
    "21", /*! y20 */
    "22", /*! y21 */
    "23", /*! y22 */
    "24", /*! y23 */
    "25", /*! y24 */
    "26", /*! y25 */
    "27", /*! y26 */
    "28", /*! y27 */
};
#endif

#if defined __XC32
/*! The constante dictionary \a pins_x contains the abscis configuration.
 * Active with X32
 */
const PinX pins_x[X_MAX] = {
    {.all = SX16_8}, /*! Pin [04-03]. */
    {.all = SX15_7}, /*! Pin [06-05]. */
    {.all = SX14_6}, /*! Pin [08-07]. */
    {.all = SX13_5}, /*! Pin [10-09]. */
    {.all = SX12_4}, /*! Pin [12-11]. */
    {.all = SX11_3}, /*! Pin [14-13]. */
    {.all = SX10_2}, /*! Pin [16-15]. */
    {.all = SX1_9},  /*! Pin [04-03]. */
    {.all = SX2_10}, /*! Pin [06-05]. */
    {.all = SX3_11}, /*! Pin [08-07]. */
    {.all = SX4_12}, /*! Pin [10-09]. */
};
#else
/*! The constante dictionary \a pins_x contains the abscis configuration.
 * Active with gcc
 */
const u8 pins_x[X_MAX][2] = {
    "01", /*! x0 */
    "02", /*! x1 */
    "03", /*! x2 */
    "04", /*! x3 */
    "05", /*! x4 */
    "06", /*! x5 */
    "07", /*! x6 */
    "08", /*! x7 */
    "09", /*! x8 */
    "10", /*! x9 */
    "11", /*! x10 */
};
#endif

#ifdef __XC32
// The function `init_pps` pre-connect the modules to the pic32's pins.
// - Source § 11.3 Peripheral Pin Select: http://ww1.microchip.com/downloads/en/DeviceDoc/60001168J.pdf#G12.1111922
void init_pps(void) {
    // Input Pin Selection: http://ww1.microchip.com/downloads/en/DeviceDoc/60001168J.pdf#G12.1112757
    SS1Rbits.SS1R = 0b0000;   // RPA0 SS1.
    U2RXRbits.U2RXR = 0b0001; // RPB5 U2RX.
    U1RXRbits.U1RXR = 0b0011; // RPB13 U1RX.
    SDI1Rbits.SDI1R = 0b0000; // RPA1 SDI1.

    // Output Pin selection: http://ww1.microchip.com/downloads/en/DeviceDoc/60001168J.pdf#G12.1122062
    RPB3Rbits.RPB3R = 0b0101;   // RPB3 OC1.
    RPB15Rbits.RPB15R = 0b0001; // RPA0 U1TX.
    RPA3Rbits.RPA3R = 0b0010;   // RPA3 U2TX.
    RPA2Rbits.RPA2R = 0b0011;   // RPA2 SDO1.
}
#endif

#ifdef __XC32
// The function `init_port` defines as input or output the pic32's pins.
// Source § 12. I/O port pin: http://ww1.microchip.com/downloads/en/DeviceDoc/60001120F.pdf#G1.962162
void init_port(void) {
    // RB0 AEN
    TRISBbits.TRISB0 = 0b0; // I/O port pin is an output.
    LATBbits.LATB0 = 0b0;   // write on I/O port pin as 0 data.
    // RB1 A0
    TRISBbits.TRISB1 = 0b0; // I/O port pin is an output.
    LATBbits.LATB1 = 0b0;   // write on I/O port pin as 0 data.
    // RB2 A1
    TRISBbits.TRISB2 = 0b0; // I/O port pin is an output.
    LATBbits.LATB2 = 0b0;   // write on I/O port pin as 0 data.
    // RB4 A2
    TRISBbits.TRISB4 = 0b0; // I/O port pin is an output.
    LATBbits.LATB4 = 0b0;   // write on I/O port pin as 0 data.
    // RA4 A3
    TRISAbits.TRISA4 = 0b0; // I/O port pin is an output.
    LATAbits.LATA4 = 0b0;   // write on I/O port pin as 0 data.

    // RB9 BEN
    TRISBbits.TRISB9 = 0b0; // I/O port pin is an output.
    LATBbits.LATB9 = 0b0;   // write on I/O port pin as 0 data.
    // RB8 B0
    TRISBbits.TRISB8 = 0b0; // I/O port pin is an output.
    LATBbits.LATB8 = 0b0;   // write on I/O port pin as 0 data.
    // RB7 B1
    TRISBbits.TRISB7 = 0b0; // I/O port pin is an output.
    LATBbits.LATB7 = 0b0;   // write on I/O port pin as 0 data.
    // RB6 B2
    TRISBbits.TRISB6 = 0b0; // I/O port pin is an output.
    LATBbits.LATB6 = 0b0;   // write on I/O port pin as 0 data.
    // RB12 B3
    TRISBbits.TRISB12 = 0b0; // I/O port pin is an output.
    LATBbits.LATB12 = 0b0;   // write on I/O port pin as 0 data.
}
#endif

#ifdef __XC32
/*!
 * \fn flush_board
 * \brief The function \a flush_board writes the last dot piece writted to the multiplixer ports.
 * \return A boolean for a writtable dot piece.
 */
bool flush_board(void) {
    if (buffer_dot.lenght) {
        buffer_dot.lenght -= 1;
        Dot *current = buffer_dot.content;
        const Dot *end = current + buffer_dot.lenght;
        const PinY pin_y = *(pins_y + current->bits.y);
        const PinX pin_x = *(pins_x + current->bits.x);

        LATBbits.LATB9 = pin_y.bits.en;  /*! B_EN */
        LATBbits.LATB8 = pin_y.bits.b0;  /*! B_0 */
        LATBbits.LATB7 = pin_y.bits.b1;  /*! B_1 */
        LATBbits.LATB6 = pin_y.bits.b2;  /*! B_2 */
        LATBbits.LATB12 = pin_y.bits.b3; /*! B_3 */
        if (current->bits.color == Close) {
            LATBbits.LATB0 = 0b1;           // AEN.
            LATBbits.LATB1 = pin_x.bits.a0; /*! A_0 */
            LATBbits.LATB2 = pin_x.bits.a1; /*! A_1 */
            LATBbits.LATB4 = pin_x.bits.a2; /*! A_2 */
            LATAbits.LATA4 = pin_x.bits.a3; /*! A_3 */
        } else {
            LATBbits.LATB0 = 0b0;           /*! A_EN */
            LATBbits.LATB1 = pin_x.bits.a4; /*! A_4 */
            LATBbits.LATB2 = pin_x.bits.a5; /*! A_5 */
            LATBbits.LATB4 = pin_x.bits.a6; /*! A_6 */
            LATAbits.LATA4 = pin_x.bits.a7; /*! A_7 */
        }
        while (current < end) {
            *(current) = *(current + 1);
            current++;
        }
        return 1;
    } else {
        LATBbits.LATB0 = 0b0; /*! A_EN */
        LATBbits.LATB1 = 0b0; /*! A_0 */
        LATBbits.LATB2 = 0b0; /*! A_1 */
        LATBbits.LATB4 = 0b0; /*! A_2 */
        LATAbits.LATA4 = 0b0; /*! A_3 */
        return 0;
    }
}
#else
#ifdef __SDL__
/*!
 * \fn flush_board
 * \brief The function \a flush_board writes the last dot piece writted into the vt100 format.
 * \return A boolean for a writtable dot piece.
 */
bool flush_board(void) {
    buffer_dot.lenght = 0;
    return 0;
}
#else
/*!
 * \fn flush_board
 * \brief The function \a flush_board writes the last dot piece writted into the vt100 format.
 * \return A boolean for a writtable dot piece.
 */
bool flush_board(void) {
    int __attribute__((__unused__)) unused;

    if (buffer_dot.lenght) {
        buffer_dot.lenght -= 1;
        u8 buf[12] = "\033[__;__H_\0338\0";
        Dot *current = buffer_dot.content;
        const Dot *end = current + buffer_dot.lenght;

        *(buf + 2) = **(pins_y + current->bits.y);
        *(buf + 3) = *(*(pins_y + current->bits.y) + 1);
        *(buf + 5) = **(pins_x + current->bits.x);
        *(buf + 6) = *(*(pins_x + current->bits.x) + 1);
        if (current->bits.color == Open) {
            *(buf + 8) = 't';
        }
        unused = write(1, &buf, 11);
        while (current < end) {
            *(current) = *(current + 1);
            current++;
        }
        return 1;
    } else {
        return 0;
    }
}
#endif
#endif

#endif /* LIBDRIVER_H */
