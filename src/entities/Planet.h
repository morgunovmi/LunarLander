#pragma once

#include "Circle.h"
class Planet : public Circle {
public:
    Planet(Vec2f pos, float radius, Color color, u16 numPoints)
        : Circle(pos, radius, color, numPoints, true) {}

    virtual void update(float dt) override {
        m_position.x -= 0.8f * dt;

        if (m_position.x < -m_radius - 10.f) {
            m_position.x = m_radius + 10.f;
        }
    }
}; 
