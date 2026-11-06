#include "types.h"

/**
 * Indique si un pixel donné est dans le nouveau contour ou pas
 * \param old ancienne surface
 * \param x coordonnée x du pixel sur la nouvelle surface
 * \param y coordonnée y du pixel sur la nouvelle surface
 * \param width l'épaisseur des nouveaux contours (en pixel)
 * \param a la valeur de l'alpha du pixel
 * \return `true` si le pixel est sur le contour à dessiner, `false` sinon
 * \note `old` n'est ni détruit, ni modifié par cette fonction
 */
bool _img_is_outline(SDL_Surface *old, i32 x, i32 y, i32 width, u8 a) {
    if (a) {
        return false;
    }

    i32 min_x = (x - 2 * width < 0) ? 0 : x - 2 * width;
    i32 min_y = (y - 2 * width < 0) ? 0 : y - 2 * width;
    i32 max_x = (x > old->w - 1) ? old->w - 1 : x;
    i32 max_y = (y > old->h - 1) ? old->h - 1 : y;
    u32 *row;
    const SDL_PixelFormatDetails *format;
    format = SDL_GetPixelFormatDetails(old->format);

    for (i32 sub_y = min_y; sub_y <= max_y; sub_y++) {
        row = (u32*)((u8*)old->pixels + sub_y * old->pitch);

        for (i32 sub_x = min_x; sub_x <= max_x; sub_x++) {
            SDL_GetRGBA(row[sub_x], format, NULL, NULL, NULL, NULL, &a);
            if (a) {
                return true;
            }
        }
    }

    return false;
}
