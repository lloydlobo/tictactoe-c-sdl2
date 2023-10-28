#include <SDL2/SDL_ttf.h>
#include <stdarg.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "font.h"
#include "game.h"
#include "logic.h"
#include "render.h"

/// Main entrypoint of the game.

#define FMT_BOLD  "\033[1m"
#define FMT_RESET "\033[0m"

/**
 * Print a formatted error message to stderr with "error:" in bold.
 *
 * \param format A format string for the error message.
 * \param ... Variable arguments matching the format string.
 * \returns The number of characters written (non-negative) or a negative value
 * to indicate an error.
 *
 * e.g: report_error("Could not load file: %s\n", filename);
 */
int report_error(const char *format, ...) {
    int     result;
    va_list args;

    result = 0;
    va_start(args, format);
    result += fprintf(stderr, FMT_BOLD "error: " FMT_RESET);
    result += vfprintf(stderr, format, args);
    va_end(args);

    return result;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        report_error("could not initialize SDL2: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() != 0) {
        report_error("could not initialize SDL2_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window   *window;
    SDL_Renderer *renderer;
    size_t        status_bar_height;  // 16pt.
    TTF_Font     *font;               // 16pt.

    status_bar_height = 16;

    font = TTF_OpenFont("resources/fonts/m5x7.ttf", 16);
    if (font == NULL) {  // FIXME: initialize library.
        report_error("could not load font: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    window = SDL_CreateWindow(
        "tictactoe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, (SCREEN_HEIGHT + status_bar_height), SDL_WINDOW_SHOWN);
    if (window == NULL) {
        report_error("could not create window: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    renderer = SDL_CreateRenderer(
        window, (-1), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        report_error("could not create renderer: %s\n", SDL_GetError());
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    struct Game game = {
        .board  =  // clang-format off
            { CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,
              CELL_EMPTY, CELL_EMPTY, CELL_EMPTY,
              CELL_EMPTY, CELL_EMPTY, CELL_EMPTY, },  // clang-format on
        .player = CELL_PLAYER_X,
        .state  = GAME_STATE_RUNNING,
    };

    SDL_Event event;
    while (game.state != GAME_STATE_QUIT) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT: game.state = GAME_STATE_QUIT; break;
            case SDL_MOUSEBUTTONDOWN: {
                int row = event.button.y / CELL_HEIGHT,
                    col = event.button.x / CELL_WIDTH;
                click_on_cell(&game, row, col);
                break;
            }
            default: {
            }
            }  // _end:switch
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Set to black.
        SDL_RenderClear(renderer);  // Clears the entire rendering target.

        render_game(renderer, &game);
        render_status_bar(renderer, status_bar_height, &game, font);

        SDL_RenderPresent(renderer);  // Update the screen with any rendering
                                      // performed since the previous call.
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_CloseFont(font);
    TTF_Quit();  // should call TTF_CloseFont() on any open fonts before calling
                 // this function!
    SDL_Quit();

    return 0;
}
