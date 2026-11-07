#include "types.h"

SDL_Surface *img_outline(SDL_Surface *src, SDL_Color color,
                            u32 w_px, u32 w_nx, u32 w_py, u32 w_ny);

SDL_Surface *img_full_outline(SDL_Surface *src, SDL_Color color, u32 width) {
    return img_outline(src, color, width, width, width, width);
}
