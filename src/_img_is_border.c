#include "types.h"

/**
 * Indique si un pixel donné est dans la bordure ou pas
 * \param surface la surface en cour de modification
 * \param x coordonnée x du pixel sur `surface`
 * \param y coordonnée y du pixel sur `surface`
 * \param depth l'épaisseur de contour à écraser (en pixel)
 * \param a la valeur de l'alpha du pixel
 * \return `true` si le pixel est sur le contour à écraser, `false` sinon
 * \note `old` n'est ni détruit, ni modifié par cette fonction
 */
bool _img_is_border(SDL_Surface *surface, i32 x, i32 y, u32 depth, u8 a) {
    u32 *row;
    const SDL_PixelFormatDetails *format;

    if (!a) {
        return false;
    }
    if (x - (i32)depth < 0 ||
        y - (i32)depth < 0 ||
        x + (i32)depth >= surface->w ||
        y + (i32)depth >= surface->h) {
        return true;
    }
    format = SDL_GetPixelFormatDetails(surface->format);

    for (u32 sub_y = y - depth; sub_y < y + depth + 1; sub_y++) {
        row = (u32*)((u8*)surface->pixels + sub_y * surface->pitch);

        for (u32 sub_x = x - depth; sub_x < x + depth + 1; sub_x++) {
            SDL_GetRGBA(row[sub_x], format, NULL, NULL, NULL, NULL, &a);
            if (!a) {
                return true;
            }
        }
    }

    return false;
}
