#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "../text.h"

#define RES_X 480
#define RES_Y 270

#define FONT_SIZE 25

#define BLACK ((SDL_Color){0, 0, 0, 255})
#define WHITE ((SDL_Color){200, 200, 200, 200})
#define FULL_WHITE ((SDL_Color){200, 200, 200, 255})
#define DARK_RED ((SDL_Color){100, 0, 0, 255})
#define ORANGE ((SDL_Color){200, 50, 0, 255})
#define GREEN ((SDL_Color){50, 150, 0, 255})
#define NO_COLOR ((SDL_Color){0, 0, 0, 0})

typedef enum {
    TEXT_NORMAL,
    TEXT_X_GRADIENT,
    TEXT_Y_GRADIENT,
    TEXT_SOLID,
    TEXT_SHADOW,
    TEXT_REPLACE,
    TEXT_MASK,
    TEXT_SPACED_BORDER,
    TEXT_FULL_BORDER,
    TEXT_BORDERS,
    TEXT_FULL_OUTLINE,
    TEXT_OUTLINES,
    TEXT_8_COLORS,
    TEXT_16_COLORS,
    TEXT_32_COLORS,
    TEXT_DOUBLE_GRADIENT,
    TEXT_NEGATIVE,
    TEXT_COUNT
} Text;

// INPUT

typedef struct Input {
    bool key[SDL_SCANCODE_COUNT];
    bool quit;
    SDL_Scancode key_up, key_down, key_left, key_right, key_space;
    bool up, down, left, right, space;
} Input;

void update_input(Input *input) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT :
            input->quit = true;
            break;
        case SDL_EVENT_KEY_DOWN :
            input->key[event.key.scancode] = true;
            break;
        case SDL_EVENT_KEY_UP :
            input->key[event.key.scancode] = false;
            break;
        }
    }
    for (int i = 0; i < 5; i++) {
        (&input->up)[i] = input->key[(&input->key_up)[i]];
    }
}

void load_input(Input *input) {
    input->key_down = SDL_GetScancodeFromKey(SDLK_DOWN, NULL);
    input->key_up = SDL_GetScancodeFromKey(SDLK_UP, NULL);
    input->key_right = SDL_GetScancodeFromKey(SDLK_RIGHT, NULL);
    input->key_left = SDL_GetScancodeFromKey(SDLK_LEFT, NULL);
    input->key_space = SDL_GetScancodeFromKey(SDLK_SPACE, NULL);
}

// APP

