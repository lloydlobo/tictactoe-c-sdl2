#include <SDL2/SDL.h>

#include "game.h"
#include "render.h"

/// Rendering the game.

const SDL_Color GRID_COLOR     = {.r = 255, .g = 255, .b = 255};
const SDL_Color PLAYER_X_COLOR = {.r = 255, .g = 50, .b = 50};
const SDL_Color PLAYER_O_COLOR = {.r = 50, .g = 100, .b = 255};
const SDL_Color TIE_COLOR      = {.r = 100, .g = 100, .b = 100};

void render_game_over_state(SDL_Renderer *renderer, const struct Game *game,
                            const SDL_Color *color) {
    // ...
}

void render_running_state(SDL_Renderer *renderer, const struct Game *game) {
    // ...
}

// Draw the game without mutating game state.
void render_game(SDL_Renderer *renderer, const struct Game *game) {  //

    switch (game->state) {
    case GAME_STATE_RUNNING: render_running_state(renderer, game); break;
    case GAME_STATE_PLAYER_X_WON:
        render_game_over_state(renderer, game, &PLAYER_X_COLOR);
        break;
    case GAME_STATE_PLAYER_O_WON:
        render_game_over_state(renderer, game, &PLAYER_O_COLOR);
        break;
    case GAME_STATE_TIE:
        render_game_over_state(renderer, game, &TIE_COLOR);
        break;
    default: {
    }
    }
}
