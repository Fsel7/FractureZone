#pragma once

namespace sf {

    enum GamePhase;
    struct Player;
    class Event;
    
    void handleEvent(Event &event, GamePhase &phase, Player &player);

}