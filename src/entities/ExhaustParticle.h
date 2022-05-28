#pragma once

#include <chrono>

#include "Circle.h"

class ExhaustParticle : public Circle {
public:
    using clock_t = std::chrono::steady_clock;
    using timepoint_t = clock_t::time_point;

    ExhaustParticle(Vec2f pos, Vec2f vel, float radius, Color color, u16 lifeTime, std::string_view tag) 
        : Circle(pos, radius, color, 20, true, tag), m_spawnTime(clock_t::now()), m_lifeTime(lifeTime),
            m_velocity(vel) {} 

    virtual void update(float dt) override {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(clock_t::now() - m_spawnTime).count() > m_lifeTime) {
            m_isAlive = false;
        }

        m_position = m_position + m_velocity * dt;
    }

private:
    timepoint_t m_spawnTime;
    u16 m_lifeTime;
    Vec2f m_velocity;
};
