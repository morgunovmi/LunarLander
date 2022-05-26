#include <memory>
#include <unordered_set>

#include "engine/Engine.h"
#include "math/math.h"
#include "renderer/Renderer.h"
#include "entities/Player.h"
#include "entities/Ground.h"
#include "entities/Planet.h"
#include "text/Font.h"
#include "timer/Timer.h"

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

std::shared_ptr<Renderer> renderer{nullptr};
std::unordered_set<std::shared_ptr<Object>> world{};
std::shared_ptr<Player> player{nullptr};
std::shared_ptr<Ground> ground{nullptr};
std::shared_ptr<Font> font{nullptr};


// initialize game data in this function
void initialize()
{
    std::cout << "Starting game with resolution: (" << SCREEN_WIDTH << " x " << SCREEN_HEIGHT << ")\n";

    font = std::make_shared<Font>("./resources/fonts/roboto.ppm");
    
    world.insert(
            std::make_shared<Planet>(
                Vec2f{SCREEN_WIDTH - 150, 150},
                100.f,
                Blue,
                75 
            )
        );

    world.insert(
            std::make_shared<Circle>(
                Vec2f{150, 150},
                100.f,
                Blue,
                75, 
                false
            )
        );

    ground = std::make_shared<Ground>(
            groundVerts,
            groundIndices,
            White
        );

    player = std::make_shared<Player>(
            Vec2f{500, 100}, // Pos
            Vec2f{0, 0}, // Vel 
            40,         // width 
            80,         // height
            0,          // Rot
            0,          // AngVel
            White,
            TRIANGLES,
            ground,
            world
        );

    world.insert(ground);
    world.insert(player);

    renderer = std::make_shared<Renderer>(world);
}

std::vector<double> actTimes{};
// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    Timer t{};
    handleInput();
    // Think about pthread usage
    //std::cout << "Num obects in the scene: " << world.size() << '\n';
    for (auto it = world.begin(); it != world.end();) {
        (*it)->update(dt);

        if (!(*it)->m_isAlive) {
            it = world.erase(it);
        } else {
            ++it;
        }
    }
    actTimes.push_back(t.stop());
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
std::vector<double> drawTimes{};

void draw()
{
    Timer t{};
    // clear backbuffer
    Renderer::fill(Black);

    renderer->draw();

    Renderer::drawText({300, 300}, "Hello, World! My name is Jeffrey Jefferson Thompson", font, Red);
    drawTimes.push_back(t.stop());
}

// free game data in this function
void finalize()
{
    auto act = std::accumulate(actTimes.begin(), actTimes.end(), 0.0) / actTimes.size();
    auto draw = std::accumulate(drawTimes.begin(), drawTimes.end(), 0.0) / drawTimes.size();
    std::cout << "Avg act time: " << act << '\n';
    std::cout << "Avg draw time: " << draw << '\n';
    std::cout << "Avg total frame time: " << act + draw << '\n';
}
