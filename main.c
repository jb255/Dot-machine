/*!
 * \file main.c
 * \version 1.0
 * \brief The module \a Main is the first Tetris interface.
 */

#ifdef __XC32
#include <xc.h>
#include <sys/attribs.h>
#endif

#ifdef __XC32
#include "configbits.h"
#include "libinit.h"
#include "libmino.h"
#include "music.h"
#else
#include "libmino.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>
#endif

#ifdef __XC32
void __ISR(_SPI_1_VECTOR, IPL1AUTO) SPI1_Handler(void) {
    IFS1bits.SPI1EIF = 0;
}

void __ISR(_TIMER_2_VECTOR, IPL3AUTO) Note(void) {
    IFS0bits.T2IF = 0b0; // Clear the timer interrupt status flag
}

void __ISR(_TIMER_3_VECTOR, IPL2AUTO) Tempo(void) {
    IFS0bits.T3IF = 0; // Clear the timer interrupt status flag
    OC1CONbits.ON = !OC1CONbits.ON;

    if (!mute)
    {
        if (game == TETRIS && start) {
         music_tetris();
        } /* DOTO: patch the music ; cc @jgalvani
       * else if (game == DOT && start) {
        music_dot();
        } */else if (!start) {
          music_start();
        } else if (game == WIN) {
         win_music();
        } else if (game == FAIL) {
         fail_music();
        }
    }
}

void __ISR(_TIMER_4_VECTOR, IPL4AUTO) Button(void) {
    IFS0bits.T4IF = 0b0; // Clear the timer interrupt status flag
    static u8 speed = 0;

    padx();
    flush_board();

    if (game == TETRIS) {
        speed++;
        if (speed >= game_speed) {
            move_down_mino();
            speed = 0;
        }
    } else {
        speed = 0;
        game_speed = 50;
    }
}
#endif

#ifdef __XC32
/*! The start function `main` is the XC32 implementation of Dot machine. */
int main(void) {
    init_pps();
    init_port();

    init_board();
    write_title();

    init_oc1();
    init_spi1();
    init_u1();

    init_timer5();
    init_timer4();
    init_timer2();
    init_timer3();

    INTCONbits.MVEC = 0b1;         // Interrupt Controller configured for multi vectored mode; Register Table:
                                   // http://ww1.microchip.com/downloads/en/DeviceDoc/60001108H.pdf#G1.1000176
    __builtin_enable_interrupts(); // XC32 macro to enable all interrupts:
                                   // http://ww1.microchip.com/downloads/en/DeviceDoc/50002509A.pdf#G1.791014

    // Sample Example: http://ww1.microchip.com/downloads/en/DeviceDoc/60001114G.pdf#G1.874207
    // Register Table: http://ww1.microchip.com/downloads/en/DeviceDoc/60001114G.pdf#G1.879241
    WDTCONbits.ON = 0b1; // Enables the Watchdog Timer if it is not enabled by the device configuration
    while (1) {
        WDTCONbits.WDTCLR = 0b1; // Writing a ?1? will clear the WDT
    }
    return EXIT_SUCCESS;
}
#else
#ifdef __APPLE__
#define TCGETS TIOCGETA
#define TCSETS TIOCSETA
#endif
/*! The start function `main` is the Linux implementation of Dot machine. */
int main(void) {
    srand(time(NULL)); // randomize.
    struct termios raw;
    struct termios normal;

    ioctl(STDIN_FILENO, TCGETS, &raw);
    ioctl(STDIN_FILENO, TCGETS, &normal);
    raw.c_lflag ^= (ECHO | ICANON | ISIG);
    raw.c_iflag ^= BRKINT;
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    ioctl(STDIN_FILENO, TCSETS, &raw);
    restart_mino();
    while (flush_board()) {
    }
    while (1) {
        Pad pad;
        int ret;

        pad.all = 0;
        ret = read(STDIN_FILENO, pad.buf, 3);
        if (ret <= 0 || pad.key == Esc) {
            break;
        } else {
            move_mino(pad);
            while (flush_board()) {
            }
        }
    }
    ioctl(STDIN_FILENO, TCSETS, &normal);
    return EXIT_SUCCESS;
}
#endif
