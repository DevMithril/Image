#include "types.h"

bool img_mask(SDL_Surface *surface, SDL_Color keep, SDL_Color new) {
    u8 r, g, b, a;
    u32 *row;
    const SDL_PixelFormatDetails *format;

    format = SDL_GetPixelFormatDetails(surface->format);

    if (!SDL_LockSurface(surface)) {
        SDL_Log("SDL_LockSurface() : %s", SDL_GetError());
        return false;
    }

    for (i32 y = 0; y < surface->h; y++) {
        row = (u32*)((u8*)surface->pixels + y * surface->pitch);

        for (i32 x = 0; x < surface->w; x++) {
            SDL_GetRGBA(row[x], format, NULL, &r, &g, &b, &a);
            if (r != keep.r || g != keep.g || b != keep.b || a != keep.a) {
                row[x] = SDL_MapSurfaceRGBA(surface, new.r, new.g, new.b, new.a);
            }
        }
    }

    SDL_UnlockSurface(surface);

    return true;
}
