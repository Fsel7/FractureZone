#pragma once

namespace sf {
    enum GamePhase;
    struct Player;
    class Game;
    class Event;
    
    // Returns true iff the game was paused
    bool processEvents(Window *window, GamePhase &phase, Player &player);

    void processLiveEvent(Event &event, GamePhase &phase, Player &player);

    void awaitUnpause(Window *window, GamePhase &phase, Player &player);

    void menuEvents(RenderWindow &window, GamePhase &phase, MenuInterface &menu);

    void lostEvents(RenderWindow &window, GamePhase &phase);

}