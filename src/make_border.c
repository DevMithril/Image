#include "types.h"

/**
 * Indique si un pixel donné est dans la bordure ou pas
 */
bool is_border(SDL_Surface *surface, i32 x, i32 y, u32 depth, u8 a) {
    u32 *row;
    const SDL_PixelFormatDetails *format;

    if (!a) {
        return false;
    }
    if (x - (i32)depth < 0 ||
        y - (i32)depth < 0 ||
        x + (i32)depth >= surface->w ||
        y + (i32)depth >= surface->h) {
        return true;
    }
    format = SDL_GetPixelFormatDetails(surface->format);

    for (u32 sub_y = y - depth; sub_y < y + depth + 1; sub_y++) {
        row = (u32*)((u8*)surface->pixels + sub_y * surface->pitch);

        for (u32 sub_x = x - depth; sub_x < x + depth + 1; sub_x++) {
            SDL_GetRGBA(row[sub_x], format, NULL, NULL, NULL, NULL, &a);
            if (!a) {
                return true;
            }
        }
    }

    return false;
}

bool make_border(SDL_Surface *surface, SDL_Color color, u32 depth) {
    u8 r = color.r, g = color.g, b = color.b, a;
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
            SDL_GetRGBA(row[x], format, NULL, NULL, NULL, NULL, &a);
            if (is_border(surface, x, y, depth, a)) {
                row[x] = SDL_MapSurfaceRGBA(surface, r, g, b, a);
            }
        }
    }

    SDL_UnlockSurface(surface);

    return true;
}
