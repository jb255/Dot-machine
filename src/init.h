/*!
 * \file init.h
 * \version 1.0
 * \brief The module \a Init initializes the ISR, PPS and Port interface.
 */

#ifndef LIBINIT_H
#define LIBINIT_H

#ifdef __XC32
// The function `init_pps` pre-connect the modules to the pic32's pins.
// - Source § 11.3 Peripheral Pin Select: http://ww1.microchip.com/downloads/en/DeviceDoc/60001168J.pdf#G12.1111922
void init_pps(void) {
    // Input Pin Selection: http://ww1.microchip.com/downloads/en/DeviceDoc/60001168J.pdf#G12.1112757
    U2RXRbits.U2RXR = 0b0001; // RPB5 U2RX.
    U1RXRbits.U1RXR = 0b0011; // RPB13 U1RX.
    ANSELAbits.ANSA1 = 0;     // Disable analog on A1
    SDI1R = 0b0000;           // Set Data's pin as SDI1

    // Output Pin selection: http://ww1.microchip.com/downloads/en/DeviceDoc/60001168J.pdf#G12.1122062
    RPB15Rbits.RPB15R = 0b0001; // RPA0 U1TX.
    RPA3Rbits.RPA3R = 0b0010;   // RPA3 U2TX.
    RPB3R = 0b0101;             // Set Buzzer's pin as OC1
    ANSELAbits.ANSA0 = 0;       // Disable analog on A0
    TRISAbits.TRISA0 = 0;       // Set Attention's pin as output;
    LATAbits.LATA0 = 0;         // Set Attention tp 0
    TRISBbits.TRISB14 = 0;      // Set SCK1 as output
    RPA0R = 0b0011;             // Set Attention's pin as SS1
    RPA2R = 0b0011;             // Set Command's pin as SDO1
}

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

#endif /* LIBINIT_H */
