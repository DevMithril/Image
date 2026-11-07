#ifndef _TYPES_H
#define _TYPES_H
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long int u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long int i64;

typedef float f32;
typedef double f64;

typedef enum Gradient_Axis {
    GRADIENT_NONE,
    GRADIENT_X,
    GRADIENT_Y
} Gradient_Axis;

typedef struct Style_Config {
    SDL_Point shadow_offset;
    Gradient_Axis gradient_axis;
    f32 gradient_mid;
    u32 border;
    u32 border_margin;
    u32 outline;
    u32 outline_margin;
    SDL_Color primary;
    SDL_Color secondary;
    SDL_Color shadow_color;
    SDL_Color border_color;
    SDL_Color outline_color;
    SDL_Color posterize_values;
} Style_Config;

#endif
