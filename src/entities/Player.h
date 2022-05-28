#pragma once

#include <random>
#include <cmath>

#include "Quad.h" 
#include "Ground.h"
#include "Circle.h"
#include "ExhaustParticle.h"
#include "Game.h"

struct LineCollInfo {
    Vec2f collPoint;
    Vec2f surfNormal;
};

struct QuadCollInfo {
    Vec2f collPoint;
    Vec2f surfNormal;
    u8 faceNum;
};

class Player : public Quad {
public:
    Player(Vec2f pos, Vec2f vel,
           u16 width, u16 height,
           float rot, float angVel,
           Color color, DrawMode mode,
           std::shared_ptr<Ground> ground,
           u16 padIndex,
           GameWorld& world,
           std::string_view tag)
        : Quad(pos, width, height, rot, color, mode, tag),
        m_vel(vel), m_angVel(angVel), m_ground(ground), m_padIndex(padIndex),
        m_world(world) {}

    float getRemainingMonoProp() const { return monoPropAmount; }
    float getRemainingFuelAndOx() const { return fuelAndOxidizerAmount; }

    float getSpeed() const { return m_vel.norm(); }
    float getAngVel() const { return m_angVel; }

    void reset(Vec2f pos) {
        m_position = pos;
        m_vel = Vec2f{};
        m_rotation = 0.f;
        m_angVel = 0.f;
        monoPropAmount = 30.f;
        fuelAndOxidizerAmount = 100.f;
    }

    virtual void update(float dt) override {
        float acc = 0.f;
        Vec2f accVec{0.0, 1.f};
        accVec = mat2vec(rotateAround({0.f, 0.f}, m_rotation) * vec2mat(accVec));

        const auto playerCenter = m_position + m_Anchor;
        auto leftVec = mat2vec(rotateAround({0.f, 0.f}, static_cast<float>(M_PI) / 2)
                               * vec2mat(accVec));
        const auto mainEngine = playerCenter + accVec * (m_height / 2.f); 
        const auto leftEngine = playerCenter - accVec * (m_height / 4.f)
            + leftVec * (m_width / 2.f);

        if (fuelAndOxidizerAmount > 0.f) {
            if (is_key_pressed(VK_UP)) {
                acc -= mainEnginePower;

                m_world.objects.insert(
                        std::make_shared<ExhaustParticle>(
                            mainEngine,
                            1.f * mat2vec(rotateAround({0.f, 0.f}, m_angDistr(m_dre))
                                          * vec2mat(accVec)) * mainExhaustSpeed,
                            3,
                            Red,
                            mainExhaustLife + m_lifeDistr(m_dre),
                            "Particle"
                        )
                    );

                fuelAndOxidizerAmount -= fuelPerSecond * dt;
            }

            std::clamp(acc, -maxAcc, maxAcc);

            m_vel = m_vel + accVec * acc;
        }
        m_vel = m_vel + grav;
        m_position = m_position + m_vel * dt;

        QuadCollInfo collisionInfo{};
        u16 groundIndex;
        if (checkGroundCollisions(m_ground, collisionInfo, groundIndex)) {
            if (groundIndex != m_padIndex) {
                m_world.state = FAIL;
                return;
            } else {
                const auto speed = m_vel.norm();
                if (speed > crashSpeed || std::abs(m_angVel) > crashAngVel) {
                    m_world.state = FAIL;
                    return;
                }

                if (speed < successSpeed && std::abs(m_angVel) < successAngVel && std::abs(m_rotation) < successRotation) {
                    m_world.state = SUCCESS;
                    return;
                }
                ++numBounces;
            }
            //std::cout << "COllision point : " << collisionInfo.collPoint.x << " , " << collisionInfo.collPoint.y << '\n';
            resolveCollision(collisionInfo);
        }

        if (monoPropAmount > 0.f) {
            float angAcc = 0;

            if (is_key_pressed(VK_LEFT)) {
                angAcc -= maneuverEnginePower; 

                m_world.objects.insert(
                        std::make_shared<ExhaustParticle>(
                            leftEngine - leftVec * m_width,
                            -1.f * mat2vec(rotateAround({0.f, 0.f}, m_angDistr(m_dre))
                                           * vec2mat(leftVec)) * maneuverExhaustSpeed,
                            3,
                            Green,
                            maneuverExhaustLife + m_lifeDistr(m_dre), 
                            "Particle"
                        )
                    );

                    monoPropAmount -= monoPropPerSecond * dt;
            }

            if (is_key_pressed(VK_RIGHT)) {
                angAcc += maneuverEnginePower;
                m_world.objects.insert(
                        std::make_shared<ExhaustParticle>(
                            leftEngine,
                            1.f * mat2vec(rotateAround({0.f, 0.f}, m_angDistr(m_dre))
                                          * vec2mat(leftVec)) * maneuverExhaustSpeed,
                            3,
                            Green,
                            maneuverExhaustLife + m_lifeDistr(m_dre),
                            "Particle"
                        )
                    );

                    monoPropAmount -= monoPropPerSecond * dt;
            }

            std::clamp(angAcc, -maxAngAcc, maxAngAcc);

            m_angVel += angAcc;
        }
        m_rotation += m_angVel * dt;

        if (playerCenter.x < -m_width || playerCenter.x > SCREEN_WIDTH + m_width
            || playerCenter.y < -m_height || playerCenter.y > SCREEN_HEIGHT + m_height) {
            m_world.state = FAIL;
        }
    }

