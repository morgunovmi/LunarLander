#pragma once

#include <vector>

#include "renderer/RendererConstants.h"

class Drawable {
public:
    Drawable(const std::vector<Vec2i>& verts, const std::vector<u8>& indices, Color color, DrawMode mode)
       : m_verts(verts), m_indices(indices), m_color(color), m_mode(mode) {} 


    const std::vector<Vec2i>& m_verts;
    const std::vector<u8>& m_indices;
    Color m_color;
    DrawMode m_mode;
};
