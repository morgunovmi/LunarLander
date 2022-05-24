#pragma once

#include "Quad.h" 

class Player : public Quad {
public:
    Player(Vec2f pos, Vec2f vel,
           u16 width, u16 height,
           float rot, float angVel,
           Color color, DrawMode mode)
        : Quad(pos, width, height, rot, color, mode),
        m_vel(vel), m_angVel(angVel) {}

    virtual void update(float dt) override {
        Vec2f acc{};
        if (is_key_pressed(VK_UP)) {
            acc.y -= mainEnginePower;
        }

        if (acc.norm() > maxAcc) {
            acc = acc * (maxAcc / acc.norm());
        }

        m_vel = m_vel + acc;
        m_vel = m_vel + grav;
        m_position = m_position + m_vel * dt;

        float angAcc = 0;
        if (is_key_pressed(VK_LEFT)) {
            angAcc -= maneuverEnginePower; 
        }
        if (is_key_pressed(VK_RIGHT)) {
            angAcc += maneuverEnginePower;
        }

        std::clamp(angAcc, -maxAngAcc, maxAngAcc);

        m_angVel += angAcc;
        m_rotation += m_angVel * dt;
    }

private:
    Vec2f m_vel;
    float m_angVel;

    const float maxAcc = 10.f;
    const float maxAngAcc = 0.5f;
    const float maxVel = 10.f;

    const float mainEnginePower = 2.f;
    const float maneuverEnginePower = 0.01f;

    Vec2f grav{0.0, 1};
};
