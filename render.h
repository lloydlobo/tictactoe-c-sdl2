#ifndef RENDER_H_
#define RENDER_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void render_game(SDL_Renderer *renderer, const struct Game *game);
void render_status_bar(SDL_Renderer *renderer, size_t height,
                       const struct Game *game, TTF_Font *font);

#endif  // RENDER_H_
