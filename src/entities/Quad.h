#pragma once

#include "Object.h"
#include "renderer/Renderer.h"

class Quad : public Object {
public:
    Quad(Vec2f pos, u16 width, u16 height, float rot, Color color, DrawMode mode)
        : Object(color, mode), m_position(pos),
        m_width(width), m_height(height), m_rotation(rot),
        m_Anchor(Vec2f{static_cast<float>(width / 2),
                     static_cast<float>(height / 2)}) {}

    // Sets a new anchor with respect to position
    void setAnchor(Vec2f newAnchor) {
        m_Anchor = newAnchor;
    }

    virtual void draw() override {
        std::vector<Vec2i> transformed{};
        for (const auto & vert : m_verts) {
            auto newVert = mat2vec(rotateAround(m_Anchor+ m_position, m_rotation) * translation(m_position) * vec2mat(vert));

            transformed.push_back({static_cast<int>(newVert.x), static_cast<int>(newVert.y)});
        }

        Renderer::drawVerts(transformed, m_indices, m_color, m_mode);
    }

    Vec2f m_position;
    u16 m_width;
    u16 m_height;
    float m_rotation;
    Vec2f m_Anchor;
private:

    std::vector<Vec2f> m_verts {
        {0, 0},
        {0, static_cast<float>(m_height)},
        {static_cast<float>(m_width), 0},
        {static_cast<float>(m_width), static_cast<float>(m_height)}
    };

    const std::vector<u8> m_indices {
        0, 1, 2, 1, 2, 3
    };
};
