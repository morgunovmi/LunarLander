#pragma once

#include <cassert>
#include <array>
#include <vector>
#include <memory>

#include "RendererConstants.h"
#include "engine/Engine.h"
#include "entities/Object.h"

class Renderer {
public:
    Renderer(std::vector<std::shared_ptr<Object>>& world)
        :m_world(world) {} 

    void fill(Color c);

    void line(Vec2i p0, Vec2i p1, Color color);

    void triangle(std::array<Vec2i, 3>& v, Color color);

    void drawVerts(const std::vector<Vec2i>& verts, const std::vector<u8>& indices, Color color, DrawMode mode);

    void draw();

private:
    std::vector<std::shared_ptr<Object>>& m_world;
};
