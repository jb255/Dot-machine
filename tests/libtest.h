#ifndef LIBTEST_H
#define LIBTEST_H

#include <stdio.h>
#include <unistd.h>

// The macro `assert_eq` exits the program with a panic if the comparison is false.
#define assert_eq(left, right) if (left != right) { _exit(-1); }

// The macro `assert_ne` exits the program with a panic if the comparison is true.
#define assert_ne(left, right) if (left == right) { _exit(-1); }

// The macro `printb2` printf the argument with a 2 first binary format.
#define printb2(c) { printf("0b%d%d\n", (c >> 0) & 1, (c >> 1) & 1); }

// The macro `printb8` printf the argument with a 8 first binary format.
#define printb8(c) { printf("0b%d%d%d%d_%d%d%d%d\n", (c >> 0) & 1, (c >> 1) & 1, (c >> 2) & 1, (c >> 3) & 1, (c >> 4) & 1, (c >> 5) & 1, (c >> 6) & 1, (c >> 7) & 1); }

// The macro `printb11` printf the argument with a 11 first binary format.
#define printb11(c) { printf("0b%d%d%d%d%d_%d%d%d%d%d_%d\n", (c >> 0) & 1, (c >> 1) & 1, (c >> 2) & 1, (c >> 3) & 1, (c >> 4) & 1, (c >> 5) & 1, (c >> 6) & 1, (c >> 7) & 1, (c >> 8) & 1, (c >> 9) & 1, (c >> 10) & 1); }

#define printb16(c) { printf("0b%d%d%d%d%d_%d%d%d%d%d_%d%d%d_%d%d%d\n", (c >> 0) & 1, (c >> 1) & 1, (c >> 2) & 1, (c >> 3) & 1, (c >> 4) & 1, (c >> 5) & 1, (c >> 6) & 1, (c >> 7) & 1, (c >> 8) & 1, (c >> 9) & 1, (c >> 10) & 1, (c >> 11) & 1, (c >> 12) & 1, (c >> 13) & 1, (c >> 14) & 1, (c >> 15) & 1); }

// The macro `printb32` printf the argument with a 11 first binary format.
#define printb32(c) { printf("0b%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d\n", (c >> 0) & 1, (c >> 1) & 1, (c >> 2) & 1, (c >> 3) & 1, (c >> 4) & 1, (c >> 5) & 1, (c >> 6) & 1, (c >> 7) & 1, (c >> 8) & 1, (c >> 9) & 1, (c >> 10) & 1, (c >> 11) & 1, (c >> 12) & 1, (c >> 13) & 1, (c >> 14) & 1, (c >> 15) & 1, (c >> 16) & 1, (c >> 17) & 1, (c >> 18) & 1, (c >> 19) & 1, (c >> 20) & 1, (c >> 21) & 1, (c >> 22) & 1, (c >> 23) & 1, (c >> 24) & 1, (c >> 25) & 1, (c >> 26) & 1, (c >> 27) & 1, (c >> 28) & 1, (c >> 29) & 1, (c >> 30) & 1, (c >> 31) & 1); }

// The macro `printb64` printf the argument with a 64 first binary format.
#define printb64(c) { printf("0b%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu_%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu_%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu_%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu%llu\n", (c >> 0) & 1, (c >> 1) & 1, (c >> 2) & 1, (c >> 3) & 1, (c >> 4) & 1, (c >> 5) & 1, (c >> 6) & 1, (c >> 7) & 1, (c >> 8) & 1, (c >> 9) & 1, (c >> 10) & 1, (c >> 11) & 1, (c >> 12) & 1, (c >> 13) & 1, (c >> 14) & 1, (c >> 15) & 1, (c >> 16) & 1, (c >> 17) & 1, (c >> 18) & 1, (c >> 19) & 1, (c >> 20) & 1, (c >> 21) & 1, (c >> 22) & 1, (c >> 23) & 1, (c >> 24) & 1, (c >> 25) & 1, (c >> 26) & 1, (c >> 27) & 1, (c >> 28) & 1, (c >> 29) & 1, (c >> 30) & 1, (c >> 31) & 1, (c >> 32) & 1, (c >> 33) & 1, (c >> 34) & 1, (c >> 35) & 1, (c >> 36) & 1, (c >> 37) & 1, (c >> 38) & 1, (c >> 39) & 1, (c >> 40) & 1, (c >> 41) & 1, (c >> 42) & 1, (c >> 43) & 1, (c >> 44) & 1, (c >> 45) & 1, (c >> 46) & 1, (c >> 47) & 1, (c >> 48) & 1, (c >> 49) & 1, (c >> 50) & 1, (c >> 51) & 1, (c >> 52) & 1, (c >> 53) & 1, (c >> 54) & 1, (c >> 55) & 1, (c >> 56) & 1, (c >> 57) & 1, (c >> 58) & 1, (c >> 59) & 1, (c >> 60) & 1, (c >> 61) & 1, (c >> 62) & 1, (c >> 63) & 1); }

#define printboard() \
    printb11(board.y_bits.line0.x_all); \
    printb11(board.y_bits.line1.x_all); \
    printb11(board.y_bits.line2.x_all); \
    printb11(board.y_bits.line3.x_all); \
    printb11(board.y_bits.line4.x_all); \
    printb11(board.y_bits.line5.x_all); \
    printb11(board.y_bits.line6.x_all); \
    printb11(board.y_bits.line7.x_all); \
    printb11(board.y_bits.line8.x_all); \
    printb11(board.y_bits.line9.x_all); \
    printb11(board.y_bits.line10.x_all); \
    printb11(board.y_bits.line11.x_all); \
    printb11(board.y_bits.line12.x_all); \
    printb11(board.y_bits.line13.x_all); \
    printb11(board.y_bits.line14.x_all); \
    printb11(board.y_bits.line15.x_all); \
    printb11(board.y_bits.line16.x_all); \
    printb11(board.y_bits.line17.x_all); \
    printb11(board.y_bits.line18.x_all); \
    printb11(board.y_bits.line19.x_all); \
    printb11(board.y_bits.line20.x_all); \
    printb11(board.y_bits.line21.x_all); \
    printb11(board.y_bits.line22.x_all); \
    printb11(board.y_bits.line23.x_all); \
    printb11(board.y_bits.line24.x_all); \
    printb11(board.y_bits.line25.x_all); \
    printb11(board.y_bits.line26.x_all); \
    printb11(board.y_bits.line27.x_all); \

#define printboard_info() \
    printf("[x; y]: [%d; %d]\n", projection.tetro.cursor.bits.x, projection.tetro.cursor.bits.y); \
    printboard(); \

#endif
