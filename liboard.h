/*!
 * \file liboard.h
 * \version 1.0
 * \brief The module \a Board is a tetris interface.
 */

#ifndef LIBOARD_H
#define LIBOARD_H

#include "libdriver.h"
#include "configbits.h"

/*!
 * \union Line
 * \brief The structure \a Line describes a \f$ 11 \f$'s line representation.
 */
typedef union Line {
    struct {
        bool col0 : 1;  /*! X_0 */
        bool col1 : 1;  /*! X_1 */
        bool col2 : 1;  /*! X_2 */
        bool col3 : 1;  /*! X_3 */
        bool col4 : 1;  /*! X_4 */
        bool col5 : 1;  /*! X_5 */
        bool col6 : 1;  /*! X_6 */
        bool col7 : 1;  /*! X_7 */
        bool col8 : 1;  /*! X_8 */
        bool col9 : 1;  /*! X_9 */
        bool col10 : 1; /*! X_10 */
        u8 oob : 5;     /*! Out of bound. */
    } x_bits;
    u16 x_all : X_MAX;
    u16 oob : 16; /*! Out of bound. */
} Line;

/*!
 * \union Board
 * \brief The union \a Board describes a \f$ 28 \times 11 \f$'s board representation.
 */
typedef union Board {
    struct {
        Line line0;  /*! Y_0 */
        Line line1;  /*! Y_1 */
        Line line2;  /*! Y_2 */
        Line line3;  /*! Y_3 */
        Line line4;  /*! Y_4 */
        Line line5;  /*! Y_5 */
        Line line6;  /*! Y_6 */
        Line line7;  /*! Y_7 */
        Line line8;  /*! Y_8 */
        Line line9;  /*! Y_9 */
        Line line10; /*! Y_10 */
        Line line11; /*! Y_11 */
        Line line12; /*! Y_12 */
        Line line13; /*! Y_13 */
        Line line14; /*! Y_14 */
        Line line15; /*! Y_15 */
        Line line16; /*! Y_16 */
        Line line17; /*! Y_17 */
        Line line18; /*! Y_18 */
        Line line19; /*! Y_19 */
        Line line20; /*! Y_20 */
        Line line21; /*! Y_21 */
        Line line22; /*! Y_22 */
        Line line23; /*! Y_23 */
        Line line24; /*! Y_24 */
        Line line25; /*! Y_25 */
        Line line26; /*! Y_26 */
        Line line27; /*! Y_27 */
        Line oob;    /*! Out of bound. */
    } y_bits;
    Line y_all[Y_MAX];
} Board;

/*! The mutable registry \a board contains the orthonormal list of cells as \f$ 28 \f$ sectors and \f$ 11 \f$
 * sub-sectors. */
Board board;

/*! The macro `write_board_open` updates the dot from mutable \a board as open without check the overflow. */
#define write_board_open(line, dot) line->x_all |= 1 << dot.bits.x

/*! The macro `write_board_close` updates the dot from mutable \a board as close without check the overflow. */
#define write_board_close(line, dot) \
    line->x_all = ~line->x_all;      \
    line->x_all |= 1 << dot.bits.x;  \
    line->x_all = ~line->x_all;

/*! The macro `write_buffer_open` updates the dot from mutable \a board as open and stacks it to the buffer */
#define write_buffer_open(line, dot)                 \
    dot.bits.color = Open;                           \
    write_board_open(line, dot);                     \
    *(buffer_dot.content + buffer_dot.lenght) = dot; \
    if (buffer_dot.lenght < BUFF_MAX) {              \
        buffer_dot.lenght += 1;                      \
    }

/*! The macro `write_buffer_close` updates the dot from mutable \a board as close and stacks it to the buffer */
#define write_buffer_close(line, dot)                \
    dot.bits.color = Close;                          \
    write_board_close(line, dot);                    \
    *(buffer_dot.content + buffer_dot.lenght) = dot; \
    if (buffer_dot.lenght < BUFF_MAX) {              \
        buffer_dot.lenght += 1;                      \
    }

/*! The test function `yellow_board` yellows the board !. */
void yellow_board(void) {
    Dot piece;

    game = NOGAME;
    piece.bits.y = 0;
    while (piece.bits.y < Y_MAX) {
        piece.bits.x = 0;
        while (piece.bits.x < X_MAX) {
            Line *line = board.y_all + piece.bits.y;
            write_buffer_open(line, piece);
            piece.bits.x += 1;
        }
        piece.bits.y += 1;
    }
}

/*! The function `init_board` initializes a new board. */
void init_board(void) {
    Dot piece;

    game = NOGAME;
    piece.bits.y = 0;
    while (piece.bits.y < Y_MAX) {
        piece.bits.x = 0;
        while (piece.bits.x < X_MAX) {
            Line *line = board.y_all + piece.bits.y;

            line->x_bits.oob = 0b11111;
            write_buffer_close(line, piece);
            piece.bits.x += 1;
        }
        piece.bits.y += 1;
    }
    board.y_bits.oob.oob = 0b1111111111111111;
}

#endif /* LIBOARD.H */
