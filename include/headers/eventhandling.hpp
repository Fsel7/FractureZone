#pragma once

namespace sf {
    enum GamePhase;
    struct Player;
    class Game;
    class Event;

    inline bool leftMouseOrButton(Event &event, Keyboard::Key key) {
        return (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) ||
               (event.type == Event::KeyPressed         && event.key.code == key);
    }

    inline bool leftMouseOrKey(Event &event) {
        bool letterOrEsc = event.key.code == Keyboard::Key::Escape || event.key.code <= 25;
        return (event.type == Event::KeyPressed         && letterOrEsc) ||
               (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left);
    }
    
    /// @brief Returns true iff the game was paused.
    bool processEvents(Window *window, GamePhase &phase, Player &player);

    /// @brief To be used during runPhase.
    void processLiveEvent(Event &event, GamePhase &phase, Player &player);
    
    /// @brief To be used during runPhase.
    void awaitUnpause(Window *window, GamePhase &phase, Player &player);

    /// @brief Handles user inputs during menuPhase.
    void menuEvents(RenderWindow &window, GamePhase &phase, MenuInterface &menu);

    /// @brief Handles user inputs during settingsPhase.
    void settingsEvents(RenderWindow& window, Game &game, GamePhase &phase, MenuInterface &menu);

    /// @brief Handles user inputs during the game over screen.
    void lostEvents(RenderWindow &window, GamePhase &phase);

    template<typename T>
    T fetchNumberInput(RenderWindow &window, MenuInterface &menu, const std::string &prefix, const T minimum, const T maximum);

}