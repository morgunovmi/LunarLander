#pragma once

#include "Object.h"
#include "renderer/Renderer.h"

class Ground : public Object {
public:
    Ground(std::vector<Vec2i>& verts, std::vector<u8>& indices, Color color, DrawMode mode = LINES)
        : Object(color, mode), m_verts(verts), m_indices(indices) {}

    virtual void draw() override {
        Renderer::drawVerts(m_verts, m_indices, m_color, m_mode);
    }

private:
    std::vector<Vec2i>& m_verts;
    std::vector<u8>& m_indices;
};
