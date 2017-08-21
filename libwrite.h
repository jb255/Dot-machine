#ifndef LIBWRITE_H /* Guard against multiple inclusion */
#define LIBWRITE_H

#define LEFT 4
#define UNIT 8

#define LINE1 0
#define LINE2 7
#define LINE3 14
#define LINE4 21

typedef union Characters {
    struct {
        Line line0; /*! Line 0. */
        Line line1; /*! Line 1. */
        Line line2; /*! Line 2. */
        Line line3; /*! Line 3. */
        Line line4; /*! Line 4. */
    } bits;
    u64 oob : 64; /*! Out of bound. */
} Characters;

/*****************NUMBERS*************************************************/
Characters zero = {.bits = {.line0 = {.x_all = 0b11100000000},
                            .line1 = {.x_all = 0b10100000000},
                            .line2 = {.x_all = 0b10100000000},
                            .line3 = {.x_all = 0b10100000000},
                            .line4 = {.x_all = 0b11100000000}}};

Characters one = {.bits = {.line0 = {.x_all = 0b01000000000},
                           .line1 = {.x_all = 0b11000000000},
                           .line2 = {.x_all = 0b01000000000},
                           .line3 = {.x_all = 0b01000000000},
                           .line4 = {.x_all = 0b11100000000}}};

Characters two = {.bits = {.line0 = {.x_all = 0b11100000000},
                           .line1 = {.x_all = 0b00100000000},
                           .line2 = {.x_all = 0b11100000000},
                           .line3 = {.x_all = 0b10000000000},
                           .line4 = {.x_all = 0b11100000000}}};

Characters three = {.bits = {.line0 = {.x_all = 0b11100000000},
                             .line1 = {.x_all = 0b00100000000},
                             .line2 = {.x_all = 0b11100000000},
                             .line3 = {.x_all = 0b00100000000},
                             .line4 = {.x_all = 0b11100000000}}};

Characters four = {.bits = {.line0 = {.x_all = 0b10000000000},
                            .line1 = {.x_all = 0b10100000000},
                            .line2 = {.x_all = 0b11100000000},
                            .line3 = {.x_all = 0b00100000000},
                            .line4 = {.x_all = 0b00100000000}}};

Characters five = {.bits = {.line0 = {.x_all = 0b11100000000},
                            .line1 = {.x_all = 0b10000000000},
                            .line2 = {.x_all = 0b11100000000},
                            .line3 = {.x_all = 0b00100000000},
                            .line4 = {.x_all = 0b11100000000}}};

Characters six = {.bits = {.line0 = {.x_all = 0b11100000000},
                           .line1 = {.x_all = 0b10000000000},
                           .line2 = {.x_all = 0b11100000000},
                           .line3 = {.x_all = 0b10100000000},
                           .line4 = {.x_all = 0b11100000000}}};

Characters seven = {.bits = {.line0 = {.x_all = 0b11100000000},
                             .line1 = {.x_all = 0b00100000000},
                             .line2 = {.x_all = 0b00100000000},
                             .line3 = {.x_all = 0b00100000000},
                             .line4 = {.x_all = 0b00100000000}}};

Characters eight = {.bits = {.line0 = {.x_all = 0b11100000000},
                             .line1 = {.x_all = 0b10100000000},
                             .line2 = {.x_all = 0b11100000000},
                             .line3 = {.x_all = 0b10100000000},
                             .line4 = {.x_all = 0b11100000000}}};

Characters nine = {.bits = {.line0 = {.x_all = 0b11100000000},
                            .line1 = {.x_all = 0b10100000000},
                            .line2 = {.x_all = 0b11100000000},
                            .line3 = {.x_all = 0b00100000000},
                            .line4 = {.x_all = 0b11100000000}}};

/*************************WORDS**********************************************/
Characters title = {.bits = {.line0 = {.x_all = 0b11001110111},
                             .line1 = {.x_all = 0b10101010010},
                             .line2 = {.x_all = 0b10101010010},
                             .line3 = {.x_all = 0b10101010010},
                             .line4 = {.x_all = 0b11001110010}}};

Characters forty_two = {.bits = {.line0 = {.x_all = 0b01000011100},
                                 .line1 = {.x_all = 0b01010000100},
                                 .line2 = {.x_all = 0b01111011100},
                                 .line3 = {.x_all = 0b00010010000},
                                 .line4 = {.x_all = 0b00010011100}}};

Characters sco = {.bits = {.line0 = {.x_all = 0b11101110111},
                           .line1 = {.x_all = 0b10001000101},
                           .line2 = {.x_all = 0b11101000101},
                           .line3 = {.x_all = 0b00101000101},
                           .line4 = {.x_all = 0b11101110111}}};

Characters re = {.bits = {.line0 = {.x_all = 0b11100111000},
                          .line1 = {.x_all = 0b10100100000},
                          .line2 = {.x_all = 0b11000111000},
                          .line3 = {.x_all = 0b10100100000},
                          .line4 = {.x_all = 0b10100111000}}};

