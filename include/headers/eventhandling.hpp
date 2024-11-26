#pragma once

namespace sf {
    enum GamePhase;
    struct Player;
    class Game;
    class Event;
    
    /// @brief Returns true iff the game was paused.
    bool processEvents(Window *window, GamePhase &phase, Player &player);

    /// @brief To be used during runPhase.
    void processLiveEvent(Event &event, GamePhase &phase, Player &player);
    
    /// @brief To be used during runPhase.
    void awaitUnpause(Window *window, GamePhase &phase, Player &player);

    /// @brief Handles user inputs during menu phase.
    void menuEvents(RenderWindow &window, GamePhase &phase, MenuInterface &menu);

    /// @brief Handles user inputs during the game over screen.
    void lostEvents(RenderWindow &window, GamePhase &phase);

}