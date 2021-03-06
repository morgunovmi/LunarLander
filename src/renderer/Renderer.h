#pragma once

#include <array>
#include <unordered_set>

#include "RendererConstants.h"
#include "engine/Engine.h"
#include "entities/Object.h"
#include "text/Font.h"
#include "Game.h"

class Renderer {
public:
    Renderer(GameWorld& world, std::unordered_set<std::shared_ptr<Object>>& background)
        : m_world(world), m_background(background) {} 

    static void fill(Color c);

    static void line(Vec2i p0, Vec2i p1, Color color);

    static void triangle(std::array<Vec2i, 3>& v, Color color);

    static void drawVerts(const std::vector<Vec2i>& verts, const std::vector<u8>& indices, Color color, DrawMode mode);

    static void drawText(Vec2i pos, std::string_view text, std::shared_ptr<Font> font, Color color);

    void draw();

private:
    GameWorld& m_world;
    std::unordered_set<std::shared_ptr<Object>>& m_background;
};
