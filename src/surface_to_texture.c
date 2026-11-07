#include "types.h"

SDL_Texture *surface_to_texture(SDL_Surface *surface, SDL_Renderer *renderer) {
    SDL_Texture *texture = NULL, *tmp = NULL;

    tmp = SDL_CreateTextureFromSurface(renderer, surface);
    if(!tmp) {
        SDL_Log("SDL_CreateTextureFromSurface() : %s\n", SDL_GetError());
        return NULL;
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                            SDL_TEXTUREACCESS_TARGET, surface->w, surface->h);
    if(!texture) {
        SDL_Log("SDL_CreateTexture() : %s\n", SDL_GetError());
        SDL_DestroyTexture(tmp);
        return NULL;
    }

    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, tmp, NULL, NULL);
    SDL_DestroyTexture(tmp);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    return texture;
}