typedef struct App {
    Input input;
    SDL_FRect dst[TEXT_COUNT];
    SDL_Texture *texture[TEXT_COUNT];
    TTF_Font *font;
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

void quit_app(App *app, int status) {
    if (app->font) {
        TTF_CloseFont(app->font);
    }
    for (int i = 0; i < TEXT_COUNT; i++) {
        if (app->texture[i]) {
            SDL_DestroyTexture(app->texture[i]);
        }
    }
    if (app->renderer) {
        SDL_DestroyRenderer(app->renderer);
    }
    if (app->window) {
        SDL_DestroyWindow(app->window);
    }
    TTF_Quit();
    SDL_Quit();
    exit(status);
}

void init_app(App *app, const char window_name[], int res_x, int res_y, bool fullscreen) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init() : %s\n", SDL_GetError());
        quit_app(app, EXIT_FAILURE);
    }
    if (!TTF_Init()) {
        printf("TTF_Init() : %s\n", SDL_GetError());
        quit_app(app, EXIT_FAILURE);
    }
    app->window = SDL_CreateWindow(window_name, res_x, res_y, ((fullscreen) ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (!app->window) {
        printf("SDL_CreateWindow() : %s\n", SDL_GetError());
        quit_app(app, EXIT_FAILURE);
    }
    app->renderer = SDL_CreateRenderer(app->window, NULL);
    if (!app->renderer) {
        printf("SDL_CreateRenderer() : %s\n", SDL_GetError());
        quit_app(app, EXIT_FAILURE);
    }
    SDL_SetRenderLogicalPresentation(app->renderer, res_x, res_y, SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
}

void load_app_assets(App *app) {
    SDL_Surface *tmp;
    load_input(&app->input);

    app->font = TTF_OpenFont("upheavtt.ttf", FONT_SIZE);
    if (!app->font) {
        printf("TTF_OpenFont() : %s\n", SDL_GetError());
        quit_app(app, EXIT_FAILURE);
    }

    tmp = create_text("Normal", app->font, ORANGE);
    app->texture[TEXT_NORMAL] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_NORMAL] = (SDL_FRect){10, 10, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("X Gradient", app->font, ORANGE);
    img_gradient(tmp, ORANGE, WHITE, NULL, X_GRADIENT);
    app->texture[TEXT_X_GRADIENT] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_X_GRADIENT] = (SDL_FRect){10, 30, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Y Gradient", app->font, ORANGE);
    img_gradient(tmp, ORANGE, WHITE, NULL, Y_GRADIENT);
    app->texture[TEXT_Y_GRADIENT] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_Y_GRADIENT] = (SDL_FRect){10, 50, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Solid", app->font, ORANGE);
    img_solid(tmp, WHITE, NULL);
    app->texture[TEXT_SOLID] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_SOLID] = (SDL_FRect){10, 70, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Shadow", app->font, ORANGE);
    tmp = img_shadow(tmp, WHITE, (SDL_Point){1, -1});
    app->texture[TEXT_SHADOW] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_SHADOW] = (SDL_FRect){10, 90, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Replace", app->font, ORANGE);
    tmp = img_shadow(tmp, WHITE, (SDL_Point){1, -1});
    img_replace(tmp, ORANGE, GREEN, NULL);
    app->texture[TEXT_REPLACE] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_REPLACE] = (SDL_FRect){10, 110, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Mask", app->font, ORANGE);
    tmp = img_shadow(tmp, FULL_WHITE, (SDL_Point){1, -1});
    img_mask(tmp, FULL_WHITE, NO_COLOR);
    app->texture[TEXT_MASK] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_MASK] = (SDL_FRect){10, 130, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Full Border", app->font, ORANGE);
    img_full_border(tmp, WHITE, 1);
    app->texture[TEXT_FULL_BORDER] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_FULL_BORDER] = (SDL_FRect){170, 10, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Spaced Border", app->font, ORANGE);
    img_spaced_border(tmp, WHITE, 1, 1);
    app->texture[TEXT_SPACED_BORDER] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_SPACED_BORDER] = (SDL_FRect){170, 30, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Borders", app->font, ORANGE);
    img_border(tmp, FULL_WHITE, 0, 1, 0, 0);
    img_border(tmp, DARK_RED, 1, 0, 0, 0);
    img_border(tmp, DARK_RED, 0, 0, 1, 0);
    img_border(tmp, FULL_WHITE, 0, 0, 0, 1);
    app->texture[TEXT_BORDERS] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_BORDERS] = (SDL_FRect){170, 50, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Full Outline", app->font, ORANGE);
    tmp = img_full_outline(tmp, WHITE, 1);
    app->texture[TEXT_FULL_OUTLINE] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_FULL_OUTLINE] = (SDL_FRect){170, 70, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Outlines", app->font, ORANGE);
    tmp = img_outline(tmp, FULL_WHITE, 0, 1, 0, 0);
    tmp = img_outline(tmp, DARK_RED, 1, 0, 0, 0);
    tmp = img_outline(tmp, DARK_RED, 0, 0, 1, 0);
    tmp = img_outline(tmp, FULL_WHITE, 0, 0, 0, 1);
    app->texture[TEXT_OUTLINES] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_OUTLINES] = (SDL_FRect){170, 90, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("8^3 Colors", app->font, ORANGE);
    img_gradient(tmp, ORANGE, WHITE, NULL, Y_GRADIENT);
    img_posterize(tmp, (SDL_Color){8, 8, 8, 8});
    app->texture[TEXT_8_COLORS] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_8_COLORS] = (SDL_FRect){170, 110, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("16^3 Colors", app->font, ORANGE);
    img_gradient(tmp, ORANGE, WHITE, NULL, Y_GRADIENT);
    img_posterize(tmp, (SDL_Color){16, 16, 16, 16});
    app->texture[TEXT_16_COLORS] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_16_COLORS] = (SDL_FRect){170, 130, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("32^3 Colors", app->font, ORANGE);
    img_gradient(tmp, ORANGE, WHITE, NULL, Y_GRADIENT);
    img_posterize(tmp, (SDL_Color){32, 32, 32, 32});
    app->texture[TEXT_32_COLORS] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_32_COLORS] = (SDL_FRect){170, 150, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Double Gradient", app->font, ORANGE);
    img_double_gradient(tmp, ORANGE, WHITE, 0.5f, X_GRADIENT);
    app->texture[TEXT_DOUBLE_GRADIENT] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_DOUBLE_GRADIENT] = (SDL_FRect){170, 170, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Negative", app->font, ORANGE);
    img_double_gradient(tmp, ORANGE, WHITE, 0.5f, X_GRADIENT);
    img_negative(tmp, NULL);
    app->texture[TEXT_NEGATIVE] = surface_to_texture(tmp, app->renderer);
    app->dst[TEXT_NEGATIVE] = (SDL_FRect){170, 190, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);
}

// MAIN

int main(void) {
    App app;

    init_app(&app, "Demo Text", RES_X, RES_Y, true);
    load_app_assets(&app);

    while (!app.input.quit) {
        update_input(&app.input);
        SDL_RenderClear(app.renderer);

        for (int i = 0; i < TEXT_COUNT; i++) {
            SDL_RenderTexture(app.renderer, app.texture[i], NULL, &app.dst[i]);
        }

        SDL_RenderPresent(app.renderer);
        SDL_Delay((int)(1000 / 60));
    }

    quit_app(&app, EXIT_SUCCESS);
}
