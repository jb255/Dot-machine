#include "libtest.h"
#include "libmino.h"

// The function `main` contents the detail of unit testing.
int main(void) {
    projection.cursor.bits.y = 0;
    projection.tetro = tetromino[I_NS];
  
    Piece before = tetromino[I_NS].piece;
    Piece after = tetromino[I_EW].piece;

    write_mino(before, before);
    
    assert_eq(buffer_dot.lenght, 0);

    write_mino(after, after);
    
    assert_eq(buffer_dot.lenght, 0);

    write_mino(before, after);
  
    assert_eq(buffer_dot.lenght, 6);

    assert_eq(buffer_dot.content[0].bits.color, 0);
    assert_eq(buffer_dot.content[0].bits.x, 6);
    assert_eq(buffer_dot.content[0].bits.y, 0);

    assert_eq(buffer_dot.content[1].bits.color, 0);
    assert_eq(buffer_dot.content[1].bits.x, 6);
    assert_eq(buffer_dot.content[1].bits.y, 2);

    assert_eq(buffer_dot.content[2].bits.color, 0);
    assert_eq(buffer_dot.content[2].bits.x, 6);
    assert_eq(buffer_dot.content[2].bits.y, 3);

    assert_eq(buffer_dot.content[3].bits.color, 1);
    assert_eq(buffer_dot.content[3].bits.x, 4);
    assert_eq(buffer_dot.content[3].bits.y, 1);

    assert_eq(buffer_dot.content[4].bits.color, 1);
    assert_eq(buffer_dot.content[4].bits.x, 5);
    assert_eq(buffer_dot.content[4].bits.y, 1);

    assert_eq(buffer_dot.content[5].bits.color, 1);
    assert_eq(buffer_dot.content[5].bits.x, 7);
    assert_eq(buffer_dot.content[5].bits.y, 1);
    return 0;
}
