#ifndef FONT_H_
#define FONT_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void display_text(SDL_Renderer *renderer, char *text, TTF_Font *font,
                  SDL_Color fg_color, int x, int y);

#endif  // FONT_H_
