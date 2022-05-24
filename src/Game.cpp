#include <stdlib.h>
#include <memory.h>
#include <memory>

#include <stdio.h>
#include <array>

#include "engine/Engine.h"
#include "math/math.h"
#include "renderer/Renderer.h"
#include "entities/Object.h"

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, VK_RETURN)
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  schedule_quit_game() - quit game after act()

void handleInput() {
    if (is_key_pressed(VK_ESCAPE)) {
        schedule_quit_game();
    }
}

std::shared_ptr<Renderer> renderer{nullptr};
std::vector<std::shared_ptr<Object>> world{};

const std::vector<Vec2i> quadVerts {
    Vec2i{SCREEN_WIDTH - 10, 100},
    Vec2i{SCREEN_WIDTH - 10, 200},
    Vec2i{SCREEN_WIDTH - 50, 150},
};

const std::vector<u8> quadIndices {
    0, 1, 2
};

const std::vector<Vec2i> groundVerts {
    Vec2i{400, 400},
    Vec2i{400, SCREEN_WIDTH - 10},
};

const std::vector<u8> groundIndices {
    0, 1
};

const std::vector<Vec2i> starVerts {
    {SCREEN_WIDTH - 10, SCREEN_HEIGHT - 10}
};

// initialize game data in this function
void initialize()
{
    std::cout << "Starting game with resolution: (" << SCREEN_WIDTH << " x " << SCREEN_HEIGHT << ")\n";

    world.push_back(
            std::make_shared<Object>(
                quadVerts,
                quadIndices,
                Red,
                TRIANGLES,
                Vec2f{0, 0},
                Vec2f{0, 0},
                12
            )
        );

    world.push_back(
            std::make_shared<Object>(
                groundVerts,
                groundIndices,
                White,
                LINES,
                Vec2f{0, 0},
                Vec2f{0, 0},
                12
            )
        );

    world.push_back(
            std::make_shared<Object>(
                starVerts,
                groundIndices,
                Green,
                POINTS,
                Vec2f{0, 0},
                Vec2f{0, 0},
                12
            )
        );

    renderer = std::make_shared<Renderer>(world);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    handleInput();
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)

void draw()
{
    // clear backbuffer
    renderer->draw();
}

// free game data in this function
void finalize()
{
}
