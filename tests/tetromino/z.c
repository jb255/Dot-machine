#include "libmino.h"
#include "libtest.h"

// The function `main` contents the detail of unit testing.
int main(void) {
    g_piece.tetromino.type = Z_Block;
    assert_eq(g_piece.tetromino.type, 'Z');

    g_piece.tetromino.dot.bits.x = 3;
    g_piece.tetromino.dot.bits.y = 3;
    board.y_bits.line3.x_bits.col2 = 0b1;
    board.y_bits.line3.x_bits.col5 = 0b1;
    // line3 _ _ X P P X ...
    // line4 _ _ _ _ P P ...
    assert_eq(tetromino(g_piece), 0b0);

    g_piece.tetromino.dot.bits.x = 2;
    // line3 _ _ E P _ X ...
    // line4 _ _ _ P P _ ...
    assert_eq(tetromino(g_piece), 0b1);

    g_piece.tetromino.direction = East;
    // line3 _ _ X P _ X ...
    // line4 _ _ P P _ _ ...
    // line5 _ _ P _ _ _ ...
    assert_eq(tetromino(g_piece), 0b0);
    return 0;
}
