#include "types.h"

/**
 * Indique si un pixel donné est dans le nouveau contour ou pas
 * \param old ancienne surface
 * \param x coordonnée x du pixel sur la nouvelle surface
 * \param y coordonnée y du pixel sur la nouvelle surface
 * \param a la valeur de l'alpha du pixel
 * \param w_px l'épaisseur des nouveaux contours (en pixel) du côté droit
 * \param w_nx l'épaisseur des nouveaux contours (en pixel) du côté gauche
 * \param w_py l'épaisseur des nouveaux contours (en pixel) du côté bas
 * \param w_ny l'épaisseur des nouveaux contours (en pixel) du côté haut
 * \return `true` si le pixel est sur le contour à dessiner, `false` sinon
 * \note `old` n'est ni détruit, ni modifié par cette fonction
 */
bool _img_is_outline(SDL_Surface *old, i32 x, i32 y, u8 a,
                        u32 w_px, u32 w_nx, u32 w_py, u32 w_ny) {
    if (a) {
        return false;
    }

    x -= (i32)w_nx;
    y -= (i32)w_ny;

    i32 min_x = (x - (i32)w_px < 0) ? 0 : x - (i32)w_px;
    i32 min_y = (y - (i32)w_py < 0) ? 0 : y - (i32)w_py;
    i32 max_x = (x + (i32)w_nx > old->w - 1) ? old->w - 1 : x + (i32)w_nx;
    i32 max_y = (y + (i32)w_ny > old->h - 1) ? old->h - 1 : y + (i32)w_ny;
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
