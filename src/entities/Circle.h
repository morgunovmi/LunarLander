#pragma once

#include "Object.h"
#include "renderer/Renderer.h"

class Circle : public Object {
public:
    Circle(Vec2f pos, float radius, Color color, u16 numPoints)
        : Object(color, TRIANGLES), m_position(pos), m_radius(radius), m_points(numPoints) { assert(numPoints >= 3); }

    virtual void draw() override {
        float angle = static_cast<float>(2 * M_PI); 
        angle /= m_points;

        std::vector<Vec2i> verts;
        verts.push_back(Vec2i{static_cast<int>(m_position.x), static_cast<int>(m_position.y)});
        Vec2f vec{0.f, m_radius};
        for (size_t i = 0; i < m_points - 1; ++i) {
            const auto p = m_position + vec;
            verts.push_back(Vec2i{static_cast<int>(p.x), static_cast<int>(p.y)});
            vec = mat2vec(rotateAround({0.f, 0.f}, angle) * vec2mat(vec));
        }
        const auto p = m_position + vec;
        verts.push_back(Vec2i{static_cast<int>(p.x), static_cast<int>(p.y)});

        std::vector<u8> indices{};
        for (size_t i = 0; i < m_points - 1; ++i) {
            indices.push_back(0);
            indices.push_back(i + 1);
            indices.push_back(i + 2);
        }
        indices.push_back(0);
        indices.push_back(1);
        indices.push_back(m_points);

        Renderer::drawVerts(verts, indices, m_color, m_mode);
    }

private:
    Vec2f m_position;
    float m_radius;
    u16 m_points;
};
