/*!
 * \file music.h
 * \version 1.0
 * \brief The module \a Music is the sound interface.
 */

#ifndef MUSIC_H
#define MUSIC_H

#ifdef __XC32
// Music
#define GRAVE 3
#define AIGUE 1.5

#define DOA 59 * AIGUE
#define DOA2 56 * AIGUE
#define REA 53 * AIGUE
#define REA2 50 * AIGUE
#define MIA 47 * AIGUE
#define FAA 45 * AIGUE
#define FAA2 42 * AIGUE
#define SOLA 40 * AIGUE
#define SOLA2 38 * AIGUE
#define LAA 36 * AIGUE
#define LAA2 34 * AIGUE
#define SIA 32 * AIGUE

#define DO DOA * 2     // 59 * GRAVE //(4186.01 Hz)
#define DO2 DOA2 * 2   // 56 * GRAVE //(4434.92 Hz)
#define RE REA * 2     // 53 * GRAVE //(4698.64 Hz)
#define RE2 REA2 * 2   // 50 * GRAVE //(4978.03 Hz)
#define MI MIA * 2     // 47 * GRAVE //(5274.04 Hz)
#define FA FAA * 2     // 45 * GRAVE //(5587.65 Hz)
#define FA2 FAA2 * 2   // 42 * GRAVE //(5919.91 Hz)
#define SOL SOLA * 2   // 40 * GRAVE //(6271.93 Hz)
#define SOL2 SOLA2 * 2 // 38 * GRAVE //(6644.88 Hz)
#define LA LAA * 2     // 36 * GRAVE //(7040.00 Hz)
#define LA2 LAA2 * 2   // 34 * GRAVE //(7458.62 Hz)
#define SI SIA * 2     // 32 * GRAVE //(7902.13 Hz)

#define DOUBLE 0xABFE
#define DEMI 0x2AFF
#define NOIR 0x55FF

void fail_music() {
    static int game_over_music[] = {DOA, SOL, MI, LA, SI, LA2, LA, LA2, LA, SOL, RE, MI, DO, 0};
    static int game_over_tempo[]
        = {DOUBLE, DOUBLE, NOIR, DEMI, NOIR, DEMI, DEMI, NOIR, DEMI, DEMI, DEMI, DOUBLE, DEMI, 0};

    if (OC1CONbits.ON) {
        TMR2 = 0;
        PR2 = game_over_music[i];
        PR3 = game_over_tempo[i] / 1.2;
        i++;
    }

    if (OC1CONbits.ON && (!game_over_music[i] || !game_over_tempo[i])) {
        i = 0;
        PR3 = DOUBLE;
        T3CONbits.ON = 0;
        OC1CONbits.ON = 0; // Disable Output Compare
    }
}

void win_music() {
    static int victory_music[] = {SOL * 2, DO,      RE, DO, RE, MI, SOL, MI,  SOL2 * 2, DO,  RE2, DO,  RE2, SOL, SOL2,
                                  RE2,     LA2 * 2, RE, FA, RE, FA, LA,  LA2, LA2,      LA2, LA2, DOA, DO,  0};
    static int victory_tempo[]
        = {DEMI,   DEMI, DEMI, DEMI, DEMI, DEMI, NOIR, DOUBLE, DEMI, DEMI, DEMI, DEMI,   DEMI, DEMI, NOIR,
           DOUBLE, DEMI, DEMI, DEMI, DEMI, DEMI, DEMI, DOUBLE, DEMI, DEMI, DEMI, DOUBLE, DEMI, 0};

    if (OC1CONbits.ON) {
        TMR2 = 0;
        PR2 = victory_music[i];
        PR3 = victory_tempo[i];
        i++;
    }

    if (OC1CONbits.ON && (!victory_music[i] || !victory_tempo[i])) {
        i = 0;
        PR3 = DOUBLE;
        T3CONbits.ON = 0;
        OC1CONbits.ON = 0; // Disable Output Compare
    }
}

void music_start() {
    static int start_music[] = {MI, MI, MI, DO, MI, SOL, SOL * 2, DO, 0};
    static int tempo_start[] = {DEMI, NOIR, NOIR, DEMI, NOIR, DOUBLE, DOUBLE, DEMI, 0};

    if (OC1CONbits.ON) {
        TMR2 = 0;
        PR2 = start_music[i];
        PR3 = tempo_start[i] / 1.2;
        i++;
    }

    if (OC1CONbits.ON && (!start_music[i] || !tempo_start[i])) {
        i = 0;
        start = 1;
        PR3 = DOUBLE;
        T3CONbits.ON = 0;
        OC1CONbits.ON = 0;
    }
}

