#include <headers\sampler.hpp>

#pragma once

namespace sf {

struct Player;
struct BlackHole;

class Clock;
class Game;

enum GamePhase{
    RESETTING,
    RUNNING,
    PAUSED,
    MENU,
    LOST,
    CLOSE
};

class GameEngine {

private:
    MersenneSampler sampler;
    Player player;
    Clock clock;
    Game game;
    GamePhase phase;
    
private:
    /// @brief Restarts the clock and returns the passed time in seconds
    float restartClock() { return clock.restart().asSeconds(); }

    void resetPhase();

    void runPhase();

    void menuPhase();

    void lostPhase();

    void closePhase();

public:
    GameEngine(Game &gameZ, Player &playerZ, int seedling);

    void execute();
};

}