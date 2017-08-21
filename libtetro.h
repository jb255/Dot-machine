/*!
 * \file libtetro.h
 * \version 1.0
 * \brief The module \a Tetromino is a tetromino interface.
 */

#ifndef LIBTETRO_H
#define LIBTETRO_H

/*!
 * \enum Block
 * \brief The enumeration \a Block Tetromino lists the piece types.
 */
typedef enum Block {
    I = 'I', /*! I-tetronimo. */
    J = 'J', /*! J-tetronimo. */
    L = 'L', /*! L-Tetrimino. */
    O = 'O', /*! O-Tetrimino. */
    S = 'S', /*! S-tetronimo. */
    T = 'T', /*! T-tetronimo. */
    Z = 'Z', /*! Z-tetronimo. */
} Block;

/*!
 * \union Piece
 * \brief The union \a Piece describes a 4 bytes data piece limited at four lines.
 */
typedef union Piece {
    struct {
        Line line0; /*! Line 0. */
        Line line1; /*! Line 1. */
        Line line2; /*! Line 2. */
        Line line3; /*! Line 3. */
    } bits;
    u64 oob : 64; /*! Out of bound. */
} Piece;

/*!
 * \enum BlockDirection
 * \brief The enumeration \a BlockDirection defines the list possibility pieces.
 */

typedef enum BlockDirection {
    I_EW2,
    I_NS2,
    I_EW,
    I_NS,
    J_W,
    J_S,
    J_E,
    J_N,
    L_W,
    L_S,
    L_E,
    L_N,
    O_NESW,
    O_NESW2,
    O_NESW3,
    O_NESW4,
    S_NS,
    S_EW,
    S_NS2,
    S_EW2,
    T_S,
    T_W,
    T_N,
    T_E,
    Z_NS,
    Z_EW,
    Z_NS2,
    Z_EW2,
    BLOCK_MAX,
} BlockDirection;

/*!
 * \struct BlockDirection
 * \brief The structure \a Tetromino is a data couple of piece, block and direction block who describe a piece.
 */
typedef struct Tetromino {
    Piece piece;
    Block block;
    BlockDirection next;
} Tetromino;

// clang-format off

/*! The mutable registry `projection` contains list of tetromino
 * according to the order enumeration BlockDirection. */
