#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include "game.h"
#include "logic.h"
#include "render.h"

/// Main entrypoint of the game.

#define FMT_BOLD  "\033[1m"
#define FMT_RESET "\033[0m"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "could not initialize SDL2: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("tictactoe", 100, 100, SCREEN_WIDTH,
                                          SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, FMT_BOLD "SDL_CreateWindow error: " FMT_RESET "%s\n",
                SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, (-1), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, FMT_BOLD "SDL_CreateRenderer error: " FMT_RESET "%s\n",
                SDL_GetError());
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

    SDL_Event e;
    // int       quit = 0;
    // while (!quit) {
    while (game.state != GAME_STATE_QUIT) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            // case SDL_QUIT: quit = 1; break;
            case SDL_QUIT: game.state = GAME_STATE_QUIT; break;
            case SDL_MOUSEBUTTONDOWN: {
                int row = e.button.y / CELL_HEIGHT,
                    col = e.button.x / CELL_WIDTH;
                click_on_cell(&game, row, col);
                break;
            }
            default: {
            }
            }  // switch
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Set to black.
        SDL_RenderClear(renderer);  // Clears the entire rendering target.
        render_game(renderer, &game);
        SDL_RenderPresent(renderer);  // Update the screen with any rendering
                                      // performed since the previous call.
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
