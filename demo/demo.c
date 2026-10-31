#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "../text.h"

#define RES_X 320
#define RES_Y 240

#define BLACK ((SDL_Color){0, 0, 0, 255})
#define ORANGE ((SDL_Color){200, 100, 0, 255})
#define CYAN ((SDL_Color){0, 100, 200, 255})

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
    SDL_FRect dst_normal, dst_x_gradient, dst_y_gradient;
    SDL_Texture *normal, *x_gradient, *y_gradient;
    TTF_Font *font;
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

void quit_app(App *app, int status) {
    if (app->font) {
        TTF_CloseFont(app->font);
    }
    if (app->normal) {
        SDL_DestroyTexture(app->normal);
    }
    if (app->x_gradient) {
        SDL_DestroyTexture(app->x_gradient);
    }
    if (app->y_gradient) {
        SDL_DestroyTexture(app->y_gradient);
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
    SDL_SetRenderLogicalPresentation(app->renderer, res_x, res_y, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

void load_app_assets(App *app) {
    SDL_Surface *tmp;
    load_input(&app->input);

    app->font = TTF_OpenFont("upheavtt.ttf", 15);
    if (!app->font) {
        printf("TTF_OpenFont() : %s\n", SDL_GetError());
        quit_app(app, EXIT_FAILURE);
    }

    tmp = create_text("Normal", app->font, ORANGE);
    app->normal = surface_to_texture(tmp, app->renderer);
    app->dst_normal = (SDL_FRect){10, 10, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("X Gradient", app->font, ORANGE);
    make_gradient(tmp, ORANGE, CYAN, NULL, X_GRADIENT);
    app->x_gradient = surface_to_texture(tmp, app->renderer);
    app->dst_x_gradient = (SDL_FRect){10, 50, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);

    tmp = create_text("Y Gradient", app->font, ORANGE);
    make_gradient(tmp, ORANGE, CYAN, NULL, Y_GRADIENT);
    app->y_gradient = surface_to_texture(tmp, app->renderer);
    app->dst_y_gradient = (SDL_FRect){10, 90, tmp->w, tmp->h};
    SDL_DestroySurface(tmp);
}

// MAIN

int main(void) {
    App app;

    init_app(&app, "Demo Text", RES_X, RES_Y, false);
    load_app_assets(&app);

    while (!app.input.quit) {
        update_input(&app.input);
        SDL_RenderClear(app.renderer);

        SDL_RenderTexture(app.renderer, app.normal, NULL, &app.dst_normal);
        SDL_RenderTexture(app.renderer, app.x_gradient, NULL, &app.dst_x_gradient);
        SDL_RenderTexture(app.renderer, app.y_gradient, NULL, &app.dst_y_gradient);

        SDL_RenderPresent(app.renderer);
        SDL_Delay((int)(1000 / 60));
    }

    quit_app(&app, EXIT_SUCCESS);
}
