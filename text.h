/*
================================================================================
    zlib License
================================================================================

Copyright (c) 2026 Théophane Bruyelles

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from
the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment in the product
   documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

*/

#ifndef TEXT_LIB_H
#define TEXT_LIB_H
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

/*
================================================================================
    Text
================================================================================
*/
// TODO : make_outline()
// TODO : fonction pour limiter la palette de couleur
typedef enum Gradient_Axis {
    X_GRADIENT,
    Y_GRADIENT
} Gradient_Axis;

/**
 * Crée une surface au format SDL_PIXELFORMAT_RGBA32 avec un texte dessus
 * \param str le texte à render sur la surface (null-terminated string)
 * \param font la police du texte
 * \param color la couleur du texte
 * \return La surface avec le texte dessus
 */
SDL_Surface *create_text(const char str[], TTF_Font *font, SDL_Color color);

/**
 * Crée une nouvelle surface ajoutant une ombre à `src`
 * \param src la surface d'origine
 * \param color la couleur de l'ombre
 * \param offset position de l'ombre par rapport à la surface d'origine
 * \return La nouvelle surface avec l'ombre, NULL en cas d'erreur
 * \note `src` est présumé être au format SDL_PIXELFORMAT_RGBA32
 * \note `src` est détruit par cette fonction
 */
SDL_Surface *make_shadow(SDL_Surface *src, SDL_Color color, SDL_Point offset);

/**
 * Dessine des bordures sur les contours des éléments opaques d'une surface
 * \param surface la surface à modifier
 * \param color la couleur des bordures
 * \param depth l'épaisseur des contours (en pixel)
 * \return `false` en cas d'échec, `true` sinon
 * \note `surface` n'est pas détruit par cette fonction
 * \note les bordures conservent la transparence initiale
 */
bool make_border(SDL_Surface *surface, SDL_Color color, unsigned int depth);

/**
 * Crée un dégradé sur une surface en concervant la transparence
 * \param surface la surface à modifier
 * \param src la couleur de départ du dégradé (en haut ou à gauche)
 * \param dst la couleur d'arrivée du dégradé (en bas ou à droite)
 * \param clip rectangle où doit être fait le dégradé sur `surface`,
 *             NULL pour toute la surface
 * \param axis axe sur lequel sera fait le dégradé
 * \return `false` en cas d'échec, `true` sinon
 * \note `surface` est présumé être au format SDL_PIXELFORMAT_RGBA32
 * \note `surface` n'est pas détruit par cette fonction
 */
bool make_gradient(SDL_Surface *surface, SDL_Color src, SDL_Color dst,
                   SDL_Rect *clip, Gradient_Axis axis);

/**
 * Recolorise une surface en concervant la transparence
 * \param surface la surface à modifier
 * \param color la couleur à appliquer
 * \param clip rectangle à modifier sur `surface`, NULL pour toute la surface
 * \return `false` en cas d'échec, `true` sinon
 * \note `surface` est présumé être au format SDL_PIXELFORMAT_RGBA32
 * \note `surface` n'est pas détruit par cette fonction
 */
bool make_solid(SDL_Surface *surface, SDL_Color color, SDL_Rect *clip);
// TODO : prendre en compte l'alpha de `color`

/**
 * Converti une surface en texture pouvant être utilisée comme 
 * destination de rendu
 * \param surface surface à convertir
 * \param renderer renderer sur lequel est créée la texture
 * \return La texture sur laquelle est copiée la surface
 * \note `surface` n'est ni modifié ni détruit par cette fonction
 */
SDL_Texture *surface_to_texture(SDL_Surface *surface, SDL_Renderer *renderer);

/**
 * Crée une texture "vide" pouvant être utilisée comme destination de rendu
 * \param w largeur de la texture en pixel
 * \param h hauteur de la texture en pixel
 * \param renderer renderer sur lequel est créée la texture
 * \return La texture vide créée
 */
SDL_Texture *create_texture(int w, int h, SDL_Renderer *renderer);

#endif
