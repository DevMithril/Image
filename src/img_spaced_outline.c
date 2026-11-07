#include "types.h"

SDL_Surface *img_full_outline(SDL_Surface *src, SDL_Color color, u32 width);
bool img_mask(SDL_Surface *surface, SDL_Color keep, SDL_Color new);
bool img_replace(SDL_Surface *surface, SDL_Color base, SDL_Color new,
                    SDL_Rect *clip);

SDL_Surface *img_spaced_outline(SDL_Surface *src, SDL_Color color,
                                u32 start, u32 width) {
    SDL_Surface *mask = NULL;
    SDL_Rect dst = {start + width, start + width, src->w, src->h};
    SDL_Color random_color = color;
    random_color.r = (random_color.r + 1) % 256;

    mask = SDL_DuplicateSurface(src);
    if (!mask) {
        SDL_Log("SDL_DuplicateSurface() : %s\n", SDL_GetError());
        SDL_DestroySurface(src);
        return NULL;
    }

    mask = img_full_outline(mask, random_color, start);
    if (!mask) {
        SDL_DestroySurface(src);
        return NULL;
    }
    mask = img_full_outline(mask, color, width);
    if (!mask) {
        SDL_DestroySurface(src);
        return NULL;
    }
    if (!img_mask(mask, color, (SDL_Color){0, 0, 0, 0})) {
        SDL_DestroySurface(mask);
        SDL_DestroySurface(src);
        return NULL;
    }

    SDL_BlitSurface(src, NULL, mask, &dst);
    SDL_DestroySurface(src);

    return mask;
}
