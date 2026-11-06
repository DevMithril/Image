#include "types.h"

/**
 * Indique si un pixel donné est dans la bordure ou pas
 * \param surface la surface en cour de modification
 * \param x coordonnée x du pixel sur `surface`
 * \param y coordonnée y du pixel sur `surface`
 * \param a la valeur de l'alpha du pixel
 * \param d_px l'épaisseur de contour à écraser (en pixel) du côté droit
 * \param d_nx l'épaisseur de contour à écraser (en pixel) du côté gauche
 * \param d_py l'épaisseur de contour à écraser (en pixel) du côté bas
 * \param d_ny l'épaisseur de contour à écraser (en pixel) du côté haut
 * \return `true` si le pixel est sur le contour à écraser, `false` sinon
 * \note `old` n'est ni détruit, ni modifié par cette fonction
 */
bool _img_is_border(SDL_Surface *surface, i32 x, i32 y, u8 a,
                    u32 d_px, u32 d_nx, u32 d_py, u32 d_ny) {
    u32 *row;
    const SDL_PixelFormatDetails *format;

    if (!a) {
        return false;
    }
    if (x - (i32)d_nx < 0 ||
        y - (i32)d_ny < 0 ||
        x + (i32)d_px >= surface->w ||
        y + (i32)d_py >= surface->h) {
        return true;
    }
    format = SDL_GetPixelFormatDetails(surface->format);

    for (u32 sub_y = y - d_ny; sub_y < y + d_py + 1; sub_y++) {
        row = (u32*)((u8*)surface->pixels + sub_y * surface->pitch);

        for (u32 sub_x = x - d_nx; sub_x < x + d_px + 1; sub_x++) {
            SDL_GetRGBA(row[sub_x], format, NULL, NULL, NULL, NULL, &a);
            if (!a) {
                return true;
            }
        }
    }

    return false;
}
