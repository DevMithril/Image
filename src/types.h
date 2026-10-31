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
    X_GRADIENT,
    Y_GRADIENT
} Gradient_Axis;

#endif
