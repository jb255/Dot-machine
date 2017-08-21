#include "libmino.h"
#include "libtest.h"

/*
 * test if one can go down, (extra second before to stop)
 *	if the piece can t go down any longer
 *  check every ligns the piece is on
 *	 if the are full
 *	suppress every ligns that are full
 *	bring down each lign from the one not moving
 *  do it lign after lign
 *
 */


int main(void) {
	board.y_bits.line24.x_all = 0b11011111111;
	board.y_bits.line25.x_all = 0b11110111111;
	board.y_bits.line26.x_all = 0b11010111011;
	board.y_bits.line27.x_all = 0b11111111111;

	assert_eq(board.y_bits.line27.x_all, 0b0);
//	check_lign_mino(&board.y_bits.line24);
	//printboard();
	return 0;
}
