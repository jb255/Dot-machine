/*!
 * \file libmino.h
 * \version 1.0
 * \brief The module \a Tetromino is a tetromino interface.
 */

#ifndef LIBMINO_H
#define LIBMINO_H

#ifndef __XC32
#include "libtest.h"
#endif

#include "liboard.h"
#include "libtetro.h"

#ifndef __XC32
#include <stdlib.h>
#endif

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

/*! the macro `restart_mino` starts or restarts the game. */
#define restart_mino() \
    init_board();      \
    init_mino();

/*! the macro `oob_mino` respawn the piece or restarts the game
 * according to the y coordinate. */
#define oob_mino() \
        if (projection.cursor.bits.y) { \
            lock_mino(); \
            clear_mino(); \
            init_mino(); \
        } else { \
            restart_mino(); \
        }


#define down_mino() \
        if (projection.cursor.bits.y) { \
            lock_mino(); \
            clear_mino(); \
            init_mino(); \
        } else { \
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
        if ((next.piece.oob >> (projection.cursor.bits.x-1)) & 0b1
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
        return 0;
    } else {
        projection.tetro.piece.oob = next.oob;
        projection.cursor.bits.x -= 1;
        write_mino(before, projection.tetro.piece);
        return 1;
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
        return 0;
    } else {
        projection.tetro.piece.oob = next.oob;
        projection.cursor.bits.x += 1;
        write_mino(before, projection.tetro.piece);
        return 1;
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
        return 1;
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
}

/*! The function `clear_mino` clearing as many lines as possible. */
void clear_mino(void) {
    Line *line = (board.y_all + projection.cursor.bits.y);
    const Line *end = line + TETRO_Y_MAX;

    while (line <= &board.y_bits.line27 && line < end) {
        if (line->x_all == 0b11111111111) {
            clear_down_mino(line);
        }
        line++;
    }
}

#ifdef __XC32
/*! The function `init_mino` initialize a new piece. */
void init_mino(void) {
    projection.cursor.bits.x = 0;
    projection.cursor.bits.y = 0;
    projection.tetro = *(tetromino + 1);

    write_open_piece_mino(projection.cursor.bits.y, projection.tetro.piece);
}
#else
void init_mino(void) {
    const u8 index = rand() % TETRO_BLOCK_MAX * TETRO_DIRECTION_MAX;

    projection.cursor.bits.x = 0;
    projection.cursor.bits.y = 0;
    projection.tetro = *(tetromino + index);

    write_open_piece_mino(projection.cursor.bits.y, projection.tetro.piece);
}
#endif

/*! The main function `move_mino` moves the piece according to the pad. */
void move_mino(Pad pad) {
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
        if (!down_ok_mino()) {
            oob_mino();
        }
    }
}

#endif /* LIBMINO_H */
