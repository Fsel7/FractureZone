#include <headers\sampler.hpp>
#include <headers\gui.hpp>

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
    SETTINGS,
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
    MenuInterface menu;
    RenderWindow* window;
    
private:
    /// @brief Restarts the clock and returns the passed time in seconds.
    float restartClock() { return clock.restart().asSeconds(); }

    /// @brief Prepares the next game round.
    void resetPhase();

    /// @brief Handles the entire game round logic.
    void runPhase();

    /// @brief Handles everything related to the menu.
    void menuPhase();

    /// @brief Handles the settings screens.
    void settingsPhase();

    /// @brief Handles the losing screen and everything related.
    void lostPhase();

    /// @brief Final things before closing the program.
    void closePhase();

public:
    GameEngine(Game &gameZ, Player &playerZ, int seedling);

    void execute();
};

}