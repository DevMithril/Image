#include "types.h"

bool img_solid(SDL_Surface *surface, SDL_Color color, SDL_Rect *clip) {
    f32 color_a = color.a / 255.0f;
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
            r = (1 - color_a) * r + color_a * color.r;
            g = (1 - color_a) * g + color_a * color.g;
            b = (1 - color_a) * b + color_a * color.b;
            row[x] = SDL_MapSurfaceRGBA(surface, r, g, b, a);
        }
    }

    SDL_UnlockSurface(surface);

    return true;
}