Characters win = {.bits = {.line0 = {.x_all = 0b10001010000},
                           .line1 = {.x_all = 0b10001000110},
                           .line2 = {.x_all = 0b10101010101},
                           .line3 = {.x_all = 0b10101010101},
                           .line4 = {.x_all = 0b01110010101}}};

Characters hundred = {.bits = {.line0 = {.x_all = 0b01001110111},
                               .line1 = {.x_all = 0b11001010101},
                               .line2 = {.x_all = 0b01001010101},
                               .line3 = {.x_all = 0b01001010101},
                               .line4 = {.x_all = 0b11101110111}}};

Characters exclamation = {.bits = {.line0 = {.x_all = 0b01000100010},
                                   .line1 = {.x_all = 0b01000100010},
                                   .line2 = {.x_all = 0b01000100010},
                                   .line3 = {.x_all = 0b00000000000},
                                   .line4 = {.x_all = 0b01000100010}}};

void write_characters_score(Dot dot, u8 y, u8 x, Characters buffer) {
    dot.bits.y = y;
    while (dot.bits.y < y + 5) {
        dot.bits.x = 0;
        while (dot.bits.x < X_MAX) {
            if (buffer.oob & 0b1) {
                dot.bits.x -= x;
                *(buffer_dot.content + buffer_dot.lenght) = dot;
                if (buffer_dot.lenght < BUFF_MAX) {
                    buffer_dot.lenght += 1;
                    dot.bits.x += x;
                }
            }
            buffer.oob >>= 1;
            dot.bits.x += 1;
        }
        buffer.oob >>= 5;
        dot.bits.y += 1;
    }
}

void write_characters(Dot dot, u8 y, Characters buffer) {
    dot.bits.y = y;
    while (dot.bits.y < y + 5) {
        dot.bits.x = 0;
        while (dot.bits.x < X_MAX) {
            if (buffer.oob & 0b1) {
                *(buffer_dot.content + buffer_dot.lenght) = dot;
                if (buffer_dot.lenght < BUFF_MAX) {
                    buffer_dot.lenght += 1;
                }
            }
            buffer.oob >>= 1;
            dot.bits.x += 1;
        }
        buffer.oob >>= 5;
        dot.bits.y += 1;
    }
}

void write_line(Dot dot, u8 x, Line buffer) {
    dot.bits.x = -x;
    while (dot.bits.x < X_MAX) {
        if (buffer.x_all & 0b1) {
            *(buffer_dot.content + buffer_dot.lenght) = dot;
            if (buffer_dot.lenght < BUFF_MAX) {
                buffer_dot.lenght += 1;
            }
        }
        buffer.x_all >>= 1;
        dot.bits.x += 1;
    }
}

void write_title() {
    Dot dot;
    dot.bits.color = Open;

    write_characters(dot, LINE2, title);
    dot.bits.y = LINE2 + 4;
    write_line_mino(dot, title.bits.line4);

    write_characters(dot, LINE3, forty_two);
    dot.bits.y = LINE3 + 4;
    write_line_mino(dot, forty_two.bits.line4);

    game = DOT;
}

void write_score(u8 score) {
    Dot dot;
    dot.bits.color = Open;
    u8 decimal_place = UNIT;
    Characters tab[] = {zero, one, two, three, four, five, six, seven, eight, nine};

    T3CONbits.ON = 0;
    OC1CONbits.ON = 0;
    init_board();

    write_characters(dot, LINE1, sco);
    dot.bits.y = LINE1 + 4;
    write_line_mino(dot, sco.bits.line4);

    write_characters(dot, LINE2, re);
    dot.bits.y = LINE2 + 4;
    write_line_mino(dot, re.bits.line4);

    if (!score) {
        write_characters_score(dot, LINE3, decimal_place, zero);
        dot.bits.y = LINE3 + 4;
        write_line(dot, UNIT, zero.bits.line4);
    }

    while (score > 0) {
        write_characters_score(dot, LINE3, decimal_place, tab[score % 10]);
        dot.bits.y = LINE3 + 4;
        write_line(dot, decimal_place, tab[score % 10].bits.line4);
        score /= 10;
        decimal_place -= LEFT;
    }
    
    game = FAIL;
    i = 0;
    TMR2 = 0;
    TMR3 = 0;
    if (!mute){
    T3CONbits.ON = 1; // Enable Timer
    }
}

void win_score() {
    Dot dot;
    dot.bits.color = Open;

    T3CONbits.ON = 0;
    OC1CONbits.ON = 0;
    init_board();

    write_characters(dot, LINE1, win);
    dot.bits.y = LINE1 + 4;
    write_line_mino(dot, win.bits.line4);

    write_characters(dot, LINE2, exclamation);
    dot.bits.y = LINE2 + 4;
    write_line_mino(dot, exclamation.bits.line4);

    write_characters(dot, LINE3, hundred);
    dot.bits.y = LINE3 + 4;
    write_line_mino(dot, hundred.bits.line4);
    
    game = WIN;
    i = 0;
    TMR2 = 0;
    TMR3 = 0;
    if (!mute){
        T3CONbits.ON = 1; // Enable Timer
    }
}

#endif /* LIBWRITE_H */