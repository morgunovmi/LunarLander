#include <memory.h>
#include <numeric>
#include <iostream>
#include <algorithm>

#include "Renderer.h"

void Renderer::fill(Color c) {
    std::fill(buffer[0], buffer[0] + SCREEN_HEIGHT * SCREEN_WIDTH, c.c32);
}

void Renderer::line(Vec2i p0, Vec2i p1, Color color) {
    auto x0 = p0.x;
    auto x1 = p1.x;
    auto y0 = p0.y;
    auto y1 = p1.y;

    auto steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    const auto dx = x1 - x0;
    const auto dy = y1 - y0;
    const auto derror2 = std::abs(dy) * 2;
    auto error2 = 0;
    auto y = y0;

    for (int x = x0; x < x1; ++x) {
        if (steep) {
            if (y >= 0 && y < SCREEN_HEIGHT
                && x >= 0 && x < SCREEN_WIDTH) {
                buffer[y][x] = color.c32;
            }
        } else {
            if (x >= 0 && x < SCREEN_HEIGHT
                && y >= 0 && y < SCREEN_WIDTH) {
                buffer[x][y] = color.c32;
            }
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx *2;
        }
    }
}

void Renderer::triangle(std::array<Vec2i, 3>& v, Color color) {
    std::sort(v.begin(), v.end(), [](auto a, auto b) { return a.y < b.y; });
    const auto totalHeight = v[2].y - v[0].y;
    for (int i = 0; i < totalHeight; i++) {
        auto secondHalf = i > v[1].y - v[0].y || v[1].y == v[0].y;
        const auto segHeight = secondHalf ? v[2].y - v[1].y : v[1].y - v[0].y;
        const auto alpha = static_cast<float>(i) / static_cast<float>(totalHeight);
        const auto beta = static_cast<float>(i - (secondHalf ? v[1].y - v[0].y : 0))
                                                / static_cast<float>(segHeight);
        auto a = v[0] + (v[2] - v[0]) * alpha;
        auto b = secondHalf ? v[1] + (v[2] - v[1]) * beta : v[0] + (v[1] - v[0]) * beta;
        if (a.x > b.x) std::swap(a, b);
        for (int j = a.x; j < b.x; j++) {
            if (v[0].y + i >= 0 && v[0].y + i < SCREEN_HEIGHT
                && j >= 0 && j < SCREEN_WIDTH) {
                buffer[v[0].y + i][j] = color.c32;
            }
        }
    }
}

void Renderer::drawVerts(const std::vector<Vec2i> &verts, const std::vector<u8> &indices, Color color, DrawMode mode) {
    switch (mode) {
        case TRIANGLES: {
            const auto numTriangles = indices.size() / 3;

            for (size_t i = 0; i < numTriangles; ++i) {
                std::array<Vec2i, 3> triangleVerts{
                    verts[indices[3 * i]],
                    verts[indices[3 * i + 1]],
                    verts[indices[3 * i + 2]]
                };
                triangle(triangleVerts, color);
            }
        }
        break;
        case LINES: {
            const auto numLines = indices.size() / 2;

            for (size_t i = 0; i < numLines; ++i) {
                Vec2i p0 = verts[indices[2 * i]]; 
                Vec2i p1 = verts[indices[2 * i + 1]]; 
                line(p0, p1, color);
            }
        }
        break;
        case POINTS:
            for (const auto & vert : verts) {
                if (vert.y >= 0 && vert.y < SCREEN_HEIGHT
                    && vert.x >= 0 && vert.x < SCREEN_WIDTH) {
                    buffer[vert.y][vert.x] = color.c32;
                }
            }
        break;
        default:
            std::cerr << "Undefined draw mode\n";
    }
}

void Renderer::draw() {
    for (const auto & obj : m_background) {
        obj->draw();
    }

    for (const auto & obj : m_world.objects) {
        obj->draw();
    }
}

void Renderer::drawText(Vec2i pos, std::string_view text, std::shared_ptr<Font> font, Color color) {
    const auto& atlas = font->getAtlas();

    u16 xOffset = 0;
    for (auto c : text) {
        const auto glyph = font->getGlyph(c);

        for (size_t y = 0; y < glyph.height; ++y) {
            for (size_t x = 0; x < glyph.width; ++x) {
                auto atlasPixelColor = atlas.getImage()[glyph.startPos.y + y][glyph.startPos.x + x];

                if (atlasPixelColor.g > 50) {
                    buffer[pos.y + y][pos.x + xOffset + x] = color.c32;
                }
            }
        }

        xOffset += glyph.width;
    }
}