    /*
    virtual void draw() override {
        Quad::draw();

        auto playerCenter = m_position + m_Anchor;
        Circle circ{
            playerCenter,
            5.f,
            Red,
            10,
            true,
        };
        circ.draw();

        Vec2f accVec{0.0, 1.f};
        accVec = mat2vec(rotateAround({0.f, 0.f}, m_rotation) * vec2mat(accVec));

        auto p2 = playerCenter + accVec * 500.f;
        Renderer::line(Vec2i{static_cast<int>(playerCenter.y), static_cast<int>(playerCenter.x)},
                       Vec2i{static_cast<int>(p2.y), static_cast<int>(p2.x)}, Red);

        auto leftVec = mat2vec(rotateAround({0.f, 0.f}, M_PI / 2)
                               * vec2mat(accVec.normalize()));

        auto p3 = playerCenter + leftVec * 500.f;
        Renderer::line(Vec2i{static_cast<int>(playerCenter.y), static_cast<int>(playerCenter.x)},
                       Vec2i{static_cast<int>(p3.y), static_cast<int>(p3.x)}, Red);

    }
    */
    const float crashSpeed = 150.f;
    const float crashAngVel = 1.f;
    const float successSpeed = 5.f;
    const float successAngVel = 0.1f;
    const float successRotation = 0.1f;
    u16 numBounces = 0;

private:
    bool lineLineCollision(Vec2f a1, Vec2f a2, Vec2f b1, Vec2f b2, LineCollInfo& collisionInfo) {
        auto x1 = a1.x;
        auto x2 = a2.x;
        auto x3 = b1.x;
        auto x4 = b2.x;
        auto y1 = a1.y;
        auto y2 = a2.y;
        auto y3 = b1.y;
        auto y4 = b2.y;

        // calculate the distance to intersection point
        float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
        float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

        // if uA and uB are between 0-1, lines are colliding
        if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {

            collisionInfo.collPoint.x = x1 + (uA * (x2-x1));
            collisionInfo.collPoint.y = y1 + (uA * (y2-y1)); 
            collisionInfo.surfNormal = Vec2f{-(y4 - y3), (x4 - x3)}.normalize();

            return true;
        }
        return false;
    }

