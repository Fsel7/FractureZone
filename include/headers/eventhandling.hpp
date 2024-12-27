#pragma once

namespace sf {
    enum GamePhase : uint8_t;
    struct Player;
    class Game;
    class Event;
    
    /// @brief Returns true iff the game was paused.
    bool processEvents(RenderWindow &window, GamePhase &phase, Player &player);

    /// @brief To be used during runPhase.
    void processLiveEvent(const Event &event, GamePhase &phase, Player &player);
    
    /// @brief To be used during runPhase.
    void awaitUnpause(RenderWindow &window, GamePhase &phase, Player &player);

    /// @brief Handles user inputs during menuPhase.
    void menuEvents(RenderWindow &window, const Game &game, GamePhase &phase, const MenuInterface &menu);

    /// @brief Handles user inputs during settingsPhase.
    void settingsEvents(RenderWindow& window, Game &game, GamePhase &phase, const MenuInterface &menu, IniManager &ini);

    /// @brief Handles user inputs during the game over screen.
    void lostEvents(RenderWindow &window, GamePhase &phase);

}