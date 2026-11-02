#include "types.h"

#define abs(x) (((x) < 0) ? -(x) : (x))

bool make_solid(SDL_Surface *surface, SDL_Color color, SDL_Rect *clip);

SDL_Surface *make_shadow(SDL_Surface *src, SDL_Color color, SDL_Point offset) {
    SDL_Surface *new, *shade;
    SDL_Point origin, size;
    SDL_Rect dst_src, dst_shade;

    origin.x = (offset.x < 0) ? -offset.x : 0;
    origin.y = (offset.y < 0) ? -offset.y : 0;
    size.x = src->w + abs(offset.x);
    size.y = src->h + abs(offset.y);

    dst_src = (SDL_Rect){origin.x, origin.y, src->w, src->h};
    dst_shade = dst_src;
    dst_shade.x += offset.x;
    dst_shade.y += offset.y;

    shade = SDL_DuplicateSurface(src);
    if (!shade) {
        SDL_Log("SDL_DuplicateSurface() : %s\n", SDL_GetError());
        SDL_DestroySurface(src);
        return NULL;
    }
    make_solid(shade, color, NULL);

    new = SDL_CreateSurface(size.x, size.y, src->format);
    if (!new) {
        SDL_Log("SDL_CreateSurface() : %s\n", SDL_GetError());
        SDL_DestroySurface(src);
        SDL_DestroySurface(shade);
        return NULL;
    }

    SDL_BlitSurface(shade, NULL, new, &dst_shade);
    SDL_BlitSurface(src, NULL, new, &dst_src);

    SDL_DestroySurface(src);
    SDL_DestroySurface(shade);

    return new;
}