    bool checkGroundCollisions(std::shared_ptr<Ground> ground, QuadCollInfo& collisionInfo, u16& groundIndex) {
        const auto& groundVerts = ground->getVerts();
        for (size_t i = 0; i < groundVerts.size() - 1; ++i) {
            std::vector<Vec2f> transformedQuadVerts{};
            for (const auto & vert : getVerts()) {
                auto newVert = mat2vec(rotateAround(m_Anchor+ m_position, m_rotation) * translation(m_position) * vec2mat(vert));
                transformedQuadVerts.push_back(newVert);
            }

            Vec2f groundSegmentP1{static_cast<float>(groundVerts[i].y), static_cast<float>(groundVerts[i].x)};
            Vec2f groundSegmentP2{static_cast<float>(groundVerts[i + 1].y), static_cast<float>(groundVerts[i + 1].x)};
            LineCollInfo info{};
            for (size_t j = 0; j < 3; ++j) {
                if (lineLineCollision(transformedQuadVerts[j], transformedQuadVerts[j + 1],
                                      groundSegmentP1, groundSegmentP2, info)) {
                    collisionInfo.collPoint = info.collPoint;
                    collisionInfo.surfNormal = info.surfNormal;
                    collisionInfo.faceNum = j;
                    groundIndex = i;
                    return true;
                }
            }
            if (lineLineCollision(transformedQuadVerts[0], transformedQuadVerts[3],
                                  groundSegmentP1, groundSegmentP2, info)) {
                    collisionInfo.collPoint = info.collPoint;
                    collisionInfo.surfNormal = info.surfNormal;
                    collisionInfo.faceNum = 3;
                    return true;
            }
        }

        return false;
    }

    void resolveCollision(QuadCollInfo collInfo) {
        m_vel = (m_vel - 2 * (collInfo.surfNormal * m_vel) * collInfo.surfNormal) * hitDamping; 

        auto centerCollVec = collInfo.collPoint - (m_position + m_Anchor);
        std::vector<Vec2f> transformedQuadVerts{};
        for (const auto & vert : getVerts()) {
            auto newVert = mat2vec(rotateAround(m_Anchor+ m_position, m_rotation) * translation(m_position) * vec2mat(vert));
            transformedQuadVerts.push_back(newVert);
        }

        auto faceVec = collInfo.faceNum == 3 ? (transformedQuadVerts[3] - transformedQuadVerts[0]) :
                                            (transformedQuadVerts[collInfo.faceNum + 1] - transformedQuadVerts[collInfo.faceNum]);

        float lever = faceVec * centerCollVec;

        std::cout << m_vel.norm() << '\n';
        if (m_vel.norm() > 3.f) {
            m_angVel += lever * m_vel.norm() * 0.000002f;

            if (m_vel.x > horizontalSpeedEps) {
                m_angVel += lever * std::abs(m_vel.x) * 0.00001f;
            } else if (m_vel.x < -horizontalSpeedEps) {
                m_angVel -= lever * std::abs(m_vel.x) * 0.00001f;
            }
        } else {
            if (m_angVel < 0.1f) {
                m_angVel = 0.f;
            }
            m_angVel -= m_angVel > 0 ? 0.1f : -0.1f;
        }
    }


private:
    Vec2f m_vel;
    float m_angVel;

    std::shared_ptr<Ground> m_ground;
    u16 m_padIndex;
    GameWorld& m_world;

    float fuelAndOxidizerAmount = 100.f;
    float fuelPerSecond = 10.f;
    float monoPropAmount = 30.f;
    float monoPropPerSecond = 5.f;

    const float maxAcc = 10.f;
    const float maxAngAcc = 0.5f;

    const float mainEnginePower = 2.f;
    const float maneuverEnginePower = 0.01f;

    const float mainExhaustSpeed = 800.f;
    const float maneuverExhaustSpeed = 800.f;

    const u16 mainExhaustLife = 80;
    const u16 maneuverExhaustLife = 50;

    const float hitDamping = 0.8f;
    const float horizontalSpeedEps = 1.f; 

    Vec2f grav{0.0, 0.7f};

    std::random_device m_rd;
    std::default_random_engine m_dre{ m_rd() };
    std::uniform_real_distribution<float> m_angDistr{ -static_cast<float>(M_PI) / 6,
                                                    static_cast<float>(M_PI) / 6 };
    std::uniform_int_distribution<short> m_lifeDistr{ -50, 50 };
};
