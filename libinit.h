/*!
 * \file libinit.h
 * \version 1.0
 * \brief The module \a Init initializes the Timer, OSC, ISR, PPS and Port interface.
 */

#ifndef LIBINIT_H
#define LIBINIT_H

#include "configbits.h"
#include "music.h"

#ifdef __XC32
// The function `init_pps` pre-connect the modules to the pic32's pins.
// - Source § 11.3 Peripheral Pin Select: http://ww1.microchip.com/downloads/en/DeviceDoc/60001168J.pdf#G12.1111922
void init_pps(void) {
    // Input Pin Selection: http://ww1.microchip.com/downloads/en/DeviceDoc/60001168J.pdf#G12.1112757
    ANSELBbits.ANSB13 = 0;
    U1RXR = 0b0011;       // RPB13 U1RX.
    ANSELAbits.ANSA1 = 0; // Disable analog on A1
    SDI1R = 0b0000;       // Set Data's pin as SDI1

    // Output Pin selection: http://ww1.microchip.com/downloads/en/DeviceDoc/60001168J.pdf#G12.1122062
    ANSELBbits.ANSB15 = 0;
    RPB15Rbits.RPB15R = 0b0001; // RPA0 U1TX.
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
    // RA3
    TRISAbits.TRISA3 = 0b0; // I/O port pin is an output.
    LATAbits.LATA3 = 0b0;   // AEN

    // RB5 AEN
    TRISBbits.TRISB5 = 0b0; // I/O port pin is an output.
    LATBbits.LATB5 = 0b0;   // AEN
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

void init_u1(void) {
    U1MODEbits.ON = 0; // UARTx is disabled.
    // Register Table: http://ww1.microchip.com/downloads/en/DeviceDoc/61107G.pdf#G1.881874
    // 1. Initialize the UxBRG register for the appropriate baud rate (refer to 21.3 ?UART Baud
    // Rate Generator?)
    U1BRG = 1; //(((1000/9600)/16)-1); // 25

    // Register Table: http://ww1.microchip.com/downloads/en/DeviceDoc/61107G.pdf#G1.910009
    // 2. Set the number of data and Stop bits, and parity selection by writing to the PDSEL<1:0>
    // bits (UxMODE<2:1>) and STSEL bit (UxMODE<0>)
    U1MODEbits.BRGH = 1;     // High-Speed mode ? 4x baud clock enabled
    U1MODEbits.STSEL = 1;    // 1 Stop bit.
    U1MODEbits.PDSEL = 0b00; // 8-bit data, no parity.
    U1MODEbits.UEN = 0b00;   // UxTX  and  UxRX  pins  are  enabled  and  used ;
                             // http://ww1.microchip.com/downloads/en/DeviceDoc/61107G.pdf#G1.910009

    // Register Table: http://ww1.microchip.com/downloads/en/DeviceDoc/61107G.pdf#G1.911135
    // 4. Enable the transmission by setting the UTXEN bit (UxSTA<10>), which also sets the
    // UxTXIF bit. The UxTXIF bit should be cleared in the software routine that services the
    // UART transmit interrupt. The operation of the UxTXIF bit is controlled by the UTXISEL
    // control bits.
    U1STAbits.UTXEN = 1; // UARTx transmitter is enabled. UxTX pin is controlled by UARTx
    U1STAbits.URXEN = 1; // UARTx receiver is enabled. UxTX pin is controlled by UARTx

    // 3. If transmit interrupts are desired, set the UxTXIE control bit in the corresponding Interrupt
    // Enable Control register (IEC). Specify the interrupt priority and subpriority for the transmit
    // interrupt using the UxIP<2:0> and UxIS<1:0> control bits in the corresponding Interrupt
    // Priority Control register (IPC). Also, select the Transmit Interrupt mode by writing to the

    // Register Table: http://ww1.microchip.com/downloads/en/DeviceDoc/61107G.pdf#G1.910009
    // 5. Enable the UART module by setting the ON bit (UxMODE<15>).
    U1MODEbits.ON = 1; // UARTx is enabled.
                       // UARTx pins are controlled by UARTx as defined by UEN<1:0> and UTXEN control bits
}

void init_oc1(void) {
    OC1CON = 0;             // Clear Output Compare
    OC1CONbits.OC32 = 0;    // Set Output Compare on 16 bits Timer
    OC1CONbits.OCTSEL = 0;  // Select Timer 2
    OC1CONbits.OCM = 0b011; // Compare event toggles event OC1 pin
    OC1CONbits.ON = 0;      // Disable Output Compare
}

void init_spi1(void) {
    IEC1 = 0;    // Disable the SPI interrupts in the respective IECx register
    IFS1 = 0;    // Clear the SPIx interrupt flags/events in the respective IFSx register.
    SPI1CON = 0; // Stops and resets the SPI1

    const int clear = SPI1BUF; // Clears the receive buffer

    SPI1BRG = 0; // Use FPB/ clock frequency

    SPI1STATbits.SPIROV = 0; // No overflow has occurred

    SPI1CONbits.MSTEN = 1; // Enable master mode
    SPI1CONbits.CKP = 1;   // Idle state for clock is a high level; active state is a low level
    SPI1CONbits.CKE
        = 0; // Serial output data changes on transition from idle clock state to active clock state (see CKP bit)
    SPI1CONbits.SMP = 1; // Input data sampled at end of data output time
    SPI1CONbits.MODE32 = 0;
    SPI1CONbits.MODE16 = 0; // 8-bit transfer mode

    SPI1CONbits.ON = 1; // Enable SPI1.
}

void init_timer3(void) {
    T3CON = 0;    // Disable Timer
    TMR3 = 0;     // Clear timer register
    PR3 = DOUBLE; // Load period register

    IPC3bits.T3IP = 2; // Set priority level = 1
    IPC3bits.T3IS = 1; // Set subpriority level = 1

    IFS0bits.T3IF = 0; // Clear the timer interrupt status flag
    IEC0bits.T3IE = 1; // Enable timer interrupts; Register Table

    T3CONbits.TCKPS = 0; // Timer Input Clock Prescale value
    T3CONbits.ON = 1;    // Enable Timer
}

void init_timer2(void) {
    T2CON = 0; // Disable Timer
    TMR2 = 0;  // Clear timer register
    PR2 = DO;  // Load period register

    IPC2bits.T2IP = 3; // Set priority level = 2
    IPC2bits.T2IS = 1; // Set subpriority level = 1

    IFS0bits.T2IF = 0; // Clear the timer interrupt status flag
    IEC0bits.T2IE = 1; // Enable timer interrupts; Register Table

    T2CONbits.TCKPS = 0; // Timer Input Clock Prescale value
    T2CONbits.ON = 1;    // Enable Timer
}

void init_timer4(void) {
    T4CON = 0;   // Disable Timer
    TMR4 = 0;    // Clear timer register
    PR4 = 0x5FF; // Load period register

    IPC4bits.T4IP = 4; // Set priority level = 4
    IPC4bits.T4IS = 1; // Set subpriority level = 1

    IFS0bits.T4IF = 0; // Clear the timer interrupt status flag
    IEC0bits.T4IE = 1; // Enable timer interrupts; Register Table

    T4CONbits.TCKPS = 0b0; // Timer Input Clock Prescale value
    T4CONbits.ON = 1;      // Enable Timer
}

void    init_timer5() {
    // Sample Example: http://ww1.microchip.com/downloads/en/DeviceDoc/61105F.pdf#G1.883796
    T5CONbits.ON = 0b0; // Disable Timer; Register Table: http://ww1.microchip.com/downloads/en/DeviceDoc/61105F.pdf#G1.884049
    TMR5 = 0; // Clear timer register
    PR5 = 0xFFFF; // Load period register

    // Register Table: http://ww1.microchip.com/downloads/en/DeviceDoc/60001108H.pdf#G1.980585
    IPC5bits.T5IP = 5; // Set priority level = 4
    IPC5bits.T5IS = 1; // Set subpriority level = 1

    IFS0bits.T5IF = 0b0; // Clear the timer interrupt status flag
    IEC0bits.T5IE = 0b0; // Disable timer interrupts; Register Table

    T5CONbits.TCKPS = 0b0; // Timer Input Clock Prescale value; Register Table: http://ww1.microchip.com/downloads/en/DeviceDoc/61105F.pdf#G1.885676
    T5CONbits.ON = 0b1; // Enable Timer; Register Table: http://ww1.microchip.com/downloads/en/DeviceDoc/61105F.pdf#G1.884049
}
#endif /* XC32 */

#endif /* LIBINIT_H */