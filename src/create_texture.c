#include "types.h"

SDL_Texture *create_texture(int w, int h, SDL_Renderer *renderer) {
    SDL_Texture *texture = NULL;

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET, w, h);
    if (!texture) {
        SDL_Log("SDL_CreateTexture() : %s\n", SDL_GetError());
        return NULL;
    }

    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

    return texture;
}
