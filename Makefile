FLAG := -Wall -Wextra -Werror -O2

default: all

all:
	$(CC) $(FLAG) -Isrc -Isrc/tetromino -Itests -o main src/main.c

sdl:
	$(CC) $(FLAG) -D __SDL__ $(shell sdl2-config --cflags --libs) -Isrc -Isrc/tetromino -Itests -o main src/main.c

doc:
	doxygen # && make -C doc/latex

asmjs:
	emcc $(FLAG) -D __SDL__ -Isrc -Isrc/tetromino -Itests src/main.c -s USE_SDL=2 -o main.html
wasm:
	emcc $(FLAG) -D __SDL__ -Isrc -Isrc/tetromino -Itests src/main.c -s WASM=1 -s USE_SDL=2 -o main.html

test:
	gcc $(FLAG) -Isrc -Itests -o test_piece tests/piece.c && ./test_piece
	gcc $(FLAG) -Isrc -Itests -o test_buffer tests/buffer.c && ./test_buffer
	gcc $(FLAG) -Isrc -Itests -o test_move tests/move.c && ./test_move
#	gcc $(FLAG) -Isrc -Itests -o test_mino tests/mino.c && ./test_mino
#	gcc $(FLAG) -Isrc -Itests -o test_reset_lign tests/reset_lign.c && ./test_reset_lign

format:
	clang-format -i -style=file src/*.h src/*.c

.PHONY: all doc test
