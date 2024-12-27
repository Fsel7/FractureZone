#include <headers/sampler.hpp>
#include <headers/gui.hpp>
#include <headers/managers.hpp>

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

public:
    GameEngine(const Game &gameZ, const Player &playerZ, const int seedling);

    ~GameEngine() { delete window; }

    void execute();

private:
    MersenneSampler sampler;
    Player player;
    Clock clock;
    Game game;
    GamePhase phase;
    MenuInterface menu;
    RenderWindow* window;
    IniManager ini;
    
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
};

}