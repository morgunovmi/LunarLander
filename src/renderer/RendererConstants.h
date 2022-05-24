#pragma once 

#include "math/math.h"

union Color{
    struct{
        u8 b;
        u8 g;
        u8 r;
        u8 a;
    };
    u8 c8[4];
    u32 c32;
};

static const Color Black{{0, 0, 0, 100}};
static const Color White{{255, 255, 255, 100}};
static const Color Red{{0, 0, 255, 100}};
static const Color Green{{0, 255, 0, 100}};
static const Color Blue{{255, 0, 0, 100}};

enum DrawMode {
    LINES,
    TRIANGLES,
    POINTS,
};
