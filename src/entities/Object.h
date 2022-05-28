#pragma once

#include "Drawable.h"

class Object : public Drawable {
public:
    Object(Color color, DrawMode mode, std::string_view tag) 
        : Drawable(color, mode), m_isAlive(true), m_tag(tag) {}

    virtual void update(float dt) {}

    virtual ~Object() = default;

public:
    bool m_isAlive;
    std::string m_tag;
};
