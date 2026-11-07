#include "types.h"

bool img_borders(SDL_Surface *surface, SDL_Color color, u32 depth);
bool img_mask(SDL_Surface *surface, SDL_Color keep, SDL_Color new);
bool img_replace(SDL_Surface *surface, SDL_Color base, SDL_Color new,
                    SDL_Rect *clip);

bool img_margin_borders(SDL_Surface *surface, SDL_Color color,
                        u32 depth, u32 width) {
    SDL_Surface *mask = NULL;
    SDL_Color mask_color = color;
    mask_color.a = 255;
    SDL_Color random_color = mask_color;
    random_color.r = (random_color.r + 1) % 256;

    mask = SDL_DuplicateSurface(surface);
    if (!mask) {
        SDL_Log("SDL_DuplicateSurface() : %s\n", SDL_GetError());
        return false;
    }

    if (!img_borders(mask, mask_color, depth + width) ||
        !img_borders(mask, random_color, depth) ||
        !img_mask(mask, mask_color, (SDL_Color){0, 0, 0, 0}) ||
        !img_replace(mask, mask_color, color, NULL)) {
        SDL_DestroySurface(mask);
        return false;
    }

    SDL_BlitSurface(mask, NULL, surface, NULL);
    SDL_DestroySurface(mask);

    return true;
}
