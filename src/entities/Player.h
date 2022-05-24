#pragma once

#include "Quad.h" 

class Player : public Quad {
public:
    Player(Vec2f pos, Vec2f vel, Vec2f acc,
           u16 width, u16 height,
           float rot, float angVel, float angAcc,
           Color color, DrawMode mode)
        : Quad(pos, width, height, rot, color, mode),
        m_vel(vel), m_acc(acc), m_angVel(angVel), m_angAcc(angAcc) {}

    void update(float dt) override {

    }

private:
    Vec2f m_vel;
    Vec2f m_acc;
    float m_angVel;
    float m_angAcc;
};