void music_tetris() {
    static int tetris[] = {MI, SI * 2, DO, RE,     DO,     SI * 2, LA * 2, LA * 2, DO, MI, RE, DO, SI * 2, SI * 2, DO,
                           RE, MI,     DO, LA * 2, LA * 2, LA * 2, SI * 2, DO,     RE, RE, FA, LA, LA,     SOL,    FA,
                           MI, DO,     MI, MI,     RE,     DO,     SI * 2, SI * 2, DO, RE, MI, DO, LA * 2, LA * 2, 0};
    static int tetris2[]
        = {MI,     MI, DO, DO, RE, RE, SI * 2, SI * 2, DO,     DO,     LA * 2, LA * 2, SOL2 * 2, SOL2 * 2, SI * 2,
           SI * 2, MI, MI, DO, DO, RE, RE,     SI * 2, SI * 2, LA * 2, MI,     LA,     SOL2,     SOL2,     0};
    static int tempo_tetris2[]
        = {NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, NOIR,   NOIR,   NOIR,   NOIR,
           NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, NOIR, DOUBLE, DOUBLE, DOUBLE, 0};
    static int tempo_tetris[]
        = {NOIR, DEMI, DEMI, NOIR, DEMI, DEMI, NOIR, DEMI, DEMI, NOIR, DEMI, DEMI, NOIR, DEMI,   DEMI,
           NOIR, NOIR, NOIR, NOIR, DEMI, DEMI, DEMI, DEMI, DEMI, NOIR, DEMI, DEMI, DEMI, DEMI,   DEMI,
           NOIR, NOIR, DEMI, DEMI, DEMI, DEMI, NOIR, DEMI, DEMI, NOIR, NOIR, NOIR, NOIR, DOUBLE, 0};

    if (OC1CONbits.ON) {
        TMR2 = 0;
        if (j < 2) {
            PR2 = tetris[i];
            PR3 = tempo_tetris[i];
        } else {
            PR2 = tetris2[i];
            PR3 = tempo_tetris2[i];
        }
        i++;
    }

    if (OC1CONbits.ON
        && ((j < 2 && (!tetris[i] || !tempo_tetris[i])) || (j >= 2 && (!tetris2[i] || !tempo_tetris2[i])))) {
        i = 0;
        j++;
        if (j >= 3) {
            j = 0;
        }
    }
}

void music_dot() {
    static int dot1[] = {RE, LA,     SOL, LA,     FA, LA,  MI, LA, RE, LA,  DO2, LA, RE, LA, MI, LA, FA,
                         LA, LA * 2, LA,  SI * 2, LA, DO2, LA, RE, LA, DO2, LA,  RE, LA, MI, LA, 0};
    static int dot2[] = {RE, LA, SOL, LA,  FA, LA, MI, LA, RE, LA, MI, LA, FA, LA,  RE, LA, MI,
                         LA, FA, LA,  SOL, LA, MI, LA, FA, LA, RE, LA, MI, LA, DO2, LA, 0};
    static int dot3[] = {RE,  LA, SOL, LA,  FA,  LA, MI,  LA, RE,  LA2, LAA, LA2, SOL, LA2, FA,  LA2, MI,
                         LA2, LA, LA2, SOL, LA2, FA, LA2, MI, LA2, RE,  LA2, DO2, LA2, MI,  LA2, 0};

    PR3 = DEMI / 1.5;

    if (OC1CONbits.ON) {
        TMR2 = 0;
        if (j == 0 || j == 2) {
            PR2 = dot1[i];
        }
        if (j == 1) {
            PR2 = dot2[i];
        }
        if (j == 3) {
            PR2 = dot3[i];
        }
        i++;
    }
    if (OC1CONbits.ON && (((!j || j == 2) && !dot1[i]) || (j == 1 && !dot2[i]) || (j == 3 && !dot3[i]))) {
        i = 0;
        j++;
        if (j >= 4) {
            j = 0;
        }
    }
}
#endif /* XC32 */

#endif /* MUSIC_H */
