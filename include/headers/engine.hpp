#include <headers\sampler.hpp>
#include <headers\spawner.hpp>

#pragma once

namespace sf {

class Player;
class Clock;
class Game;
class Font;
class BlackHole;

class GameEngine {

protected:
    MersenneSampler sampler;
    Player player;
    Clock clock;
    Game game;
    Font font;
    BlackHole sink;
    CircularSpawner spawner1;
    
protected:
    /// @brief Restarts the clock and returns the passed time in seconds
    float restartClock() {
        return clock.restart().asSeconds();
    }

    void createEnemies();

    void createSpawners();

public:
    GameEngine(int seedling);

    void execute();

};

}