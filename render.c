#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>  // Used for thickLineRGBA(...).
#include <math.h>

#include "font.h"
#include "game.h"
#include "render.h"

/// Rendering the game via procedures.

// Procedures: how to render grid and render board.
// We don't think in states here.

#define COLOR_ALPHA       255  // Magic constant used in `SDL_SetRenderDrawColor`.
#define XO_LINE_THICKNESS 10  // Line thickness of crosses and zeroes.

const SDL_Color GRID_COLOR     = {.r = 255, .g = 255, .b = 255};  // White.
const SDL_Color PLAYER_X_COLOR = {.r = 255, .g = 50, .b = 50};    // Red.
const SDL_Color PLAYER_O_COLOR = {.r = 50, .g = 100, .b = 255};   // Blue.
const SDL_Color TIE_COLOR      = {.r = 100, .g = 100, .b = 100};  // Gray.
const SDL_Color BG_COLOR       = {.r = 0, .g = 0, .b = 0};        // Black.
const SDL_Color WIN_COLOR      = {.r = 255, .g = 215, .b = 0};    // status.

static void render_grid(SDL_Renderer *renderer, const SDL_Color *color) {
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, COLOR_ALPHA);

    for (size_t i = 1; i < N_GRID; ++i) {
        SDL_RenderDrawLine(renderer, (i * CELL_WIDTH), 0, (i * CELL_WIDTH),
                           SCREEN_HEIGHT);  // Vertical lines.
        SDL_RenderDrawLine(renderer, 0, (i * CELL_HEIGHT), SCREEN_WIDTH,
                           (i * CELL_HEIGHT));  // Horizontal lines.
    }
}

static void render_x_cell(SDL_Renderer *renderer, size_t row, size_t col,
                          const SDL_Color *color) {
    const float half_block_side = (fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25);
    const float center_x        = (CELL_WIDTH * 0.5) + (col * CELL_WIDTH);
    const float center_y        = (CELL_HEIGHT * 0.5) + (row * CELL_HEIGHT);

    thickLineRGBA(renderer, center_x - half_block_side,
                  center_y - half_block_side, center_x + half_block_side,
                  center_y + half_block_side, XO_LINE_THICKNESS, color->r,
                  color->g, color->b, COLOR_ALPHA);  // Draw `\`.
    thickLineRGBA(renderer, center_x + half_block_side,
                  center_y - half_block_side, center_x - half_block_side,
                  center_y + half_block_side, XO_LINE_THICKNESS, color->r,
                  color->g, color->b, COLOR_ALPHA);  // Draw `/`.
}

static void render_o_cell(SDL_Renderer *renderer, size_t row, size_t col,
                          const SDL_Color *color) {
    const float half_block_side = (fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25);
    const float center_x        = (CELL_WIDTH * 0.5) + (col * CELL_WIDTH);
    const float center_y        = (CELL_HEIGHT * 0.5) + (row * CELL_HEIGHT);

    filledCircleRGBA(renderer, center_x, center_y, half_block_side, color->r,
                     color->g, color->b, COLOR_ALPHA);  // Draw solid O.
    filledCircleRGBA(renderer, center_x, center_y,
                     (half_block_side - XO_LINE_THICKNESS), BG_COLOR.r,
                     BG_COLOR.g, BG_COLOR.b, COLOR_ALPHA);  // Draw mask o.
}

static void render_board(SDL_Renderer *renderer, const int *board,
                         const SDL_Color *player_x_color,
                         const SDL_Color *player_o_color) {
    for (size_t i = 0; i < N_GRID; ++i) {
        for (size_t j = 0; j < N_GRID; ++j) {
            switch (board[i * N_GRID + j]) {
            case CELL_PLAYER_X:  // 1.
                render_x_cell(renderer, i, j, player_x_color);
                break;
            case CELL_PLAYER_O:  // 2.
                render_o_cell(renderer, i, j, player_o_color);
                break;
            default: {
            }
            }
        }
    }
}

static void render_game_over_state(SDL_Renderer      *renderer,
                                   const struct Game *game,
                                   const SDL_Color   *color) {
    render_grid(renderer, color);
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

// Render status bar below board; where extra space is reserved in game window.
void render_status_bar(SDL_Renderer *renderer, size_t height,
                       const struct Game *game, TTF_Font *font) {
    SDL_Rect status_bar_rect = {0, SCREEN_HEIGHT, SCREEN_WIDTH, height};
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderFillRect(renderer, &status_bar_rect);

    SDL_Color fg;
    char     *indicator;

    indicator = game->player == CELL_PLAYER_X ? "X" : "O";

    switch (game->state) {
    case GAME_STATE_RUNNING:
        fg = game->player == CELL_PLAYER_X ? PLAYER_X_COLOR : PLAYER_O_COLOR;
        break;
    case GAME_STATE_PLAYER_X_WON:
        indicator = "X";
        fg        = WIN_COLOR;
        break;
    case GAME_STATE_PLAYER_O_WON:
        indicator = "O";
        fg        = WIN_COLOR;
        break;
    case GAME_STATE_TIE:
        fg        = TIE_COLOR;
        indicator = "-";
        break;
    case GAME_STATE_QUIT:
        indicator = " ";
        fg        = BG_COLOR;
        break;
    default: {
    }
    }

    display_text(renderer, indicator, font, fg, (8), (SCREEN_HEIGHT));
}
