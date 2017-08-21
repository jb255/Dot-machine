#ifndef __XC32
#include "libtest.h"
#endif
#include "libmino.h"

#ifdef __XC32
#   include <xc.h>
#else
#   include <time.h>
#   ifdef __SDL__
#      define SIZE 15
#      define SIZE_ONE_TENTH SIZE/3
#      define SIZE_TWO_TENTH SIZE_ONE_TENTH+SIZE_ONE_TENTH
#      define WIDTH SIZE*X_MAX
#      define HEIGHT SIZE*Y_MAX
#      ifdef __EMSCRIPTEN__
#         include <emscripten.h>
#         include <emscripten/emscripten.h>
#         include <SDL.h>
#      else
#         ifdef linux
#             include <SDL2/SDL.h>
#         endif /*! LINUX */
#         ifdef __APPLE__
#             include <SDL.h>
#         endif /*! APPLE */
#      endif /*! EMSCRIPTEN */
#   else
#       include <unistd.h>
#       include <stdio.h>
#       include <termios.h>
#       include <sys/ioctl.h>
#   endif
#endif

#ifdef __XC32
/*! The start function `main` is the XC32 implementation of Dot machine. */
int main(void) {
    // Sample Example:
    // http://www.johnloomis.org/microchip/docs/PIC32_FRM.pdf#G9.876363
    INTCONbits.MVEC = 0b1; // Interrupt Controller configured for multi vectored
    // mode; Register
    // Table:
    // http://ww1.microchip.com/downloads/en/DeviceDoc/60001108H.pdf#G1.1000176
    __builtin_enable_interrupts(); // XC32 macro to enable all interrupts:
    // http://ww1.microchip.com/downloads/en/DeviceDoc/50002509A.pdf#G1.791014

    init_mino();
    init_pps();
    init_port();
    // Sample Example:
    // http://ww1.microchip.com/downloads/en/DeviceDoc/60001114G.pdf#G1.874207
    // Register Table:
    // http://ww1.microchip.com/downloads/en/DeviceDoc/60001114G.pdf#G1.879241
    WDTCONbits.ON = 0b1; // Enables the Watchdog Timer if it is not enabled by the
                         // device configuration.
    while (!0) {
        WDTCONbits.WDTCLR = 0b1; // Writing a ‘1’ will clear the WDT
    }
    return EXIT_SUCCESS;
}
#else
#ifdef __SDL__

unsigned int lastTime = 0, currentTime;

u32 callback_down(u32 interval, void *param) {
    Pad pad;
    
    pad.all = Down;
    move_mino(pad);
    while (flush_board()) {
    }
    (void)param;
    return interval;
}

typedef struct Context {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_bool done;
} Context;

void init(Context *context) {
    assert_eq(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER), 0);
	
    context->window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    assert_ne(context->window, NULL);

    context->renderer = SDL_CreateRenderer(context->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    assert_ne(context->renderer, NULL);
		
    SDL_SetWindowTitle(context->window, "Tetris\0");
    
    context->done = SDL_FALSE;
}

void destroy(Context *context) {
    if (context) {
        if (context->renderer) {
            SDL_DestroyRenderer(context->renderer);
        }
        if (context->window) {
            SDL_DestroyWindow(context->window);
        }
    }
}

void loop(void *argument) {
    Context *context = (Context *)argument;

    SDL_SetRenderDrawColor(context->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(context->renderer);
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
	    context->done = SDL_TRUE;
	} else if (event.type == SDL_KEYDOWN) {
            Pad pad;

            pad.all = event.key.keysym.sym;
            if (pad.key == Esc) {
                context->done = SDL_TRUE;
            } else {
                move_mino(pad);
                while (flush_board()) {
                }
            }
        }
    }
    SDL_Rect border;
    border.w = SIZE;
    border.h = SIZE;
    for (u8 y = 0; y < Y_MAX; y += 1) {
        Line line = *(board.y_all + y);
        for (u8 x = 0; x < X_MAX; x += 1) {
            border.x = x*SIZE;
            border.y = y*SIZE;
            if (line.x_all & 0b1) {
	        SDL_SetRenderDrawColor(context->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(context->renderer, &border);
            } else {
	        SDL_SetRenderDrawColor(context->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawRect(context->renderer, &border);

                SDL_Point point[9];
		point[0].x = border.x + SIZE_ONE_TENTH;
		point[0].y = border.y;
		point[1].x = point[0].x + SIZE_ONE_TENTH;
		point[1].y = point[0].y;
		point[2].x = point[1].x + SIZE_ONE_TENTH;
		point[2].y = point[0].y + SIZE_ONE_TENTH;
		point[3].x = point[2].x;
		point[3].y = point[0].y + SIZE_TWO_TENTH;
		point[4].x = point[1].x;
		point[4].y = point[0].y + SIZE;
		point[5].x = point[0].x;
		point[5].y = point[4].y;
		point[6].x = x*SIZE;
		point[6].y = point[3].y;
		point[7].x = point[6].x;
		point[7].y = point[2].y;
		point[8].x = point[0].x;
		point[8].y = point[0].y;
	        SDL_RenderDrawLines(context->renderer, point, 9);
            }
            line.x_all >>= 1;
        }
    }
    Piece piece = projection.tetro.piece;
    for (u8 y = projection.cursor.bits.y; y < projection.cursor.bits.y+TETRO_LINE_MAX; y += 1) {
        for (u8 x = 0; x < X_MAX; x += 1) {
            if (piece.oob & 1) {
                border.x = x*SIZE;
                border.y = y*SIZE;
	        SDL_SetRenderDrawColor(context->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(context->renderer, &border);
            }
            piece.oob >>= 1;
        }
        piece.oob >>= 5;
    }
    SDL_RenderPresent(context->renderer);

    // Print a report once per second
    currentTime = SDL_GetTicks();
    if (currentTime > lastTime + 150) {
	callback_down(0, NULL);
        lastTime = currentTime;
    }

}

int main(void) {
    srand(time(NULL)); // randomize.

    restart_mino();
    while (flush_board()) {
    }

    Context context;

    init(&context);
#   ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(loop, &context, -1, 1);
#   else
    while (!context.done) {
        loop(&context);
    }
#   endif
    destroy(&context);
    return EXIT_SUCCESS;
}
#else
#ifdef __APPLE__
#define TCGETS TIOCGETA
#define TCSETS TIOCSETA
#endif
/*! The start function `main` is the Linux implementation of Dot machine. */
int main(void) {
    srand(time(NULL)); // randomize.
    struct termios raw;
    struct termios normal;

    assert_ne(ioctl(STDIN_FILENO, TCGETS, &raw), -1);
    assert_ne(ioctl(STDIN_FILENO, TCGETS, &normal), -1);
    raw.c_lflag ^= (ECHO | ICANON | ISIG);
    raw.c_iflag ^= BRKINT;
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    assert_ne(ioctl(STDIN_FILENO, TCSETS, &raw), -1);
    restart_mino();
    while (flush_board()) {
    }
    while (!0) {
        Pad pad;
        int ret;

        pad.all = 0;
        ret = read(STDIN_FILENO, pad.buf, 3);
        if (ret <= 0 || pad.key == Esc) {
            break;
        } else {
            move_mino(pad);
            while (flush_board()) {
            }
        }
    }
    assert_ne(ioctl(STDIN_FILENO, TCSETS, &normal), -1);
    return EXIT_SUCCESS;
}
#endif
#endif
