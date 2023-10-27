#ifndef RENDER_H_
#define RENDER_H_

#include <SDL2/SDL.h>

// Draw the game without mutating game state.
void render_game(SDL_Renderer *renderer, const struct Game *game);

#endif  // RENDER_H_
