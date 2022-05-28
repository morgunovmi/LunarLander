#pragma once

#include "Circle.h"
class Planet : public Circle {
public:
    Planet(Vec2f pos, float radius, Color color, u16 numPoints, std::string_view tag)
        : Circle(pos, radius, color, numPoints, true, tag) {}

    virtual void update(float dt) override {
        m_position.x -= 1.5f * dt;

        if (m_position.x < -m_radius - 10.f) {
            m_position.x = m_radius + 10.f;
        }
    }
}; 
