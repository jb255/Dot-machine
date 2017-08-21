/*!
 * \file libmino.h
 * \version 1.0
 * \brief The module \a Tetromino is a tetromino interface.
 */

#ifndef LIBMINO_H
#define LIBMINO_H

#ifndef __XC32
#include <stdlib.h>
#else
#include <sys/attribs.h>
#endif

#include "configbits.h"
#include "liboard.h"
#include "libpad.h"
#include "libtetro.h"

/*! The constante \a \f$TETRO_Y_{MAX}\f$ is the line' limit of one piece . */
#define TETRO_Y_MAX 4

/*!
 * \union Polyomino
 * \brief The union \a Polyomino is a genecic interface to describe a projection.
 */
typedef struct Polyomino {
    Dot cursor;      /*! Location Cursor. */
    Tetromino tetro; /*! Piece's Type. */
} Polyomino;

/*! The mutable registry `projection` contains the current tetromino played. */
Polyomino projection;

/*! The macro `restart_mino` starts or restarts the game. */
#define restart_mino()     \
    buffer_dot.lenght = 0; \
    write_score(score);    \
    score = 0; \
    bonus = 0;

/*! the macro `oob_mino` respawn the piece or restarts the game
 *  * according to the y coordinate. */
#define oob_mino()   \
    if (projection.cursor.bits.y != 1) { \
        lock_mino();                \
        clear_mino();               \
        if (score >= 100) {         \
            win_score(); \
            score = 0; \
            bonus = 0; \
        } \
        init_mino(); \
    } \
    else { \
        restart_mino(); \
    }

/*! The function `write_line_mino` stacks a close or open's dot
 * from a line to the `buffer_dot` mutable global. */
