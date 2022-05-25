#pragma once

#include "Drawable.h"

class Object : public Drawable {
public:
    Object(Color color, DrawMode mode) 
        : Drawable(color, mode), m_isAlive(true) {}

    virtual void update(float dt) {}

    virtual ~Object() = default;

public:
    bool m_isAlive;
};
