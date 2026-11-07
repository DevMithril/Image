#include "types.h"

bool img_gradient(SDL_Surface *surface, SDL_Color src, SDL_Color dst,
                   SDL_Rect *clip, Gradient_Axis axis);

bool img_double_gradient(SDL_Surface *surface, SDL_Color src, SDL_Color dst,
                            f32 gradient_mid, Gradient_Axis axis) {
    SDL_Rect clip1, clip2 = {0, 0, surface->w, surface->h};
    clip1 = clip2;

    switch (axis) {
    case GRADIENT_X :
        clip1.w = (i32)(clip1.w * gradient_mid);
        clip2.x = clip1.w;
        clip2.w -= clip1.w;
    break;
    case GRADIENT_Y :
        clip1.h = (i32)(clip1.h * gradient_mid);
        clip2.y = clip1.w;
        clip2.h -= clip1.w;
    break;
    default:
        return true;
    }

    return (img_gradient(surface, dst, src, &clip1, axis) &&
            img_gradient(surface, src, dst, &clip2, axis));
}
