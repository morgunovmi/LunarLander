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

#include "Game.h"

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, VK_RETURN)
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  schedule_quit_game() - quit game after act()


std::vector<Vec2i> groundVerts {
    Vec2i{500, 0},
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

u16 landingPadIndex = 3;

std::shared_ptr<Renderer> renderer{nullptr};
std::shared_ptr<Player> player{nullptr};
std::shared_ptr<Ground> ground{nullptr};
std::shared_ptr<Font> font{nullptr};


float gameTime = 0.f;
GameWorld world {
    .state = INTRO,
    .objects = {}
};

void handleInput() {
    if (is_key_pressed(VK_ESCAPE)) {
        schedule_quit_game();
    }

    if (is_key_pressed(VK_SPACE)) {
        switch (world.state) {
            case INTRO:
                world.state = GAME;
                break;
            case FAIL:
                world.state = GAME;
                gameTime = 0.f;
                player->reset({500.f, 100.f});
                break;
            case SUCCESS:
                world.state = GAME;
                gameTime = 0.f;
                player->reset({500.f, 100.f});
            break;
        }
    }
}

// initialize game data in this function
void initialize()
{
    std::cout << "Starting game with resolution: (" << SCREEN_WIDTH << " x " << SCREEN_HEIGHT << ")\n";

    font = std::make_shared<Font>("./resources/fonts/roboto.ppm");
    
    world.objects.insert(
            std::make_shared<Planet>(
                Vec2f{SCREEN_WIDTH - 150, 150},
                100.f,
                Blue,
                75,
                "Planet"
            )
        );

    world.objects.insert(
            std::make_shared<Circle>(
                Vec2f{150, 150},
                100.f,
                Blue,
                75, 
                false,
                "Hollow"
            )
        );

    ground = std::make_shared<Ground>(
            groundVerts,
            groundIndices,
            White,
            "Ground"
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
            landingPadIndex,
            world,
            "Player"
        );

    world.objects.insert(ground);
    world.objects.insert(player);

    renderer = std::make_shared<Renderer>(world);
}

std::vector<double> actTimes{};
// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    handleInput();

    if (world.state == GAME || world.state == FREEROAM) {
        gameTime += dt;
        Timer t{};
        // Think about pthread usage
        //std::cout << "Num obects in the scene: " << world.size() << '\n';

        for (auto it = world.objects.begin(); it != world.objects.end();) {
            (*it)->update(dt);

            if (!(*it)->m_isAlive) {
                it = world.objects.erase(it);
            } else {
                ++it;
            }
            actTimes.push_back(t.stop());
        }
    }
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

    switch (world.state) {
        case INTRO:
            Renderer::drawText({250, 20}, "Welcome to Lunar Lander", font, White);
            Renderer::drawText({250, 40}, "Your goal is to safely land the rocket on the green landing pad", font, White);
            Renderer::drawText({250, 60}, "You have limited fuel and the faster you do it the more points you get", font, White);
            Renderer::drawText({250, 80}, "Touching the ground anywhere except the landing pad means failure", font, White);
            Renderer::drawText({250, 100}, "You also have to land the right way up", font, White);
        break;
        case GAME: {
            std::string gameTimeText{"Current game time: " + std::to_string(gameTime)};
            Renderer::drawText({300, 40}, gameTimeText, font, White);

            std::string monopropText{"Monoprop left: " + std::to_string(player->getRemainingMonoProp() > 0.f ?
                                                                        player->getRemainingMonoProp() : 0.f)};
            Renderer::drawText({300, 60}, monopropText, font, White);

            std::string fuelText{"Fuel and oxidizer left left: " + std::to_string(player->getRemainingFuelAndOx() > 0.f ?
                                                                                  player->getRemainingFuelAndOx() : 0.f)};
            Renderer::drawText({300, 80}, fuelText, font, White);
            
            const auto speed = player->getSpeed();
            std::string speedText{"Speed: " + std::to_string(speed)};
            if (speed > player->crashSpeed) {
                Renderer::drawText({300, 100}, speedText, font, Red);
            } else {
                Renderer::drawText({300, 100}, speedText, font, Green);
            }
            const auto angVel = std::abs(player->getAngVel());
            std::string angVelText{"Angular velocity: " + std::to_string(angVel)};
            if (angVel > player->crashAngVel) {
                Renderer::drawText({300, 120}, angVelText, font, Red);
            } else {
                Renderer::drawText({300, 120}, angVelText, font, Green);
            }

        }
        break;
        case FAIL:
            Renderer::drawText({250, 20}, "You have crashed your rocket! Jebediah is gone!", font, Red);
            Renderer::drawText({250, 40}, "Press space to try again", font, Red);
        break;
        case SUCCESS: {
            Renderer::drawText({250, 20}, "You have successfully landed the rocket! Congratulations!", font, Green);
            const u32 score = player->getRemainingFuelAndOx() + player->getRemainingMonoProp() + 100.f / (player->numBounces + 1) + 200.f / gameTime;
            std::string scoreText{"Your score is " + std::to_string(score)};
            Renderer::drawText({250, 40}, scoreText, font, Green);
            Renderer::drawText({250, 80}, "Press space to play again", font, Green);
        }
            break;
        case FREEROAM:
        break;
        default:
            throw std::runtime_error{"Undefined game mode encountered"};
    }

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
