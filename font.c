#include "font.h"

/// Display text with SDL_ttf.

// Borrowed from:
// [mcksp/sdl-game](https://github.com/mcksp/sdl-game/blob/master/font.c)

//  Renders and displays text on an SDL renderer using a TrueType font.
void display_text(SDL_Renderer *renderer, char *text, TTF_Font *font,
                  SDL_Color fg_color, int x, int y) {
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect     pos;

    // Render Latin1 text at fast quality to a new 8-bit surface.
    // Render the text onto an SDL surface with a solid (opaque) color.
    surface = TTF_RenderText_Solid(font, text, fg_color);

    // Create a texture from an existing surface.
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Define the position and dimensions of the rendered text.
    pos.w = surface->w;  // Width of the rendered text.
    pos.h = surface->h;  // Height of the rendered text.
    pos.x = x;           // X-coordinate where the text will be placed.
    pos.y = y;           // Y-coordinate where the text will be placed.

    // Free/Clean up an RGB temporary surface.
    SDL_FreeSurface(surface);

    // Copy a portion of the texture to the current rendering target(position).
    SDL_RenderCopy(renderer, texture, NULL, &pos);  // (_,_,srcrect, destrect).
}
