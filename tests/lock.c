#include "libtest.h"
#include "libmino.h"

// The function `main` contents the detail of unit testing.
int main(void) {
    projection.tetro.piece = tetromino[I_EW];
    lock_tetro();

    assert_eq(board.y_bits.line0.x_all, 0b00000000000);
    assert_eq(board.y_bits.line1.x_all, 0b00011110000);
    assert_eq(board.y_bits.line2.x_all, 0b00000000000);
    assert_eq(board.y_bits.line3.x_all, 0b00000000000);

    projection.tetro.piece = tetromino[I_NS];
    lock_tetro();

    assert_eq(board.y_bits.line0.x_all, 0b00001000000);
    assert_eq(board.y_bits.line1.x_all, 0b00011110000);
    assert_eq(board.y_bits.line2.x_all, 0b00001000000);
    assert_eq(board.y_bits.line3.x_all, 0b00001000000);
    return 0;
}
