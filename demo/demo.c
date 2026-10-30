#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "../text.h"

#define RES_X 320
#define RES_Y 240

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
    input->down = input->key[input->key_down];
    input->left = input->key[input->key_left];
    input->right = input->key[input->key_right];
    input->up = input->key[input->key_up];
    input->space = input->key[input->key_space];
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
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

void quit_app(App *app, int status) {
    if (app->renderer) {
        SDL_DestroyRenderer(app->renderer);
    }
    if (app->window) {
        SDL_DestroyWindow(app->window);
    }
    SDL_Quit();
    exit(status);
}

void init_app(App *app, const char window_name[], int res_x, int res_y, bool fullscreen) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init() : %s\n", SDL_GetError());
        quit_app(app, EXIT_FAILURE);
    }
    if (fullscreen) {
        app->window = SDL_CreateWindow(window_name, res_x, res_y, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    } else {
        app->window = SDL_CreateWindow(window_name, res_x, res_y, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    }
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
    load_input(&app->input);
}

// MAIN

int main(void) {
    App app = {.renderer = NULL, .window = NULL};

    init_app(&app, "Demo Text", RES_X, RES_Y, false);
    load_app_assets(&app);

    while (!app.input.quit) {
        update_input(&app.input);
        SDL_RenderClear(app.renderer);

        SDL_RenderPresent(app.renderer);
        SDL_Delay((int)(1000 / 60));
    }

    quit_app(&app, EXIT_SUCCESS);
}
