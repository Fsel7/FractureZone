#pragma once

namespace sf {
    class Event;
    class RenderWindow;
    class Player;
    
    void handleEvent(Event &event, RenderWindow &window, Player &player);

}