#pragma once

#include "Drawable.h"

class Object : public Drawable {
public:
    Object(const std::vector<Vec2i>& verts, const std::vector<u8>& indices, Color color, DrawMode mode,
           Vec2f pos, Vec2f vel, float rot)
           : Drawable(verts, indices, color, mode),
            m_position(pos), m_velocity(vel), m_rotation(rot) {}

    Vec2f m_position;
    Vec2f m_velocity;
    float m_rotation;
};
