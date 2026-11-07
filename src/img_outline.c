#include "types.h"

bool _img_is_outline(SDL_Surface *old, i32 x, i32 y, u8 a,
                        u32 w_px, u32 w_nx, u32 w_py, u32 w_ny);

SDL_Surface *img_outline(SDL_Surface *src, SDL_Color color,
                            u32 w_px, u32 w_nx, u32 w_py, u32 w_ny) {
    SDL_Surface *new;
    SDL_Point size = {src->w + w_px + w_nx, src->h + w_py + w_ny};
    SDL_Rect dst = {w_nx, w_ny, src->w, src->h};
    u8 r = color.r, g = color.g, b = color.b, a;
    u32 *row;
    const SDL_PixelFormatDetails *format;
    format = SDL_GetPixelFormatDetails(src->format);

    new = SDL_CreateSurface(size.x, size.y, src->format);
    if (!new) {
        SDL_Log("SDL_CreateSurface() : %s\n", SDL_GetError());
        SDL_DestroySurface(src);
        return NULL;
    }
    SDL_BlitSurface(src, NULL, new, &dst);

    if (!SDL_LockSurface(new)) {
        SDL_Log("SDL_LockSurface() : %s", SDL_GetError());
        SDL_DestroySurface(src);
        SDL_DestroySurface(new);
        return NULL;
    }

    for (i32 y = 0; y < new->h; y++) {
        row = (u32*)((u8*)new->pixels + y * new->pitch);

        for (i32 x = 0; x < new->w; x++) {
            SDL_GetRGBA(row[x], format, NULL, NULL, NULL, NULL, &a);
            if (_img_is_outline(src, x, y, a, w_px, w_nx, w_py, w_ny)) {
                row[x] = SDL_MapSurfaceRGBA(new, r, g, b, color.a);
            }
        }
    }

    SDL_UnlockSurface(new);
    SDL_DestroySurface(src);

    return new;
}
