#include "types.h"

SDL_Surface *create_text(const char text[], TTF_Font *font, SDL_Color color) {
    SDL_Surface *surface = NULL, *tmp = NULL;

    tmp = TTF_RenderText_Solid(font, text, 0, color);
    if (!tmp) {
        SDL_Log("TTF_RenderText_Solid() : %s", SDL_GetError());
        return NULL;
    }

    surface = SDL_ConvertSurface(tmp, SDL_PIXELFORMAT_RGBA32);
    SDL_DestroySurface(tmp);
    if (!surface) {
        SDL_Log("SDL_ConvertSurface() : %s", SDL_GetError());
        return NULL;
    }

    return surface;
}
