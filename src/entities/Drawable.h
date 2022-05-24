#pragma once

#include <vector>

#include "renderer/RendererConstants.h"

class Drawable {
public:
    Drawable(Color color, DrawMode mode)
       : m_color(color), m_mode(mode) {} 

    virtual void draw() {}

    virtual ~Drawable() = default;

    Color m_color;
    DrawMode m_mode;
};
