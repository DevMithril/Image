#include "types.h"

bool img_border(SDL_Surface *surface, SDL_Color color,
                u32 d_px, u32 d_nx, u32 d_py, u32 d_ny);

bool img_full_border(SDL_Surface *surface, SDL_Color color, u32 depth) {
    return img_border(surface, color, depth, depth, depth, depth);
}