Tetromino tetromino[BLOCK_MAX] = {
    { .block = I, .piece = { .bits = {
        .line0 = { .x_all = 0b00000000000 },
        .line1 = { .x_all = 0b00011110000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = I_NS },
    { .block = I, .piece = { .bits = {
        .line0 = { .x_all = 0b00001000000 },
        .line1 = { .x_all = 0b00001000000 },
        .line2 = { .x_all = 0b00001000000 },
        .line3 = { .x_all = 0b00001000000 }
    } }, .next = I_EW },
    { .block = I, .piece = { .bits = {
        .line0 = { .x_all = 0b00000000000 },
        .line1 = { .x_all = 0b00011110000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = I_NS },
    { .block = I, .piece = { .bits = {
        .line0 = { .x_all = 0b00001000000 },
        .line1 = { .x_all = 0b00001000000 },
        .line2 = { .x_all = 0b00001000000 },
        .line3 = { .x_all = 0b00001000000 }
    } }, .next = I_EW },

    { .block = J, .piece = { .bits = {
        .line0 = { .x_all = 0b00000000000 },
        .line1 = { .x_all = 0b00001110000 },
        .line2 = { .x_all = 0b00001000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = J_N },
    { .block = J, .piece = { .bits = {
        .line0 = { .x_all = 0b00001100000 },
        .line1 = { .x_all = 0b00000100000 },
        .line2 = { .x_all = 0b00000100000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = J_W },
    { .block = J, .piece = { .bits = {
        .line0 = { .x_all = 0b00000010000 },
        .line1 = { .x_all = 0b00001110000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = J_S },
    { .block = J, .piece = { .bits = {
        .line0 = { .x_all = 0b00000100000 },
        .line1 = { .x_all = 0b00000100000 },
        .line2 = { .x_all = 0b00000110000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = J_E },
    { .block = L, .piece = { .bits = {
        .line0 = { .x_all = 0b00000000000 },
        .line1 = { .x_all = 0b00001110000 },
        .line2 = { .x_all = 0b00000010000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = L_N },
    { .block = L, .piece = { .bits = {
        .line0 = { .x_all = 0b00000110000 },
        .line1 = { .x_all = 0b00000100000 },
        .line2 = { .x_all = 0b00000100000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = L_W },
    { .block = L, .piece = { .bits = {
        .line0 = { .x_all = 0b00001000000 },
        .line1 = { .x_all = 0b00001110000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = L_S },
    { .block = L, .piece = { .bits = {
        .line0 = { .x_all = 0b00000100000 },
        .line1 = { .x_all = 0b00000100000 },
        .line2 = { .x_all = 0b00001100000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = L_E },
    { .block = O, .piece = { .bits = {
        .line0 = { .x_all = 0b00001100000 },
        .line1 = { .x_all = 0b00001100000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = O_NESW },
    { .block = O, .piece = { .bits = {
        .line0 = { .x_all = 0b00001100000 },
        .line1 = { .x_all = 0b00001100000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = O_NESW },
    { .block = O, .piece = { .bits = {
        .line0 = { .x_all = 0b00001100000 },
        .line1 = { .x_all = 0b00001100000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = O_NESW },
    { .block = O, .piece = { .bits = {
        .line0 = { .x_all = 0b00001100000 },
        .line1 = { .x_all = 0b00001100000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = O_NESW },
    { .block = S, .piece = { .bits = {
        .line0 = { .x_all = 0b00011000000 },
        .line1 = { .x_all = 0b00001100000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = S_EW },
    { .block = S, .piece = { .bits = {
        .line0 = { .x_all = 0b00000100000 },
        .line1 = { .x_all = 0b00001100000 },
        .line2 = { .x_all = 0b00001000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = S_NS },
    { .block = S, .piece = { .bits = {
        .line0 = { .x_all = 0b00011000000 },
        .line1 = { .x_all = 0b00001100000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = S_EW },
    { .block = S, .piece = { .bits = {
        .line0 = { .x_all = 0b00000100000 },
        .line1 = { .x_all = 0b00001100000 },
        .line2 = { .x_all = 0b00001000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = S_NS },
    { .block = T, .piece = { .bits = {
        .line0 = { .x_all = 0b00000000000 },
        .line1 = { .x_all = 0b00001110000 },
        .line2 = { .x_all = 0b00000100000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = T_W },
    { .block = T, .piece = { .bits = {
        .line0 = { .x_all = 0b00000100000 },
        .line1 = { .x_all = 0b00001100000 },
        .line2 = { .x_all = 0b00000100000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = T_N },
    { .block = T, .piece = { .bits = {
        .line0 = { .x_all = 0b00000100000 },
        .line1 = { .x_all = 0b00001110000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = T_E },
    { .block = T, .piece = { .bits = {
        .line0 = { .x_all = 0b00000100000 },
        .line1 = { .x_all = 0b00000110000 },
        .line2 = { .x_all = 0b00000100000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = T_S },
    { .block = Z, .piece = { .bits = {
        .line0 = { .x_all = 0b00001100000 },
        .line1 = { .x_all = 0b00011000000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = Z_EW },
    { .block = Z, .piece = { .bits = {
        .line0 = { .x_all = 0b00010000000 },
        .line1 = { .x_all = 0b00011000000 },
        .line2 = { .x_all = 0b00001000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = Z_NS },
    { .block = Z, .piece = { .bits = {
        .line0 = { .x_all = 0b00001100000 },
        .line1 = { .x_all = 0b00011000000 },
        .line2 = { .x_all = 0b00000000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = Z_EW },
    { .block = Z, .piece = { .bits = {
        .line0 = { .x_all = 0b00010000000 },
        .line1 = { .x_all = 0b00011000000 },
        .line2 = { .x_all = 0b00001000000 },
        .line3 = { .x_all = 0b00000000000 }
    } }, .next = Z_NS },
};

#endif /* LIBTETRO_H */
