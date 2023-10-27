#include <SDL2/SDL.h>
#include <assert.h>
#include <stddef.h>

#include "game.h"
#include "render.h"

/// Rendering the game via procedures.

// Procedures: how to render grid and render board.
// We don't think in states here.

#define COLOR_ALPHA 255  // Magic constant used in `SDL_SetRenderDrawColor`.

const SDL_Color GRID_COLOR     = {.r = 255, .g = 255, .b = 255};  // White.
const SDL_Color PLAYER_X_COLOR = {.r = 255, .g = 50, .b = 50};    // Red.
const SDL_Color PLAYER_O_COLOR = {.r = 50, .g = 100, .b = 255};   // Blue.
const SDL_Color TIE_COLOR      = {.r = 100, .g = 100, .b = 100};  // Gray.

static void render_grid(SDL_Renderer *renderer, const SDL_Color *color) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, COLOR_ALPHA);

    for (size_t i = 1; i < N_GRID; ++i) {
        SDL_RenderDrawLine(renderer, (i * CELL_WIDTH), 0, (i * CELL_WIDTH),
                           SCREEN_HEIGHT);  // Vertical lines.
        SDL_RenderDrawLine(renderer, 0, (i * CELL_HEIGHT), SCREEN_WIDTH,
                           (i * CELL_HEIGHT));  // Horizontal lines.
    }
}

// static void render_x_cell() {}
// static void render_o_cell() {}

static void render_board(SDL_Renderer *renderer, const int *board,
                         const SDL_Color *player_x_color,
                         const SDL_Color *player_y_color) {}

static void render_game_over_state(SDL_Renderer      *renderer,
                                   const struct Game *game,
                                   const SDL_Color   *color) {
    render_grid(renderer, &GRID_COLOR);
    render_board(renderer, game->board, color, color);
}

static void render_running_state(SDL_Renderer      *renderer,
                                 const struct Game *game) {
    render_grid(renderer, &GRID_COLOR);
    render_board(renderer, game->board, &PLAYER_X_COLOR, &PLAYER_O_COLOR);
}

// Draw the game without mutating game state.
void render_game(SDL_Renderer *renderer, const struct Game *game) {  //

    switch (game->state) {
    case GAME_STATE_RUNNING: render_running_state(renderer, game); break;
    case GAME_STATE_PLAYER_X_WON:  // Color game in X color.
        render_game_over_state(renderer, game, &PLAYER_X_COLOR);
        break;
    case GAME_STATE_PLAYER_O_WON:  // Color game in O color.
        render_game_over_state(renderer, game, &PLAYER_O_COLOR);
        break;
    case GAME_STATE_TIE:  // Color game in gray tie state color.
        render_game_over_state(renderer, game, &TIE_COLOR);
        break;
    default: {
    }
    }
}
