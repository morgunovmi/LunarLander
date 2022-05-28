#pragma once

#include "Object.h"
#include "renderer/Renderer.h"

class Ground : public Object {
public:
    Ground(std::vector<Vec2i>& verts, std::vector<u8>& indices, Color color, std::string_view tag)
        : Object(color, LINES, tag), m_verts(verts), m_indices(indices) {}

    virtual void draw() override {
        Renderer::drawVerts(m_verts, m_indices, m_color, m_mode);
    }

    const std::vector<Vec2i>& getVerts() const { return m_verts; }

private:
    std::vector<Vec2i>& m_verts;
    std::vector<u8>& m_indices;
};
