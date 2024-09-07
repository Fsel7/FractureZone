#include <headers\sampler.hpp>

#pragma once

namespace sf {

struct Player;
struct BlackHole;

class Clock;
class Game;

class GameEngine {

protected:
    MersenneSampler sampler;
    Player player;
    Clock clock;
    Game game;
    BlackHole sink;
    
protected:
    /// @brief Restarts the clock and returns the passed time in seconds
    float restartClock() {
        return clock.restart().asSeconds();
    }

    void createEnemies();

public:
    GameEngine(Game* gameZ, Player* playerZ, int seedling);

    void execute();

};

}