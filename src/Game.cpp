#include <stdlib.h>
#include <memory.h>
#include <memory>

#include <stdio.h>
#include <array>

#include "engine/Engine.h"
#include "math/math.h"
#include "renderer/Renderer.h"
#include "entities/Player.h"
#include "entities/Ground.h"
#include "entities/Circle.h"

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

std::vector<Vec2i> groundVerts {
    Vec2i{500, 0 },
    Vec2i{400, 100},
    Vec2i{500, 200},
    Vec2i{400, 300},
    Vec2i{400, 600},
    Vec2i{500, 700},
    Vec2i{400, 800},
    Vec2i{400, SCREEN_WIDTH},
};

std::vector<u8> groundIndices {
    0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7
};

// initialize game data in this function
void initialize()
{
    std::cout << "Starting game with resolution: (" << SCREEN_WIDTH << " x " << SCREEN_HEIGHT << ")\n";

    world.push_back(
            std::make_shared<Player>(
                Vec2f{500, 500}, // Pos
                Vec2f{0, 0}, // Vel 
                100,         // width 
                200,         // height
                0,          // Rot
                0,          // AngVel
                White,
                TRIANGLES
            )
        );

    world.push_back(
            std::make_shared<Ground>(
                groundVerts,
                groundIndices,
                White
            )
        );

    world.push_back(
            std::make_shared<Circle>(
                Vec2f{500, 350},
                100.f,
                Green,
                100 
            )
        );

    renderer = std::make_shared<Renderer>(world);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    handleInput();
    for (auto & obj : world) {
        obj->update(dt);
    }
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
