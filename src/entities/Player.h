#pragma once

#include "Quad.h" 
#include "Ground.h"
#include "Circle.h"

class Player : public Quad {
public:
    Player(Vec2f pos, Vec2f vel,
           u16 width, u16 height,
           float rot, float angVel,
           Color color, DrawMode mode)
        : Quad(pos, width, height, rot, color, mode),
        m_vel(vel), m_angVel(angVel) {}

    void checkGroundCollisions(std::shared_ptr<Ground> ground) {

    }

    virtual void update(float dt) override {
        float acc = 0.f;
        if (is_key_pressed(VK_UP)) {
            acc -= mainEnginePower;
        }

        std::clamp(acc, -maxAcc, maxAcc);

        Vec2f accVec{0.0, 1.f};
        accVec = mat2vec(rotateAround({0.f, 0.f}, m_rotation) * vec2mat(accVec));
        accVec = accVec * acc;

        m_vel = m_vel + accVec;
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
    bool lineLineCollision(Vec2f a1, Vec2f a2, Vec2f b1, Vec2f b2) {
        auto x1 = a1.x;
        auto x2 = a2.x;
        auto x3 = b1.x;
        auto x4 = b2.x;
        auto y1 = a1.y;
        auto y2 = a2.y;
        auto y3 = b1.y;
        auto y4 = b2.y;

        // calculate the distance to intersection point
        float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
        float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

        // if uA and uB are between 0-1, lines are colliding
        if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

            // optionally, draw a circle where the lines meet
            float intersectionX = x1 + (uA * (x2-x1));
            float intersectionY = y1 + (uA * (y2-y1));

            Circle coll{Vec2f{intersectionX, intersectionY}, 10.f, Red, 10, true};
            coll.draw();

            return true;
        }
        return false;
    }

    Vec2f m_vel;
    float m_angVel;

    const float maxAcc = 10.f;
    const float maxAngAcc = 0.5f;

    const float mainEnginePower = 2.f;
    const float maneuverEnginePower = 0.01f;

    Vec2f grav{0.0, 0.7f};
};
