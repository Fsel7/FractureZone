#include <headers/sampler.hpp>
#include <headers/gui.hpp>
#include <headers/managers.hpp>
#include <headers/entities.hpp>
#include <headers/game.hpp>

#pragma once

namespace sf {

struct BlackHole;
class Clock;

enum GamePhase : uint8_t {
    RESETTING,
    RUNNING,
    PAUSED,
    MENU,
    SETTINGS,
    LOST,
    CLOSE
};

class GameEngine {
    friend class XMLParser;

public:
    GameEngine(const Game &gameZ, const Player &playerZ, const int seedling, const int width, const int height, const std::string &name);

    ~GameEngine() { delete window; }

    void execute();

private:
    MersenneSampler sampler;
    RenderWindow* window;
    Player player;
    Clock clock;
    Game game;
    GamePhase phase;
    MenuInterface menu;
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