void write_line_mino(Dot dot, Line buffer) {
    dot.bits.x = 0;
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

/*! The function `write_close_line_mino` stacks a close's dot
 * from a line to the `buffer_dot` mutable global. */
void write_close_line_mino(u8 y, Line buffer) {
    Dot dot;

    dot.bits.color = Close;
    dot.bits.y = y;
    write_line_mino(dot, buffer);
}

/*! The function `write_open_line_mino` stacks a open's dot
 * from a line to the `buffer_dot` mutable global. */
void write_open_line_mino(u8 y, Line buffer) {
    Dot dot;

    dot.bits.color = Open;
    dot.bits.y = y;
    write_line_mino(dot, buffer);
}

/*! The function `write_piece_mino` s a close or open's dot
 * from a line to the `buffer_dot` mutable global. */
void write_piece_mino(Dot dot, u8 y, Piece buffer) {
    dot.bits.y = y;
    while (dot.bits.y < y + TETRO_Y_MAX) {
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

#include "libwrite.h"

/*! The function `write_close_piece_mino` s a close's dot
 * from a line to the `buffer_dot` mutable global. */
void write_close_piece_mino(u8 y, Piece buffer) {
    Dot dot;

    dot.bits.color = Close;
    write_piece_mino(dot, y, buffer);
}

/*! The function `write_close_piece_mino` s a opeb's dot
 * from a line to the `buffer_dot` mutable global. */
void write_open_piece_mino(u8 y, Piece buffer) {
    Dot dot;

    dot.bits.color = Open;
    write_piece_mino(dot, y, buffer);
}

/*! The function `write_mino` generic moves a piece without flip unnecessary dots. */
void write_mino(Piece before, Piece after) {
    Piece buffer;

    buffer.oob = before.oob;
    buffer.oob &= ~(after.oob);
    write_close_piece_mino(projection.cursor.bits.y, buffer);

    buffer.oob = after.oob;
    buffer.oob &= ~(before.oob);
    write_open_piece_mino(projection.cursor.bits.y, buffer);
}

/*! The function `lock_mino` saves the piece to the board. */
void lock_mino(void) {
    Line *line = (board.y_all + projection.cursor.bits.y);

    (line + 0)->x_all |= projection.tetro.piece.bits.line0.x_all;
    (line + 1)->x_all |= projection.tetro.piece.bits.line1.x_all;
    (line + 2)->x_all |= projection.tetro.piece.bits.line2.x_all;
    (line + 3)->x_all |= projection.tetro.piece.bits.line3.x_all;
}

/*! The function `next_ok_mino` replaces the current piece by his next piece
 * from the constante global tetromino. */
u8 next_ok_mino(Tetromino next) {
    Piece before = projection.tetro.piece;
    Piece line;

    line.bits.line0 = *(board.y_all + projection.cursor.bits.y + 0);
    line.bits.line1 = *(board.y_all + projection.cursor.bits.y + 1);
    line.bits.line2 = *(board.y_all + projection.cursor.bits.y + 2);
    line.bits.line3 = *(board.y_all + projection.cursor.bits.y + 3);
    if (projection.cursor.bits.x >= 0) {
        if ((next.piece.oob >> (projection.cursor.bits.x - 1)) & 0b1
            || (next.piece.oob = (next.piece.oob >> projection.cursor.bits.x)) & line.oob) {
            return 0;
        } else {
            write_mino(before, next.piece);
            projection.tetro = next;
            return 1;
        }
    } else {
        if ((next.piece.oob = (next.piece.oob << (projection.cursor.bits.x * -1))) & line.oob) {
            return 0;
        } else {
            write_mino(before, next.piece);
            projection.tetro = next;
            return 1;
        }
    }
}

/*! The function `right_ok_mino` moves to right the current piece. */
u8 right_ok_mino() {
    Piece before = projection.tetro.piece;
    Piece next;
    Piece line;

    line.bits.line0 = *(board.y_all + projection.cursor.bits.y + 0);
    line.bits.line1 = *(board.y_all + projection.cursor.bits.y + 1);
    line.bits.line2 = *(board.y_all + projection.cursor.bits.y + 2);
    line.bits.line3 = *(board.y_all + projection.cursor.bits.y + 3);
    if ((next.oob = before.oob << 1) & line.oob) {
        return (0);
    } else {
        projection.tetro.piece.oob = next.oob;
        projection.cursor.bits.x -= 1;
        write_mino(before, projection.tetro.piece);
        return (1);
    }
}

/*! The function `left_ok_mino` moves to left the current piece. */
u8 left_ok_mino() {
    Piece before = projection.tetro.piece;
    Piece next;
    Piece line;

    line.bits.line0 = *(board.y_all + projection.cursor.bits.y + 0);
    line.bits.line1 = *(board.y_all + projection.cursor.bits.y + 1);
    line.bits.line2 = *(board.y_all + projection.cursor.bits.y + 2);
    line.bits.line3 = *(board.y_all + projection.cursor.bits.y + 3);
    if (before.bits.line0.x_bits.col0 == 0b1 || (next.oob = before.oob >> 1) & line.oob) {
        return (0);
    } else {
        projection.tetro.piece.oob = next.oob;
        projection.cursor.bits.x += 1;
        write_mino(before, projection.tetro.piece);
        return (1);
    }
}

/*! The function `end_ok_mino` moves to end the current piece. */
u8 end_ok_mino() {
    Piece before = projection.tetro.piece;
    Piece line;

    line.bits.line0 = *(board.y_all + projection.cursor.bits.y + 1);
    line.bits.line1 = *(board.y_all + projection.cursor.bits.y + 2);
    line.bits.line2 = *(board.y_all + projection.cursor.bits.y + 3);
    line.bits.line3 = *(board.y_all + projection.cursor.bits.y + 4);
    if (before.oob & line.oob) {
        return 0;
    } else {
        projection.cursor.bits.y += 1;
        return end_ok_mino();
    }
}

/*! The function `down_ok_mino` moves to down the current piece. */
u8 down_ok_mino() {
    Piece before = projection.tetro.piece;
    Piece line;

    line.bits.line0 = *(board.y_all + projection.cursor.bits.y + 1);
    line.bits.line1 = *(board.y_all + projection.cursor.bits.y + 2);
    line.bits.line2 = *(board.y_all + projection.cursor.bits.y + 3);
    line.bits.line3 = *(board.y_all + projection.cursor.bits.y + 4);
    if (before.oob & line.oob) {
        return (0);
    } else {
        if (projection.tetro.next == I_EW) {
            write_close_line_mino(projection.cursor.bits.y, projection.tetro.piece.bits.line0);
            projection.cursor.bits.y += 1;
            write_open_line_mino(projection.cursor.bits.y + 3, projection.tetro.piece.bits.line3);
        } else {
            Piece after;
            after.oob = (before.oob << 16);
            write_mino(before, after);
            projection.cursor.bits.y += 1;
        }
        return (1);
    }
}

/*! The function `clear_down_mino` moves to down the lines. */
void clear_down_mino(Line *line) {
    u8 y = line - &board.y_bits.line0;

    while (line >= &board.y_bits.line0) {
        Line open;
        Line close;

        open.x_all = ((line->x_all & (line - 1)->x_all) ^ line->x_all);
        write_close_line_mino(y, open);

        close.x_all = ((line->x_all | (line - 1)->x_all) ^ (line)->x_all);
        write_open_line_mino(y, close);

        line->x_all = (line - 1)->x_all;
        line--;
        y--;
    }
    if (game_speed > 10) {
        game_speed--;
    }
}

/*! The function `clear_mino` clearing as many lines as possible. */
void clear_mino(void) {
    Line *line = (board.y_all + projection.cursor.bits.y);
    const Line *end = line + TETRO_Y_MAX;

    while (line <= &board.y_bits.line27 && line < end) {
        if (line->x_all == 0b11111111111) {
            clear_down_mino(line);
            score++;
            bonus++;
        }
        line++;
    }
}

#ifdef __XC32
/*! The function `init_mino` initialize a new piece. */
void init_mino(void) {
    const u8 index = TMR5 % BLOCK_MAX;

    projection.cursor.bits.x = 0;
    projection.cursor.bits.y = 1;
    projection.tetro = *(tetromino + index);

    write_open_piece_mino(projection.cursor.bits.y, projection.tetro.piece);
}
#else
void init_mino(void) {
    const u8 index = rand() % BLOCK_MAX;

    projection.cursor.bits.x = 0;
    projection.cursor.bits.y = 1;
    projection.tetro = *(tetromino + index);

    write_open_piece_mino(projection.cursor.bits.y, projection.tetro.piece);
}
#endif

void move_down_mino(void) {
    if (!down_ok_mino()) {
        oob_mino();
    }
}

/*! The main function `move_mino` moves the piece according to the pad. */
void move_mino(Pad pad) {
    static Pad pad_pre;

    if (pad.key != pad_pre.key) {
        if (pad.key == End) {
            const u8 y = projection.cursor.bits.y;
            end_ok_mino();
            write_close_piece_mino(y, projection.tetro.piece);
            write_open_piece_mino(projection.cursor.bits.y, projection.tetro.piece);
            oob_mino();
        } else if (pad.key == Up) {
            next_ok_mino(tetromino[projection.tetro.next]);
        } else if (pad.key == Right) {
            right_ok_mino();
        } else if (pad.key == Left) {
            left_ok_mino();
        } else if (pad.key == Down) {
            move_down_mino();
        } /*else if (pad.key == Select) {
            OC1CONbits.ON = 0; // Disable Output Compare
            T3CONbits.ON = 0;  // Disable Timer
            start = 1;
            i = 0;
            j = 0;
            TMR2 = 0;
            TMR3 = 0;
            init_board();
            game = DOT;
            if (!mute) {
                T3CONbits.ON = 1; // Enable Timer
            }
        }*/ else if (pad.key == L2) {
            T3CONbits.ON = !T3CONbits.ON; // Enable or disable Timer
            if (T3CONbits.ON == 1) {
                mute = 0;
            }
            else {
                OC1CONbits.ON = 0;            // Disable Output Compare
                mute = 1;
            }
            i = 0;
            TMR2 = 0;
            TMR3 = 0;
            start = 1;
        }
    }
    pad_pre.key = pad.key;
}

void move_mino2(Pad pad) {
    static Pad pad_pre2;

    if (pad.key != pad_pre2.key) {
        if (pad.key == Triangle) {
            next_ok_mino(tetromino[projection.tetro.next]);

        } else if (pad.key == Square) {
            right_ok_mino();

        } else if (pad.key == Circle) {
            left_ok_mino();

        } else if (pad.key == Cross) {
            move_down_mino();
        }
    }
    pad_pre2.key = pad.key;
}

#ifdef __XC32

void dot(Pad pad) {
    static Dot dot;
    static Pad pad_pre;

    if (pad.key != pad_pre.key) {
     /*   if (pad.key == Left && dot.bits.x > 0) {
            dot.bits.x--;
        }

        else if (pad.key == Up && dot.bits.y > 0) {
            dot.bits.y--;
        }

        else if (pad.key == Right && dot.bits.x < 10) {
            dot.bits.x++;
        }

        else if (pad.key == Down && dot.bits.y < 27) {
            dot.bits.y++;
        }
*/
        if (pad.key == Start && game != TETRIS) {
            OC1CONbits.ON = 0; // Disable Output Compare
            T3CONbits.ON = 0;  // Disable Timer
            start = 1;
            i = 0;
            j = 0;
            TMR2 = 0;
            TMR3 = 0;
            init_board();
            game = TETRIS;
            if (!mute) {
                T3CONbits.ON = 1; // Enable Timer
            }
            init_mino();
        }
/*
        else if (pad.key == Square) {
            write_buffer_open((board.y_all + dot.bits.y), dot);
        }

        else if (pad.key == L2) {
            T3CONbits.ON = !T3CONbits.ON; // Enable or disable Time
            if (T3CONbits.ON == 1) {
                mute = 0;
            }
            else {
                mute = 1;
                OC1CONbits.ON = 0;            // Disable Output Compare
            }
            i = 0;
            TMR2 = 0;
            TMR3 = 0;
            start = 1;
        }

        else if (pad.key == Cross) {
            write_buffer_close((board.y_all + dot.bits.y), dot);
        }

        else if (pad.key == Circle) {
            write_title();
        }

        else if (pad.key == L1) {
            OC1CONbits.ON = 0; // Disable Output Compare
            yellow_board();
        }

        else if (pad.key == R1) {
            OC1CONbits.ON = 0; // Disable Output Compare
            init_board();
        }*/
    }
    pad_pre.key = pad.key;
    if (game == NOGAME)
        game = DOT;
}

void restart(Pad pad) {
    if (pad.key == Start) {
        OC1CONbits.ON = 0; // Disable Output Compare
        T3CONbits.ON = 0;  // Disable Timer
        i = 0;
        j = 0;
        TMR2 = 0;
        TMR3 = 0;
        init_board();
        game = TETRIS;
        if (!mute) {
            T3CONbits.ON = 1; // Enable Timer
        }
        init_mino();
    }
/*
    else if (pad.key == Select) {
        OC1CONbits.ON = 0; // Disable Output Compare
        T3CONbits.ON = 0;  // Disable Timer
        i = 0;
        j = 0;
        TMR2 = 0;
        TMR3 = 0;
        init_board();
        game = DOT;
        if (!mute) {
            T3CONbits.ON = 1; // Enable Timer
        }
    }*/
}
void padx() {
    Pad pad;
    Pad pad2;
    u8 __attribute__((__unused__)) data;

    // SPI
    LATAbits.LATA0 = 1;
    LATAbits.LATA0 = 0;

    SPI1BUF = 0b10000000; // Transmit 1 in Little Endian
    while (SPI1STATbits.SPIBUSY == 1) {
    }
    data = SPI1BUF;

    // 2
    SPI1BUF = 0b01000010; // Transmit 42
    while (SPI1STATbits.SPIBUSY == 1) {
    }
    pad.buf.data2 = SPI1BUF;

    // 3
    SPI1BUF = 0; // Transmit 0
    while (SPI1STATbits.SPIBUSY == 1) {
    }
    data = SPI1BUF;

    // 4
    SPI1BUF = 0; // Transmit 0
    while (SPI1STATbits.SPIBUSY == 1) {
    }
    pad.buf.data4 = SPI1BUF;

    // 5
    SPI1BUF = 0; // Transmit 0
    while (SPI1STATbits.SPIBUSY == 1) {
    }
    pad.buf.data5 = SPI1BUF;

    // UART
    static Pad pad_pre;
    pad2.key = Nothing;
    if (pad_pre.key != pad.key)
    {
        pad_pre.key = pad.key;
        if (bonus > 0)
        {
            if (pad.key == Triangle || pad.key == Square || pad.key == Circle || pad.key == Cross)
            {
                bonus--;
                pad2.key = pad.key;
            }
         }
     }
    U1TXREG = pad2.buf.data4;
    while (U1STAbits.TRMT == 0) {
    }
    while (U1STAbits.RIDLE == 0) {
    }
    if (U1STAbits.URXDA == 1) {
    }
    pad2.buf.data4 = U1RXREG;

    U1TXREG = pad2.buf.data5;
    while (U1STAbits.TRMT == 0) {
    }
    while (U1STAbits.RIDLE == 0) {
    }
    if (U1STAbits.URXDA == 1) {
    }
    pad2.buf.data5 = U1RXREG;

    U1STAbits.UTXEN = 0; // Reset Uart transmit buffer
    U1STAbits.UTXEN = 1; // Enbale Uart transmit




    if (game == NOGAME) {
    } else if (game == DOT) {
        dot(pad);
    } else if (game == TETRIS) {
        move_mino(pad);
        move_mino2(pad2);
    } else if (game == FAIL || WIN) {
        restart(pad);
    }
}

#endif /* XC32 */

#endif /* LIBMINO_H */
