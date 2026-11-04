#include "types.h"

bool img_gradient(SDL_Surface *surface, SDL_Color src, SDL_Color dst,
                   SDL_Rect *clip, Gradient_Axis axis) {
    f32 t, inv_delta, color_a;
    u8 r, g, b, a, br, bg, bb, ba;
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
            r = (u8)(src.r + (dst.r - src.r) * t);
            g = (u8)(src.g + (dst.g - src.g) * t);
            b = (u8)(src.b + (dst.b - src.b) * t);
            a = (u8)(src.a + (dst.a - src.a) * t);
        }

        row = (u32*)((u8*)surface->pixels + y * surface->pitch);

        for (i32 x = area.x; x < area.x + area.w; x++) {
            if (axis == X_GRADIENT) {
                t = (f32)(x - area.x) * inv_delta;
                r = (u8)(src.r + (dst.r - src.r) * t);
                g = (u8)(src.g + (dst.g - src.g) * t);
                b = (u8)(src.b + (dst.b - src.b) * t);
                a = (u8)(src.a + (dst.a - src.a) * t);
            }

            SDL_GetRGBA(row[x], format, NULL, &br, &bg, &bb, &ba);
            color_a = a / 255.0f;
            br = (1 - color_a) * br + color_a * r;
            bg = (1 - color_a) * bg + color_a * g;
            bb = (1 - color_a) * bb + color_a * b;
            row[x] = SDL_MapSurfaceRGBA(surface, br, bg, bb, ba);
        }
    }

    SDL_UnlockSurface(surface);

    return true;
}
