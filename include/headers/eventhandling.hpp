#pragma once

namespace sf {
    enum GamePhase;
    struct Player;
    class Game;
    class Event;

    inline bool isLeftMouse(Event &event) {
        return event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left;
    }

    inline bool isKey(Event &event, Keyboard::Key key) {
        return event.type == Event::KeyPressed && event.key.code == key;
    }

    inline bool isBackSpace(Event &event) {
        return event.type == Event::KeyPressed && (event.key.code == Keyboard::Key::BackSpace || event.key.code == Keyboard::Key::Backspace);
    }

    inline bool isNumber(Event &event) {
        return event.type == Event::KeyPressed && event.key.code >= 26 && event.key.code <= 35;
    }

    inline bool isLetter(Event &event) {
        return event.type == Event::KeyPressed && event.key.code <= 25;
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