#include "types.h"

bool img_posterize(SDL_Surface *surface, SDL_Color ranges) {
    u8 r, g, b, a;
    u32 *row;
    const SDL_PixelFormatDetails *format;
    format = SDL_GetPixelFormatDetails(surface->format);
    ranges.r = (ranges.r) ? (255 / ranges.r) : 1;
    ranges.g = (ranges.g) ? (255 / ranges.g) : 1;
    ranges.b = (ranges.b) ? (255 / ranges.b) : 1;
    ranges.a = (ranges.a) ? (255 / ranges.a) : 1;

    if (!SDL_LockSurface(surface)) {
        SDL_Log("SDL_LockSurface() : %s", SDL_GetError());
        return false;
    }

    for (i32 y = 0; y < surface->h; y++) {
        row = (u32*)((u8*)surface->pixels + y * surface->pitch);

        for (i32 x = 0; x < surface->w; x++) {
            SDL_GetRGBA(row[x], format, NULL, &r, &g, &b, &a);
            r -= r % ranges.r;
            g -= g % ranges.g;
            b -= b % ranges.b;
            a -= a % ranges.a;
            row[x] = SDL_MapSurfaceRGBA(surface, r, g, b, a);
        }
    }

    SDL_UnlockSurface(surface);

    return true;
}
