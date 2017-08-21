#include "libtest.h"
#include "libmino.h"

// The function `main` contents the detail of unit testing.
int main(void) {
    board.y_bits.line0.x_all = 0b11111111111;
    board.y_bits.line1.x_all = 0b00000000000;
    board.y_bits.line2.x_all = 0b11111111111;
    board.y_bits.line3.x_all = 0b00000000000;
    projection.cursor.bits.y = 0;
    Piece (*lines0)[1] = (Piece (*)[1])(board.y_all + projection.cursor.bits.y);

    assert_eq((**lines0).oob, 0b0000000000000000000001111111111100000000000000000000011111111111);

    board.y_bits.line4.x_all = 0b00000000000;
    board.y_bits.line5.x_all = 0b11111111111;
    board.y_bits.line6.x_all = 0b00000000000;
    board.y_bits.line7.x_all = 0b11111111111;
    projection.cursor.bits.y = 4;
    Piece (*lines4)[1] = (Piece (*)[1])(board.y_all + projection.cursor.bits.y);
    
    assert_eq((**lines4).oob, 0b0000011111111111000000000000000000000111111111110000000000000000);

    board.y_bits.line3.x_all = 0b11111111111;
    board.y_bits.line4.x_all = 0b11111111111;
    projection.cursor.bits.y = 2;
    Piece (*lines6)[1] = (Piece (*)[1])(board.y_all + projection.cursor.bits.y);

    assert_eq((**lines6).oob, 0b0000011111111111000001111111111100000111111111110000011111111111);
    return 0;
}
