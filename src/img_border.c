#include "types.h"

bool _img_is_border(SDL_Surface *surface, i32 x, i32 y, u32 depth, u8 a);

bool img_border(SDL_Surface *surface, SDL_Color color, u32 depth) {
    f32 color_a = color.a / 255.0f;
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
            if (_img_is_border(surface, x, y, depth, a)) {
                r = (1 - color_a) * r + color_a * color.r;
                g = (1 - color_a) * g + color_a * color.g;
                b = (1 - color_a) * b + color_a * color.b;
                row[x] = SDL_MapSurfaceRGBA(surface, r, g, b, a);
            }
        }
    }

    SDL_UnlockSurface(surface);

    return true;
}
