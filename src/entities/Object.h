#pragma once

#include "Drawable.h"

class Object : public Drawable {
public:
    Object(Color color, DrawMode mode) 
        : Drawable(color, mode) {}

    virtual void update(float dt) {}

    virtual ~Object() = default;
};
