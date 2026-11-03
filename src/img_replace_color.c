#include "types.h"

bool img_replace_color(SDL_Surface *surface, SDL_Color base, SDL_Color new,
                        SDL_Rect *clip) {
    u8 r, g, b, a;
    u32 *row;
    const SDL_PixelFormatDetails *format;
    SDL_Rect area, bounds = (SDL_Rect){0, 0, surface->w, surface->h};

    if (clip) {
        if (!SDL_GetRectIntersection(&bounds, clip, &area)) {
            return true;
        }
    } else {
        area = bounds;
    }

    format = SDL_GetPixelFormatDetails(surface->format);

    if (!SDL_LockSurface(surface)) {
        SDL_Log("SDL_LockSurface() : %s", SDL_GetError());
        return false;
    }

    for (i32 y = area.y; y < area.y + area.h; y++) {
        row = (u32*)((u8*)surface->pixels + y * surface->pitch);

        for (i32 x = area.x; x < area.x + area.w; x++) {
            SDL_GetRGBA(row[x], format, NULL, &r, &g, &b, &a);
            if (r == base.r && g == base.g && b == base.b) {
                row[x] = SDL_MapSurfaceRGBA(surface, new.r, new.g, new.b, a);
            }
        }
    }

    SDL_UnlockSurface(surface);

    return true;
}
