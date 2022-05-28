#pragma once

#include <unordered_set>
#include <memory>

#include "entities/Object.h"

enum GameState {
    INTRO,
    GAME,
    FAIL,
    SUCCESS,
    FREEROAM,
};

struct GameWorld {
    GameState state;
    std::unordered_set<std::shared_ptr<Object>> objects;
};
