#include "types.h"

bool make_gradient(SDL_Surface *surface, SDL_Color src, SDL_Color dst,
                   SDL_Rect *clip, Gradient_Axis axis) {
    f32 t, inv_delta;
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
    inv_delta = (axis == X_GRADIENT) ?
        ((area.w > 1) ? 1.0f / (f32)(area.w - 1) : 0.0f) :
        ((area.h > 1) ? 1.0f / (f32)(area.h - 1) : 0.0f);

    if (!SDL_LockSurface(surface)) {
        SDL_Log("SDL_LockSurface() : %s", SDL_GetError());
        return false;
    }

    for (i32 y = area.y; y < area.y + area.h; y++) {
        if (axis == Y_GRADIENT) {
            t = (f32)(y - area.y) * inv_delta;
            r = (u8)(dst.r + (src.r - dst.r) * t);
            g = (u8)(dst.g + (src.g - dst.g) * t);
            b = (u8)(dst.b + (src.b - dst.b) * t);
        }

        row = (u32*)((u8*)surface->pixels + y * surface->pitch);

        for (i32 x = area.x; x < area.x + area.w; x++) {
            if (axis == X_GRADIENT) {
                t = (f32)(x - area.x) * inv_delta;
                r = (u8)(dst.r + (src.r - dst.r) * t);
                g = (u8)(dst.g + (src.g - dst.g) * t);
                b = (u8)(dst.b + (src.b - dst.b) * t);
            }

            SDL_GetRGBA(row[x], format, NULL, NULL, NULL, NULL, &a);
            row[x] = SDL_MapSurfaceRGBA(surface, r, g, b, a);
        }
    }

    SDL_UnlockSurface(surface);

    return true;
}
