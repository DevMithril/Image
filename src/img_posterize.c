#include "types.h"

bool img_posterize(SDL_Surface *surface, i32 r, i32 g, i32 b, i32 a) {
    u8 br, bg, bb, ba;
    u32 *row;
    const SDL_PixelFormatDetails *format;
    format = SDL_GetPixelFormatDetails(surface->format);
    r = (r) ? 255 / r : 0;
    g = (g) ? 255 / g : 0;
    b = (b) ? 255 / b : 0;
    a = (a) ? 255 / a : 0;

    if (!SDL_LockSurface(surface)) {
        SDL_Log("SDL_LockSurface() : %s", SDL_GetError());
        return false;
    }

    for (i32 y = 0; y < surface->h; y++) {
        row = (u32*)((u8*)surface->pixels + y * surface->pitch);

        for (i32 x = 0; x < surface->w; x++) {
            SDL_GetRGBA(row[x], format, NULL, &br, &bg, &bb, &ba);
            br -= br % r;
            bg -= bg % g;
            bb -= bb % b;
            ba -= ba % a;
            row[x] = SDL_MapSurfaceRGBA(surface, br, bg, bb, ba);
        }
    }

    SDL_UnlockSurface(surface);

    return true;
}
